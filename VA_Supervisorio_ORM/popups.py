from kivy.uix.boxlayout import BoxLayout
from kivy.uix.label import Label
from kivy.uix.popup import Popup
from kivy_garden.graph import LinePlot


class ModbusPopup(Popup):
    """
    Popup da configuração do protocoloco MODBUS
    """

    _info_lb = None

    def __init__(self, server_ip, server_port, **kwargs):
        super().__init__(**kwargs)
        self.ids.txt_ip.text = str(server_ip)
        self.ids.txt_port.text = str(server_port)

    def set_info(self, message):
        self._info_lb = Label(text=message)
        self.ids.layout.add_widget(self._info_lb)

    def clear_info(self):
        if self._info_lb is not None:
            self.ids.layout.remove_widget(self._info_lb)


class ScanPopup(Popup):
    """
    Popup da configuração do tempo de varredura
    """

    def __init__(self, scan_time, **kwargs):
        super().__init__()
        self.ids.txt_scan_time.text = str(scan_time)


class DataGraphPopup(Popup):
    def __init__(self, xmax, plot_color, **kwargs):
        super().__init__()
        self.plot = LinePlot(line_width=1.5, color=plot_color)
        self.ids.graph.add_plot(self.plot)
        self.ids.graph.xmax = xmax


class LabeledCheckBoxDataGraph(BoxLayout):
    pass


class HistGraphPopup(Popup):
    def __init__(self, **kwargs):
        super().__init__()
        for key, value in kwargs["tags"].items():
            cb = LabeledCheckBoxHistGraph()
            cb.ids.label.text = key
            cb.ids.label.color = value["color"]
            cb.id = key
            self.ids.sensores.add_widget(cb)


class LabeledCheckBoxHistGraph(BoxLayout):
    pass
