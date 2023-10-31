import sqlite3
from threading import Lock


class DBHandler:
    def __init__(self, db_path, tag_names, tablename="dataTable"):
        self._tablename = tablename
        self._tag_names = tag_names
        self._conn = sqlite3.connect(db_path, check_same_thread=False)
        self._cursor = self._conn.cursor()
        self._lock = Lock()
        self.init_db()

    def init_db(self):
        """
        Cria a tabela na DB caso ela não exista
        """
        try:
            sql_real_cols = " REAL, ".join(self._tag_names)
            sql_real_cols += " REAL"
            sql_string = f"""
                CREATE TABLE IF NOT EXISTS {self._tablename} (
                    id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
                    timestamp TEXT NOT NULL,
                    {sql_real_cols}
                );
                """
            self._lock.acquire()
            self._cursor.execute(sql_string)
            self._conn.commit()
            self._lock.release()

        except Exception as e:
            print("Erro na criação da tabela -> ", e.args[0])

    def insert_data(self, data: dict):
        """
        Método para a inserção de dados na DBH

        :param data: Dados
        :type data: dict
        """
        try:
            data["timestamp"] = f"'{data['timestamp']}'"
            str_cols = ",".join(data.keys())
            str_values = ",".join([str(value) for value in data.values()])
            sql_string = f"""
                INSERT INTO {self._tablename} ({str_cols}) VALUES ({str_values});
            """
            self._lock.acquire()
            self._cursor.execute(sql_string)
            self._conn.commit()
            self._lock.release()
        except Exception as e:
            print("Erro na inserção de dados -> ", e.args[0])

    def select_data(self, init_date, final_date) -> "dict[str, list]":
        """
        Método que busca dados entre 2 horários
        """
        cols = ",".join(["timestamp", *self._tag_names])

        try:
            sql_string = f"""
                SELECT {cols} FROM {self._tablename} WHERE timestamp BETWEEN '{init_date}' AND '{final_date}';
            """
            self._lock.acquire()
            self._cursor.execute(sql_string)
            self._conn.commit()
            self._lock.release()
            selected_data = {
                "cols": cols.split(","),
                "data": [*self._cursor.fetchall()],
            }

            return selected_data
        except Exception as e:
            print("Erro na busca de dados -> ", e.args[0])
            return {}
