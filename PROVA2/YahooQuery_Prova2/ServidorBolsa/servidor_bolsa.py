import json
import socket
from threading import Thread
from yahooquery import Ticker
from datetime import datetime


class ServidorBolsa:
    """
    Classe Servidor Multi Thread - API Yahoo Finance
    """

    def __init__(self, host, port) -> None:
        self.__host = host
        self.__port = port
        self.__thread_pool = {}
        self.__tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.__tcp.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    def start(self):
        """
        Configura e inicia o servidor MT
        """
        endpoint = (self.__host, self.__port)
        try:
            self.__tcp.bind(endpoint)
            self.__tcp.listen(1)
            print(f"Servidor foi iniciado em {self.__host}:{self.__port}")
            while True:
                conn, client = self.__tcp.accept()
                self.__thread_pool[client] = Thread(
                    target=self._service, args=(conn, client)
                )
                self.__thread_pool[client].start()

        except Exception as e:
            print("Erro ao inicializar o servidor: ", e.args)

    def _service(self, conn: socket.socket, client: socket.AddressInfo):
        """
        Método que fornece o serviço de dados de ações através
        da API do Yahoo Finance

        :param conn: objeto "socket" para enviar e receber dados
        :type conn: socket.socket
        :param client: endereço e porta do cliente
        :type client: socket.AddressInfo
        """
        print("Atendendo cliente ", client)
        while True:
            try:
                msg_bytes = conn.recv(8192)
                simbolo = str(msg_bytes.decode()).strip().upper()
                papel = Ticker(simbolo)
                data_ex = papel.summary_detail[simbolo]["exDividendDate"]
                date_ex = datetime.strptime(data_ex, "%Y-%m-%d %H:%M:%S").strftime(
                    "%d/%m/%Y"
                )
                dados = {
                    "data_ex": data_ex,
                }
                resp = json.dumps(dados)

                conn.send(resp.encode())
                print(client, " -> requisição atendida")

            except OSError as e:
                print(f"Erro na conexão: {client}: {e.args}")
                return

            except Exception as e:
                print(f"Erro nos dados recebidos: {client}: {e.args}")
                conn.send("Erro na codificação".encode())
