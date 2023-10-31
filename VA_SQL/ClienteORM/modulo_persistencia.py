from pyModbusTCP.client import ModbusClient
from datetime import datetime
from time import sleep
from tabulate import tabulate
from threading import Thread, Lock
from db_settings import Session, Base, engine
from models import DadoCLP


class ModbusPersistencia:
    """
    Classe que implementa a funcionalidade de persistencia de dados lidos a partir do protocolo do Modbus e também permite a busca de dados históricos
    """

    def __init__(self, server_ip, server_port, tags_addrs, scan_time=1):
        self._client = ModbusClient(host=server_ip, port=server_port)
        self._scan_time = scan_time
        self._tags = tags_addrs
        self._session = Session()
        self._lock = Lock()
        self.create_data = Thread(target=self._create_data)
        Base.metadata.create_all(engine)

    def _create_data(self):
        """
        Faz a leitura dos dados do servidor e salva na DB
        """
        try:
            print("Persistencia iniciada")
            self._client.open()
            data = {}
            while True:
                data["timestamp"] = datetime.now()
                for tag in self._tags:
                    data[tag] = self._client.read_holding_registers(self._tags[tag], 1)[0]
                dado_clp = DadoCLP(**data)

                self._lock.acquire()
                self._session.add(dado_clp)
                self._session.commit()
                self._lock.release()

                sleep(self._scan_time)

        except Exception as e:
            print("Erro na persistência de dados -> ", e.args[0])

    def access_history(self):
        """
        Permite ao usuário acessar dados históricos
        """
        try:
            print("Acesso aos dados históricos")
            while True:
                init_date = str(input("Horário inicial (DD/MM/YYYY HH:MM:SS): "))
                final_date = str(input("Horário final (DD/MM/YYYY HH:MM:SS): "))
                init_date = datetime.strptime(init_date, "%d/%m/%Y %H:%M:%S")
                final_date = datetime.strptime(final_date, "%d/%m/%Y %H:%M:%S")

                self._lock.acquire()
                query = (
                    self._session.query(DadoCLP)
                    .filter(DadoCLP.timestamp.between(init_date, final_date))
                    .all()
                )
                self._lock.release()

                result = [obj.get_attributes() for obj in query]

                print(tabulate(result, DadoCLP.__table__.columns.keys()))

        except Exception as e:
            print("Erro na busca de dados -> ", e.args[0])
