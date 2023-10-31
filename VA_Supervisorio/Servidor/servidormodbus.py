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
            self._db.set_words(1000, [random.randrange(int(0.95 * 400), int(1.05 * 400))])
            self._db.set_words(1001, [random.randrange(int(0.95 * 20), int(1.05 * 20))])
            self._db.set_words(1002, [random.randrange(int(0.95 * 30), int(1.05 * 30))])
            self._db.set_words(1003, [random.randrange(int(0.95 * 110), int(1.05 * 110))])
            self._db.set_words(1004, [random.randrange(int(0.95 * 180), int(1.05 * 180))])
            self._db.set_words(1005, [random.randrange(int(0.95 * 260), int(1.05 * 260))])
            self._db.set_words(1006, [random.randrange(int(0.95 * 280), int(1.05 * 280))])
            self._db.set_words(1007, [random.randrange(int(0.95 * 300), int(1.05 * 300))])
            self._db.set_words(1008, [random.randrange(int(0.95 * 340), int(1.05 * 340))])
            sleep(1)
