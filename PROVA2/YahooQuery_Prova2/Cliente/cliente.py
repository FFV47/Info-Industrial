import json
import socket
import pandas as pd


class Cliente:
    """Classe Cliente - Calculadora Remota - API Socket
    """

    def __init__(self, server_ip, port) -> None:
        self.__server_ip = server_ip
        self.__port = port
        self.__tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def start(self):
        """Método que inicializa o cliente
        """
        endpoint = (self.__server_ip, self.__port)
        try:
            self.__tcp.connect(endpoint)
            print("Conexão bem-sucedida")
            self.__request()

        except Exception as e:
            print("Erro de conexão com o servidor: ", e.args)

    def __request(self):
        """Método que implementa as requisições do cliente
        """

        try:
            msg = ""
            while msg != "x":
                msg = str(input("Digite o codigo da empresa ('x' para sair): "))

                if msg == "":
                    continue
                elif msg == "x":
                    break

                self.__tcp.send(msg.encode())
                response = self.__tcp.recv(8192)
                dados = json.loads(response.decode())
                print("\nSumário\n")
                print(dados["sumario"])

                print(f"\nValor de mercado (capitalização) = $ {dados['mercado']:.2f}")
                print(f"\nCotação = $ {dados['cotacao']}")

                # Formatação do dataframe
                pd.options.display.float_format = "  {:.2f}".format
                hist = pd.read_json(dados["historico"])
                dates = pd.Series(
                    [
                        (string[22:]).replace("(", "").replace(")", "").replace(", ", "/")
                        for string in hist.index
                    ]
                )
                hist.set_index(dates, inplace=True)

                print("\nHistórico de preço da última semana\n")
                print(hist)
                print("")
            self.__tcp.close()

        except Exception as e:
            print("Erro de comunicação com o servidor: ", e.args)
