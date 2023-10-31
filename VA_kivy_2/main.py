from kivy.app import App
from kivy.uix.boxlayout import BoxLayout
from kivy.clock import Clock
from math import copysign


class MyWidget(BoxLayout):
    _vel = {"vel_x": 1, "vel_y": 1}

    def move(self, dt):
        self.ids.bola.x += self._vel["vel_x"]
        self.ids.bola.y += self._vel["vel_y"]
        if self.ids.bola.x < 0 or self.ids.bola.right > self.ids.valid_region.width:
            self._vel["vel_x"] *= -1
        if self.ids.bola.y < 0 or self.ids.bola.top > self.ids.valid_region.height:
            self._vel["vel_y"] *= -1

    def command(self):
        if self.ids.bt_move.text == "Mover":
            self._ev = Clock.schedule_interval(self.move, 1 / 60)
            self.ids.bt_move.text = "Parar"
        else:
            self._ev.cancel()
            self.ids.bt_move.text = "Mover"

    def speed(self):
        self._vel["vel_x"] = self.ids.slider.value * copysign(1, self._vel["vel_x"])
        self._vel["vel_y"] = self.ids.slider.value * copysign(1, self._vel["vel_y"])


class BasicApp(App):
    """
    Aplicativo básico Kivy
    """

    def build(self):
        """
        Construir Aplicativo
        """

        return MyWidget()


if __name__ == "__main__":
    BasicApp().run()
