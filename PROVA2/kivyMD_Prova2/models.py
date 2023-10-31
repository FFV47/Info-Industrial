from sqlalchemy.schema import Column
from sqlalchemy.types import Text, Integer
from sqlalchemy.ext.declarative import declarative_base

Base = declarative_base()


class Table(Base):
    """
    Modelo de dados CLP
    """

    __tablename__ = "dataTable"
    id = Column(Integer, primary_key=True, index=True)
    product = Column(Text)
    brand = Column(Text)
    stock = Column(Text)

    def __repr__(self):
        return "<Table(id=%s, product=%s)>" % (self.id, self.product)
