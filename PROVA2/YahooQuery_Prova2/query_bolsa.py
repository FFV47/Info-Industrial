from yahooquery import Ticker
from datetime import datetime

simbolo = "TAEE11.SA"

papel = Ticker(simbolo)
data_ex = papel.summary_detail[simbolo]["exDividendDate"]
data_ex = datetime.strptime(data_ex, "%Y-%m-%d %H:%M:%S").strftime("%d/%m/%Y")

print(data_ex)
