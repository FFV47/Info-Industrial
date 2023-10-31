from pyModbusTCP.client import ModbusClient
from pymodbus.payload import BinaryPayloadBuilder, BinaryPayloadDecoder
from typing import Union
from time import sleep


class ClienteMODBUS:
    """
    Cliente MODBUS
    """

    def __init__(self, server_ip, port) -> None:
        self.__client = ModbusClient(host=server_ip, port=port)
        self.__scan_time = 1

    def atendimento(self):
        """
        Método para atendimento do usuário
        """

        self.__client.open()

        try:
            atendimento = True
            while atendimento:
                select = int(
                    input(
                        "Deseja realizar uma leitura, escrita ou configuração?\n 1 -> Leitura\n 2 -> Escrita\n 3 -> Configuração\n 4 -> Sair\n Escolha = "
                    )
                )

                # * LEITURA
                if select == 1:
                    tipo = int(
                        input(
                            "Qual tipo de dado deseja ler\n 1 -> Holding Register\n 2 -> Coil\n 3 -> Input Register\n 4 -> Input Discrete\n Escolha = "
                        )
                    )

                    if tipo == 1:
                        complexo = int(
                            input(
                                "Tipo de dado\n 0 -> simples (int)\n 1 -> string\n 2 -> float\n Escolha = "
                            )
                        )
                    else:
                        complexo = 0

                    address = int(input("Digite o endereço da tabela MODBUS: "))
                    n = int(input("Digite o número de vezes que deseja ler: "))

                    if complexo:
                        for i in range(n):
                            print(
                                f"Leitura {i+1}: {self.__lerDadoComplexo(address, complexo)}"
                            )
                            sleep(1)
                    else:
                        for i in range(n):
                            print(f"Leitura {i+1}: {self.__lerDado(tipo, address)}")
                            sleep(1)

                # * ESCRITA
                elif select == 2:
                    tipo = int(
                        input(
                            "Qual tipo de dado deseja escrever\n 1 -> Holding Register\n 2 -> Coil\n Escolha = "
                        )
                    )

                    if tipo == 1:
                        complexo = int(
                            input(
                                "Tipo de dado\n 0 -> simples (int)\n 1 -> complexo (float, string)\n Escolha = "
                            )
                        )
                    else:
                        complexo = 0

                    address = int(input("Digite o endereço da tabela MODBUS: "))
                    valor = input("Digite o valor que deseja escrever: ")

                    if complexo:
                        try:
                            valor = float(valor)
                        except ValueError:
                            valor = str(valor)
                    else:
                        valor = int(valor)

                    self.__escreveDado(tipo, address, valor)

                # * CONFIGURAÇÃO
                elif select == 3:
                    self.__scan_time = float(
                        input("Digite o tempo de varredura desejado [s]: ")
                    )
                elif select == 4:
                    self.__client.close()
                    atendimento = False
                else:
                    print("Seleção inválida!")

        except Exception as e:
            print("Erro -> ", end="")
            for error in e.args:
                print(error)

    def __lerDado(self, tipo: int, address: int):
        """
        Método de leitura da tabela MODBUS
        """
        if tipo == 1:
            # Retorna a lista de registradores
            return self.__client.read_holding_registers(address)[0]  # type:ignore
        elif tipo == 2:
            return self.__client.read_coils(address)[0]  # type: ignore
        elif tipo == 3:
            return self.__client.read_input_registers(address)[0]  # type: ignore
        elif tipo == 4:
            return self.__client.read_discrete_inputs(address)[0]  # type: ignore

    def __lerDadoComplexo(self, address: int, complexo: int):
        """
        Método de leitura de "floats" e "strings" da tabela MODBUS
        """
        # Retorna a lista de registradores
        request = self.__client.read_holding_registers(address, 10)
        request = [x for x in request if x != 0]  # type: ignore

        # string
        if complexo == 1:
            decoder = BinaryPayloadDecoder.fromRegisters(request)
            # A decodificação tem que ser na mesma ordem de gravação do buffer no servidor. Para alcançar a string tem que decodificar os valores anteriores
            if address == 1000:
                decoder.decode_32bit_float()
            return decoder.decode_string(50).decode()
        # float
        elif complexo == 2:
            decoder = BinaryPayloadDecoder.fromRegisters(request)
            return round(decoder.decode_32bit_float(), 2)
        else:
            return "Escolha inválida!"

    def __escreveDado(self, tipo: int, address: int, valor: Union[int, float, str]):
        """
        Método para escrita na tabela MODBUS
        """
        # Holding Register
        if tipo == 1:
            if isinstance(valor, int):
                return self.__client.write_single_register(address, valor)

            builder = BinaryPayloadBuilder()
            if isinstance(valor, str):
                builder.add_string(valor)
            else:
                builder.add_32bit_float(valor)
            registers = builder.to_registers()
            self.__client.write_multiple_registers(address, registers)
        elif tipo == 0:
            self.__client.write_single_coil(address, valor)
        else:
            raise Exception("Escolha inválida")
