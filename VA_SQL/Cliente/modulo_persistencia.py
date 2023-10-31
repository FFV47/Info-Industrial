from pyModbusTCP.client import ModbusClient
from db_handler import DBHandler
from datetime import datetime
from time import sleep
from tabulate import tabulate
from threading import Thread


class ModbusPersistencia:
    """
    Classe que implementa a funcionalidade de persistencia de dados lidos a partir do protocolo do Modbus e também permite a busca de dados históricos
    """

    def __init__(self, server_ip, server_port, tags_addrs, scan_time=1):
        self._client = ModbusClient(host=server_ip, port=server_port)
        self._scan_time = scan_time
        self._tags = tags_addrs
        self._db_handler = DBHandler("database/data.db", self._tags.keys())
        self.create_data = Thread(target=self._create_data)

    def _create_data(self):
        """
        Faz a leitura dos dados do servidor e salva na DB
        """
        try:
            print("Persistencia iniciada")
            self._client.open()
            data = {}
            while True:
                data["timestamp"] = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                for tag in self._tags:
                    data[tag] = self._client.read_holding_registers(self._tags[tag], 1)[
                        0
                    ]
                self._db_handler.insert_data(data)
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
                init_date = datetime.strptime(init_date, "%d/%m/%Y %H:%M:%S").strftime(
                    "%Y-%m-%d %H:%M:%S"
                )
                final_date = datetime.strptime(
                    final_date, "%d/%m/%Y %H:%M:%S"
                ).strftime("%Y-%m-%d %H:%M:%S")

                selected_data = self._db_handler.select_data(init_date, final_date)

                print(
                    tabulate(
                        selected_data["data"], selected_data["cols"], showindex="always"
                    )
                )

        except Exception as e:
            print("Erro na busca de dados -> ", e.args[0])
