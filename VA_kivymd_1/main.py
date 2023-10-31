from kivymd.app import MDApp
from kivymd.uix.screen import MDScreen
from kivymd.uix.snackbar import Snackbar
from datacards import CardInputRegister, CardHoldingRegister, CardCoil
from pyModbusTCP.client import ModbusClient
from kivy.clock import Clock


class MyWidget(MDScreen):
    def __init__(self, tags, **kwargs):
        super().__init__(**kwargs)
        self._tags = tags
        self._client = ModbusClient()
        for tag in self._tags:
            if tag["type"] == "input":
                self.ids.modbus_data.add_widget(CardInputRegister(tag, self._client))
            elif tag["type"] == "holding":
                self.ids.modbus_data.add_widget(CardHoldingRegister(tag, self._client))
            elif tag["type"] == "coil":
                self.ids.modbus_data.add_widget(CardCoil(tag, self._client))

    def connect(self):
        if self.ids.bt_connect.text == "CONECTAR":
            try:
                self._client.host(self.ids.hostname.text)
                self._client.port(int(self.ids.port.text))
                self._client.open()
                if not self._client.is_open():
                    raise Exception("Can't connect to server")
                Snackbar(text="Conexão realizada com sucesso").show()
                self._ev = []
                for card in self.ids.modbus_data.children:
                    if card.tag["type"] == "holding" or card.tag["type"] == "coil":
                        self._ev.append(Clock.schedule_once(card.update_data))
                    else:
                        self._ev.append(Clock.schedule_interval(card.update_data, 1))
                self.ids.bt_connect.text = "DESCONECTAR"
            except Exception as e:
                print("Erro ao realizar a conexão com o servidor -> ")
                for e in e.args:
                    print(e)
        else:
            for event in self._ev:
                event.cancel()
            self._client.close()
            Snackbar(text="Cliente desconectado").show()
            self.ids.bt_connect.text = "CONECTAR"


class BasicApp(MDApp):
    _tags = [
        {
            "name": "tempForno",
            "description": "Temperatura Forno",
            "unit": "ºC",
            "address": 1000,
            "type": "input",
        },
        {
            "name": "setPoint",
            "description": "Temperatura Desejada",
            "unit": "ºC",
            "address": 2000,
            "type": "holding",
        },
        {
            "name": "status",
            "description": "Estado atuador",
            "unit": "ºC",
            "address": 1000,
            "type": "coil",
        },
    ]

    def build(self):
        self.theme_cls.primary_pallete = "Blue"
        self.theme_cls.primary_hue = "500"
        self.theme_cls.accent_pallete = "Blue"
        return MyWidget(self._tags)


if __name__ == "__main__":
    BasicApp().run()
