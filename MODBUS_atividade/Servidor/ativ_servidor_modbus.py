from pyModbusTCP.server import DataBank, ModbusServer
from pymodbus.payload import BinaryPayloadBuilder, BinaryPayloadDecoder
import random
from time import sleep


class ServidorMODBUS:
    """
    Servidor MODBUS
    """

    def __init__(self, host_ip, port) -> None:
        self.__server = ModbusServer(host=host_ip, port=port, no_block=True)
        self.__db = DataBank()
        self.__builder = BinaryPayloadBuilder()
        self.teste = "teste string"

    def run(self):
        try:
            self.__server.start()
            print("Servidor MODBUS em execução")
            while True:
                self.__builder.add_32bit_float(random.uniform(400 * 0.95, 400 * 1.05))
                self.__builder.add_string(self.teste)

                registers = self.__builder.to_registers()

                self.__db.set_words(address=1000, word_list=registers)
                print(30 * "=")
                print("Tabela MODBUS")

                decoder = BinaryPayloadDecoder.fromRegisters(registers)

                print("Holdind Register")
                print(f" R1000 float = {round(decoder.decode_32bit_float(), 2)}")
                print(f" R1000 string = {decoder.decode_string(50).decode()}")

                registers = self.__db.get_words(address=2000, number=10)
                decoder = BinaryPayloadDecoder.fromRegisters(registers)
                print(f" R2000 = {decoder.decode_string(50).decode()}")

                registers = self.__db.get_words(address=3000, number=10)
                decoder = BinaryPayloadDecoder.fromRegisters(registers)
                print(f" R3000 = {round(decoder.decode_32bit_float(), 2)}")

                self.__builder.reset()
                sleep(1)

        except Exception as e:
            print("Erros -> ", end="")
            for error in e.args:
                print(error)
