from .servidor import ServidorMT

server = ServidorMT("localhost", 40001)

server.start()
