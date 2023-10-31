from pyModbusTCP.client import ModbusClient
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

                if select == 1:
                    tipo = int(
                        input(
                            "Qual tipo de dado deseja ler\n 1 -> Holding Register\n 2 -> Coil\n 3 -> Input Register\n 4 -> Input Discrete\n Escolha = "
                        )
                    )

                    address = int(input("Digite o endereço da tabela MODBUS: "))
                    n = int(input("Digite o número de vezes que deseja ler: "))

                    for i in range(n):
                        print(f"Leitura {i+1}: {self.__lerDado(tipo, address)}")
                        sleep(1)

                elif select == 2:
                    tipo = int(
                        input(
                            "Qual tipo de dado deseja escrever\n 1 -> Holding Register\n 2 -> Coil\n Escolha = "
                        )
                    )

                    address = int(input("Digite o endereço da tabela MODBUS: "))
                    valor = int(input("Digite o valor que deseja escrever: "))
                    self.__escreveDado(tipo, address, valor)

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
            print("Erro -> ", e.args)

    def __lerDado(self, tipo: int, address: int):
        """
        Método de leitura da tabela MODBUS
        """
        if tipo == 1:
            return self.__client.read_holding_registers(address, 1)[0]  # type:ignore
        elif tipo == 2:
            return self.__client.read_coils(address, 1)[0]  # type: ignore
        elif tipo == 3:
            return self.__client.read_input_registers(address, 1)[0]  # type: ignore
        elif tipo == 4:
            return self.__client.read_discrete_inputs(address, 1)[0]  # type: ignore

    def __escreveDado(self, tipo: int, address: int, valor: int):
        """
        Método para escrita na tabela MODBUS
        """
        if tipo == 1:
            return self.__client.write_single_register(address, valor)

        elif tipo == 2:
            return self.__client.write_single_coil(address, valor)
