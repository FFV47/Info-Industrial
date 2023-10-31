from modulo_persistencia import ModbusPersistencia


def main():
    tags_addrs = {
        "temperatura": 1000,
        "pressao": 1001,
        "umidade": 1002,
        "consumo": 1003,
    }
    mod = ModbusPersistencia("localhost", 40000, tags_addrs)
    mod.create_data.start()
    mod.access_history()


if __name__ == "__main__":
    main()
