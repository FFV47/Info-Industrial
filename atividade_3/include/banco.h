#ifndef BANCO_H
#define BANCO_H

#include "conta_corrente.h"
#include "conta_poupanca.h"
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

using std::ifstream;
using std::string;
using std::vector;

namespace fs = std::filesystem;

class Banco
{
  public:
    Banco(const fs::path &path, const string &header, const int senha);
    ~Banco();
    // Auxiliares
    Conta *buscaConta(int numero);
    bool validaGerente(int senha);
    vector<string> splitString(const string &linha);

    // Inicialização
    void abrirArquivo(const fs::path &path);
    void lerContasArquivo();

    // Gerente
    void exibirContas();
    void cadastrarConta();
    void salvarContas();

    // Atendimento
    void atendimentoGeral();
    void atendimentoGerente();
    void atendimentoCliente();
    void atendimentoCorrente(ContaCorrente *cliente);
    void atendimentoPoupanca(ContaPoupanca *cliente);

  private:
    string header_;
    int senha_gerente_;
    int num_contas_;
    Conta **contas_;
    ifstream arquivo_input_;
};

#endif // BANCO_H