from kivy.app import App
from kivy.lang.builder import Builder

from main_widget import MainWidget


class MainApp(App):
    """
    Classe do aplicativo
    """

    def build(self):
        self._widget = MainWidget(
            scan_time=1000,
            server_ip="127.0.0.1",
            server_port=40000,
            modbus_addrs={
                "fornalha": 1000,
                "gas_ref": 1001,
                "gasolina": 1002,
                "nafta": 1003,
                "querosene": 1004,
                "diesel": 1005,
                "oleo_lub": 1006,
                "oleo_comp": 1007,
                "residuos": 1008,
            },
            db_path="database/scada.db",
        )
        return self._widget

    def on_stop(self):
        self._widget.stop_refresh()
        return super().on_stop()


if __name__ == "__main__":
    Builder.load_file("main_widget.kv")
    Builder.load_file("popups.kv")
    MainApp().run()
