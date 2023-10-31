#include "conta_corrente.h"
#include <string>

ContaCorrente::ContaCorrente(const int numero,
                             const int senha,
                             const string &titular,
                             const string &tipo,
                             const double saldo,
                             const unsigned long cartao)
    : Conta(numero, senha, titular, tipo, saldo),
      num_cartao_(cartao)
{}

string ContaCorrente::printCSV()
{
    string linha = Conta::printCSV();
    linha = linha + ',' + std::to_string(num_cartao_);
    return linha;
}

unsigned long ContaCorrente::getCartao() { return num_cartao_; }