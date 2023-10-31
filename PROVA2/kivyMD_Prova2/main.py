from kivymd.app import MDApp
from kivymd.uix.screen import MDScreen
from orm_engine import init_db
from models import Table


class MyWidget(MDScreen):
    def __init__(self):
        super().__init__()
        Session = init_db("database/data.db")
        self._session = Session()

    def register(self):
        product = self.ids.product.text
        brand = self.ids.brand.text
        stock = str(self.ids.stock.text)
        try:
            data = Table(product=product, brand=brand, stock=stock)
            self._session.add(data)
            self._session.commit()
            self.ids.product.text = ""
            self.ids.brand.text = ""
            self.ids.stock.text = ""
        except Exception as e:
            print("Erro na base de dados: ", e.args[0])


class BasicApp(MDApp):
    def build(self):
        return MyWidget()


if __name__ == "__main__":
    BasicApp().run()
