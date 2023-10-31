import sqlite3
from threading import Lock


class DBHandler:
    """
    Classe para manipulação do banco de dados
    """

    def __init__(self, dbpath, tags, tablename="dataTable"):
        self._dbpath = dbpath
        self._tablename = tablename
        self._conn = sqlite3.connect(self._dbpath, check_same_thread=False)
        self._cursor = self._conn.cursor()
        self._col_names = tags.keys()
        self._lock = Lock()
        self._create_table()

    def __del__(self):
        self._conn.close()

    def _create_table(self):
        sql_str = None
        try:
            sql_str = f"""
                CREATE TABLE IF NOT EXISTS {self._tablename} (
                    id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
                    timestamp TEXT NOT NULL,
            """
            for n in self._col_names:
                sql_str += f"{n} REAL,"
            sql_str = sql_str[:-1] + ");"

            self._lock.acquire()
            self._cursor.execute(sql_str)
            self._conn.commit()
            self._lock.release()

        except Exception as e:
            print(sql_str, end="\n\n")
            print("Erro na base da dados -> ", e.args[0])

    def _insert_data(self, data):
        try:
            self._lock.acquire()
            timestamp = str(data["timestamp"])
            str_cols = "timestamp," + ",".join(data["values"].keys())
            str_values = f"'{timestamp}'," + ",".join(
                [str(data["values"][k]) for k in data["values"].keys()]
            )
            sql_str = f"""
                INSERT INTO {self._tablename} ({str_cols}) VALUES ({str_values});
            """
            self._cursor.execute(sql_str)
            self._conn.commit()
        except Exception as e:
            print("Erro na escrita da base de dados -> ", e.args[0])
        finally:
            self._lock.release()

    def _select_data(self, cols, init_date, final_date):
        try:
            self._lock.acquire()

            sql_str = f"""
                SELECT {','.join(cols)} FROM {self._tablename} WHERE timestamp BETWEEN '{init_date}' AND '{final_date}';
            """
            dados = dict((sensor, []) for sensor in cols)

            self._cursor.execute(sql_str)
            for linha in self._cursor.fetchall():
                for dado in range(len(linha)):
                    dados[cols[dado]].append(linha[dado])
            self._lock.release()

            return dados
        except Exception as e:
            print("Erro de leitura da base de dados -> ", e.args[0])
