from pyModbusTCP.server import DataBank, ModbusServer
import random
from time import sleep


class ServidorMODBUS:
    """
    Servidor MODBUS
    """

    def __init__(self, host_ip, port) -> None:
        self.__server = ModbusServer(host=host_ip, port=port, no_block=True)
        self.__db = DataBank()

    def run(self):
        try:
            self.__server.start()
            print("Servidor MODBUS em execução")
            while True:
                self.__db.set_words(
                    address=1000,
                    word_list=[random.randrange(int(400 * 0.95), int(400 * 1.05))],
                )
                print(30 * "=")
                print("Tabela MODBUS")
                print(
                    f"Holdind Register \n R1000 = {self.__db.get_words(address=1000)} \n R2000 = {self.__db.get_words(address=2000)}"
                )
                print(f"Coil \n R1000 = {self.__db.get_bits(address=1000)}")
                sleep(1)

        except Exception as e:
            print("Erro -> ", e.args)
