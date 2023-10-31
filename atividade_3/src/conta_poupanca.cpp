#include "conta_poupanca.h"
#include <iomanip>
#include <ios>
#include <iostream>
#include <string>

ContaPoupanca::ContaPoupanca(const int senha,
                             const int numero,
                             const string &titular,
                             const string &tipo,
                             const double saldo,
                             const double taxa)
    : Conta(senha, numero, titular, tipo, saldo),
      taxa_rend_(taxa)
{}

void ContaPoupanca::simulaRendimento(const unsigned int num_meses)
{
    double rendimento = Conta::getSaldo(Conta::senha_);
    double saldo_inicial = rendimento;

    // Juros Composto
    for (unsigned int i{}; i < num_meses; i++)
    {
        rendimento *= (1 + taxa_rend_);
    }
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\nSaldo inicial R$ " << saldo_inicial << '\n';
    std::cout << "Em " << num_meses << " meses você terá R$ " << rendimento
              << '\n';
    std::cout << "Rendimento de R$ " << rendimento - saldo_inicial << "\n\n";
}

string ContaPoupanca::printCSV()
{
    string linha = Conta::printCSV();
    linha = linha + ',' + Conta::printFloat(taxa_rend_, 4);
    return linha;
}

double ContaPoupanca::getTaxa() { return taxa_rend_; }