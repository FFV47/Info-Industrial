from kivy.app import App
from kivy.uix.floatlayout import FloatLayout


class MyWidget(FloatLayout):
    def incrementar(self):
        self.ids["lb"].text = str(int(self.ids["lb"].text) + 1)


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
