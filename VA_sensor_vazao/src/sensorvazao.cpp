#include "sensorvazao.h"

SensorVazao::SensorVazao(const string &path, const vector<string> &header)
    : id_("desconhecido"),
      unidade_("desconhecida"),
      numMed_(0)
{
    headers_.assign(header.begin(), header.end());
    abrirArquivo(path);
}

SensorVazao::~SensorVazao() { file_.close(); }

bool SensorVazao::abrirArquivo(const string &path)
{
    try
    {
        file_.open(path);
        return true;
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << '\n';
        return false;
    }
}

bool SensorVazao::lerDados()
{
    try
    {
        if (file_.is_open())
        {
            //* Leitura do cabeçalho do arquivo

            string lineRead{};
            std::getline(file_, lineRead); // descarta a primeira linha
            vector<string> dadosHeader(headers_.size());

            int n{}, idx{};
            for (string &dado : dadosHeader)
            {
                std::getline(file_, lineRead);
                idx = lineRead.find(":");
                // compara o header do arquivo com o do objeto
                if (lineRead.substr(0, idx) == headers_[n])
                {
                    dado = lineRead.substr(idx + 1);
                }
                else
                {
                    std::cout << "Erro de leitura do cabeçalho\n";
                    return false;
                }
                n++;
            }
            id_ = dadosHeader[0];
            unidade_ = dadosHeader[1];
            numMed_ = std::stoi(dadosHeader[2]);
            Ts_ = std::stoi(dadosHeader[3]);

            //* Leitura dos dados

            std::getline(file_, lineRead); // descarta linha acima dos dados
            Medicao fileData;

            for (int i{}; i < numMed_; i++)
            {
                std::getline(file_, lineRead);
                idx = lineRead.find(",");
                fileData.horario = lineRead.substr(0, idx);
                fileData.valor = std::stod(lineRead.substr(idx + 1));
                dados_.push_back(fileData);
            }
        }
        else
        {
            std::cout << "Arquivo não está aberto\n";
            return false;
        }
    }
    catch (const std::exception &e)
    {
        std::cout << "Arquivo corrompido - Erro: " << e.what() << '\n';
    }
    return true;
}

void SensorVazao::imprimeDados()
{
    std::cout << "Sensor vazão\n";
    std::cout << "ID: " << id_ << '\n';
    std::cout << "Número de amostras: " << numMed_ << '\n';
    std::cout << "Período de Amostragem: " << Ts_ << '\n';

    for (const Medicao &dado : dados_)
    {
        std::cout << "Horário: " << dado.horario
                  << " h / Valor = " << dado.valor << " " << getUnidade()
                  << '\n';
    }
}

string SensorVazao::getID() { return id_; }

string SensorVazao::getUnidade() { return unidade_; }

int SensorVazao::getNumMed() { return numMed_; }

int SensorVazao::getPeriodoAmostragem() { return Ts_; }

double SensorVazao::getDado(const string &horario)
{
    for (const Medicao &dado : dados_)
    {
        if (dado.horario == horario)
        {
            return dado.valor;
        }
    }
    std::cout << "Valor não encontrado para essa hora\n";
    return 0.0;
}

int SensorVazao::salvarDados(const string &path,
                             const string &inicio,
                             const string &final)
{
    try
    {
        std::ofstream outFile;
        outFile.open(path, std::ofstream::out | std::ofstream::trunc);
        if (!outFile.is_open())
        {
            return -1;
        }
        string tempString{};
        int numDados{};

        bool beginFlag = false;
        for (const Medicao &dado : dados_)
        {

            if ((dado.horario == inicio && !beginFlag)
                || (inicio.empty() && !beginFlag))
                beginFlag = true;

            if (beginFlag)
            {
                tempString += dado.horario;
                tempString += ',';
                tempString += std::to_string(int(dado.valor));
                tempString += '\n';
                numDados++;
            }

            if (dado.horario == final)
                break;
        }
        outFile << "Dados salvos do sensor de vazão\n";
        outFile << "id:" << id_ << '\n';
        outFile << "unidade:" << unidade_ << '\n';
        outFile << "Numero de amostras:" << numDados << '\n';
        outFile << "Periodo de amostragem (s):" << Ts_ << '\n';
        outFile << "Horario,dado" << '\n';
        outFile << tempString;
        outFile.close();

        string arquivo = path.substr(path.rfind("/") + 1);
        std::cout << "Arquivo " << arquivo << " gravado com sucesso!\n";
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << '\n';
        return 1;
    }
}