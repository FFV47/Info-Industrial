import threading
from collections import deque
import random
from time import sleep


class Processador:
    def __init__(self, numero_threads, numero_operacoes):
        self._cont = 0
        self._nop = numero_operacoes
        self._threadPool = []
        self._fila = deque()
        self.resultados = deque()
        self._nthreads = numero_threads
        self._operacoes_processadas = 0
        self._prod_active = True
        self._lock = threading.Lock()

    def __prod(self):
        for i in range(0, self._nop):
            self._fila.append([i, i])
        self._prod_active = False

    def __cons(self):
        while self._prod_active or len(self._fila) > 0:
            try:
                self._lock.acquire()
                if len(self._fila) > 0:
                    dado = self._fila.popleft()
                    self.resultados.append(dado[0] + dado[1])
                    self._operacoes_processadas += 1
                self._lock.release()
            except Exception as e:
                print("Erro: ", e.args)
            finally:
                if self._lock.locked():
                    self._lock.release()

    def run(self):
        self._prodThread = threading.Thread(target=self.__prod)
        self._prodThread.start()
        while len(self._fila) < self._nop / 10:
            pass
        for t in range(0, self._nthreads):
            self._threadPool.append(threading.Thread(target=self.__cons))
            self._threadPool[t].start()
        for th in self._threadPool:
            th.join()
        print("Total de operações processadas: ", self._operacoes_processadas)
