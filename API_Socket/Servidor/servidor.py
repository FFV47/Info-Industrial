import socket
import operator
import threading


class Servidor:
    """
    Classe Servidor - Calculadora Remota - API Socket
    """

    def __init__(self, host, port) -> None:
        self._host = host
        self._port = port
        self._tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def start(self):
        """
        Configura e inicia o servidor
        """
        endpoint = (self._host, self._port)
        try:
            self._tcp.bind(endpoint)
            self._tcp.listen(1)
            print(f"Servidor foi iniciado em {self._host}:{self._port}")
            while True:
                conn, client = self._tcp.accept()
                self._service(conn, client)

        except Exception as e:
            print("Erro ao inicializar o servidor: ", e.args)

    def _service(self, conn: socket.socket, client: socket.AddressInfo):
        """
        Método que implementa o serviço de calculadora remota

        :param conn: objeto "socket" para enviar e receber dados
        :type conn: socket.socket
        :param client: endereço e porta do cliente
        :type client: socket.AddressInfo
        """
        print("Atendendo cliente ", client)
        operadores = {
            "+": operator.add,
            "-": operator.sub,
            "*": operator.mul,
            "/": operator.truediv,
        }
        while True:
            try:
                msg = conn.recv(1024)
                msg_str = str(msg.decode()).strip()
                # Exemplo -> "15+10"
                for op in operadores:
                    if op in msg_str:
                        equation = msg_str.split(op)
                        response = operadores[op](
                            float(equation[0]), float(equation[1])
                        )
                        break
                else:
                    response = "Operador Inválido!"

                conn.send(str(response).encode())
                print(client, " -> requisição atendida")

            except OSError as e:
                print(f"Erro na conexão: {client}: {e.args}")
                return

            except Exception as e:
                print(f"Erro nos dados recebidos: {client}: {e.args}")
                conn.send("Erro na codificação".encode())


class ServidorMT(Servidor):
    """
    Servidor multi-thread

    :param Servidor: Servidor API Socket single-thread (Calculadora Remota)
    """

    def __init__(self, host, port) -> None:
        super().__init__(host, port)
        self.__thread_pool = {}

    def start(self):
        """
        Configura e inicia o servidor MT
        """
        endpoint = (self._host, self._port)
        try:
            self._tcp.bind(endpoint)
            self._tcp.listen(1)
            print(f"Servidor foi iniciado em {self._host}:{self._port}")
            while True:
                conn, client = self._tcp.accept()
                self.__thread_pool[client] = threading.Thread(
                    target=self._service, args=(conn, client)
                )
                self.__thread_pool[client].start()

        except Exception as e:
            print("Erro ao inicializar o servidor: ", e.args)
