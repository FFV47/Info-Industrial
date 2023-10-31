#include "sensorvazao.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

using std::string;
using std::vector;

int main()
{
    vector<string> head
        = {"id", "unidade", "Numero de amostras", "Periodo de amostragem (s)"};

    string dadosCSV = (fs::current_path() / "dados.csv").string();

    SensorVazao sensor(dadosCSV, head);
    sensor.lerDados();
    // sensor.imprimeDados();

    string arquivo1 = (fs::current_path() / "sem-inicio.csv").string();
    string arquivo2 = (fs::current_path() / "sem-final.csv").string();
    string arquivo3 = (fs::current_path() / "meio.csv").string();

    sensor.salvarDados(arquivo1, "", "07:17:00");
    sensor.salvarDados(arquivo2, "07:33:18");
    sensor.salvarDados(arquivo3, "07:30:00", "07:32:00");

    SensorVazao sensor2(arquivo1, head);
    sensor2.lerDados();
    sensor2.imprimeDados();
    double valor;
    valor = sensor2.getDado("07:16:56");
    if (valor)
    {
        std::cout << "Valor encontrado: " << valor << '\n';
    }
    return 0;
}

// ofstream::open / ofstream::close
// #include <fstream> // std::ofstream

// int main()
// {

//     std::ofstream ofs;
//     ofs.open("test.txt", std::ofstream::out | std::ofstream::app);

//     ofs << "more lorem ipsum\n";
//     ofs << "Testando outra linha\n";
//     ofs << "Pulando duas linhas\n\n\n";
//     ofs << "Ultima linha";

//     ofs.close();

//     return 0;
// }