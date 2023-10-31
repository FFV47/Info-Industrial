from pyModbusTCP.server import DataBank, ModbusServer
from time import sleep
import random


class ServidorMODBUS:
    """
    Classe Servidor MODBUS
    """

    def __init__(self, host_ip, port):
        """
        Construtor
        """
        self._server = ModbusServer(host=host_ip, port=port, no_block=True)
        self._db = DataBank

    def run(self):
        """
         Execução do servidor
        """
        self._server.start()
        print("Servidor em execução")
        while True:
            self._db.set_words(1000, [random.randrange(400, 500)])  # temperatura
            self._db.set_words(1001, [random.randrange(100000, 120000)])  # pressão
            self._db.set_words(1002, [random.randrange(20, 40)])  # umidade
            self._db.set_words(1003, [random.randrange(40, 100)])  # consumo
            sleep(1)
