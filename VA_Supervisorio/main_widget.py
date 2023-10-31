import random
from datetime import datetime
from threading import Thread
from time import sleep

from kivy.core.window import Window
from kivy.uix.boxlayout import BoxLayout
from kivy_garden.graph import LinePlot
from pyModbusTCP.client import ModbusClient

from db_handler import DBHandler
from popups import DataGraphPopup, HistGraphPopup, ModbusPopup, ScanPopup
from timeseriesgraph import TimeSeriesGraph


class MainWidget(BoxLayout):
    """
    Classe com o aplicativo
    """

    _update_thread = None
    _update_widgets = True
    _tags = {}
    _max_points = 20

    def __init__(self, **kwargs):
        super().__init__()
        self._scan_time = kwargs["scan_time"]
        self._server_ip = kwargs["server_ip"]
        self._server_port = kwargs["server_port"]
        self._modbus_popup = ModbusPopup(self._server_ip, self._server_port)
        self._scan_popup = ScanPopup(self._scan_time)
        self._client = ModbusClient(host=self._server_ip, port=self._server_port)
        self._measures = {}
        self._measures["timestamp"] = None
        self._measures["values"] = {}

        for key, value in kwargs["modbus_addrs"].items():
            if key == "fornalha":
                plot_color = (1, 0, 0, 1)
            else:
                plot_color = (random.random(), random.random(), random.random(), 1)

            self._tags[key] = {"addr": value, "color": plot_color}

        self._graph = DataGraphPopup(
            xmax=self._max_points, plot_color=self._tags["fornalha"]["color"]
        )
        self._hist_graph = HistGraphPopup(tags=self._tags)
        self._db = DBHandler(kwargs["db_path"], self._tags)

    def start_data_read(self, ip, port):
        """
        Método para a configuração do IP e porta do servidor MODBUS e inicializar uma thread para a leitura dos dados da interface gráfica
        """
        self._server_ip = ip
        self._server_port = port
        self._client.host = self._server_ip
        self._client.port = self._server_port
        try:
            Window.set_system_cursor("wait")
            self._client.open()
            Window.set_system_cursor("arrow")
            if self._client.is_open():
                # Separa a interface do gerenciamento de dados
                self._update_thread = Thread(target=self._updater)
                self._update_thread.start()
                self.ids.img_con.source = "imgs/conectado.png"
                self._modbus_popup.dismiss()
            else:
                self._modbus_popup.set_info("Falha na conexão com o servidor")
        except Exception as e:
            print("Erro de conexão ->", e.args[0])

    def _updater(self):
        """
        Método que invoca as rotinas de leitura dos dados, atualização da interface e inserção dos dados no banco de dados
        """
        try:
            while self._update_widgets:
                # ler os dados
                self._read_data()
                # atualizar a interface
                self._update_gui()
                # gravar no banco de dados
                self._db._insert_data(self._measures)
                sleep(self._scan_time / 1000)
        except Exception as e:
            print("Erro -> ", e.args[0])

    def _read_data(self):
        """
        Método para a leitura dos dados
        """
        self._measures["timestamp"] = datetime.now().replace(microsecond=0)
        for key, value in self._tags.items():
            self._measures["values"][key] = self._client.read_holding_registers(
                value["addr"], 1
            )[0]

    def _update_gui(self):
        """
        Método para atualizar a GUI
        """
        # Atualiza as temperaturas
        for key in self._tags.keys():
            self.ids[key].text = str(self._measures["values"][key]) + " ºC"

        # Atualiza o nível do termometro
        self.ids.lb_temp.size = (
            self.ids.lb_temp.size[0],
            (self._measures["values"]["fornalha"]) / 450 * self.ids.termometro.size[1],
        )
        # Atualiza o gráfico
        self._graph.ids.graph.updateGraph(
            (self._measures["timestamp"], self._measures["values"]["fornalha"]), 0
        )

    def stop_refresh(self):
        self._update_widgets = False

    def get_data_db(self):
        """
        Coleta as informacoes da interface fornecidas pelo usuário e requisita a
        busca na DB
        """
        try:
            init_date = self._parse_DT_string(self._hist_graph.ids.txt_init_time.text)
            final_date = self._parse_DT_string(self._hist_graph.ids.txt_final_time.text)

            cols = []
            for sensor in self._hist_graph.ids.sensores.children:
                if sensor.ids.check_box.active:
                    cols.append(sensor.id)

            if init_date is None or final_date is None or len(cols) == 0:
                return

            cols.append("timestamp")

            dados = self._db._select_data(cols, init_date, final_date)

            if dados is None or len(dados["timestamp"]) == 0:
                return

            self._hist_graph.ids.graph.clearPlots()

            for key, value in dados.items():
                if key == "timestamp":
                    continue
                p = LinePlot(line_width=1.5, color=self._tags[key]["color"])
                p.points = [(x, value[x]) for x in range(len(value))]
                self._hist_graph.ids.graph.add_plot(p)

            self._hist_graph.ids.graph.xmax = len(dados[cols[0]])
            self._hist_graph.ids.graph.update_x_labels(
                [datetime.strptime(x, "%Y-%m-%d %H:%M:%S") for x in dados["timestamp"]]
            )

        except Exception as e:
            print("Erro na coleta de dados -> ", e.args[0])

    def _parse_DT_string(self, datetime_string):
        """
        Converte a string inserida pelo usuário para o formato utilizado na
        busca dos dados na DB
        """
        try:
            date = datetime.strptime(datetime_string, "%d/%m/%Y %H:%M:%S")
            return date.strftime("%Y-%m-%d %H:%M:%S")
        except Exception as e:
            print("Erro na conversão de data ->", e.args[0])
