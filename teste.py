    def update_graph(self,button):
        if self.dialog_hist.content_cls.ids.realtime:
            self.graph_type = 'realtime'
        else:
            self.graph_type = 'hist'

        show_peso = self.dialog_hist.content_cls.ids.graph_peso.active
        show_R = self.dialog_hist.content_cls.ids.graph_R.active
        show_G = self.dialog_hist.content_cls.ids.graph_G.active
        show_B = self.dialog_hist.content_cls.ids.graph_B.active

        show_graphs = [show_R, show_G, show_B, show_peso]
        self._graph.update_graph_config(self.graph_type, show_graphs)