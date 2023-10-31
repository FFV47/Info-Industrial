from sqlalchemy.schema import Column
from sqlalchemy.types import DateTime, Float, Integer
from sqlalchemy.ext.declarative import declarative_base

Base = declarative_base()


class DadoCLP(Base):
    """
    Modelo de dados CLP
    """

    __tablename__ = "dadoclp"
    id = Column(Integer, primary_key=True, index=True)
    timestamp = Column(DateTime)
    fornalha = Column(Float)
    gas_ref = Column(Float)
    gasolina = Column(Float)
    nafta = Column(Float)
    querosene = Column(Float)
    diesel = Column(Float)
    oleo_lub = Column(Float)
    oleo_comp = Column(Float)
    residuos = Column(Float)

    def __repr__(self):
        return "<DadoCLP(id=%s, timestamp=%s)>" % (self.id, self.timestamp,)
