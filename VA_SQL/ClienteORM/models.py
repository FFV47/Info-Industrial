from db_settings import Base
from sqlalchemy.schema import Column
from sqlalchemy.sql.sqltypes import Integer, DateTime


class DadoCLP(Base):
    """
    Modelo de dados CLP
    """

    __tablename__ = "dadoclp"
    id = Column(Integer, primary_key=True, index=True)
    timestamp = Column(DateTime)
    temperatura = Column(Integer)
    pressao = Column(Integer)
    umidade = Column(Integer)
    consumo = Column(Integer)

    def get_attributes(self):
        return [
            self.id,
            self.timestamp.strftime("%d/%m/%Y %H:%M:%S"),
            self.temperatura,
            self.pressao,
            self.umidade,
            self.consumo,
        ]

    def __repr__(self):
        return (
            "<DadoCLP(timestamp=%s, temperatura=%s, pressao=%s, umidade=%s, consumo=%s)>"
            % (
                self.timestamp,
                self.temperatura,
                self.pressao,
                self.umidade,
                self.consumo,
            )
        )
