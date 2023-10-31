from threading import Thread, Lock


class Contador:
    def __init__(self, n_threads, max_count) -> None:
        self.__count = 0
        self.__max_count: int = max_count
        self.__thread_pool: list[Thread] = []
        self.__n_threads: int = n_threads
        self.__lock = Lock()

    def incremento(self):
        n = 0
        self.__lock.acquire()
        while n < self.__max_count:
            self.__count += 1
            n += 1
        self.__lock.release()

    def run(self):
        for t in range(self.__n_threads):
            self.__thread_pool.append(Thread(target=self.incremento))
            self.__thread_pool[t].start()

        for thread in self.__thread_pool:
            thread.join()

        print(f"Resultado obtido = {self.__count}")
        print(f"Resultado esperado = {self.__n_threads * self.__max_count}")
