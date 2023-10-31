#include "conta.h"
#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

Conta::Conta(const int senha,
             const int numero,
             const string &titular,
             const string &tipo,
             const double saldo)
    : numero_(numero),
      titular_(titular),
      tipo_(tipo),
      senha_(senha)
{

    if (saldo > 0)
    {
        saldo_ = saldo;
    }
    else
    {
        saldo_ = 0.0;
        std::cout << "Saldo inicial inválido!\nSaldo inicial será R$ 0,00\n";
    }
}

int Conta::getNumero() { return numero_; }

string Conta::getTitular() { return trimChar(titular_, '\"'); }

string Conta::getTipo() { return trimChar(tipo_, '\"'); }

double Conta::getSaldo(int senha)
{
    if (senha == senha_)
    {
        return saldo_;
    }
    else
    {
        std::cout << "Senha inválida!\n";
        return 1;
    }
}
void Conta::setSaldo(double valor) { saldo_ = valor; }

void Conta::setSenha(int senha) { senha_ = senha; }

bool Conta::validaSenha(int senha)
{
    if (senha_ != senha)
    {
        std::cout << "Senha inválida!";
        return false;
    }
    else
    {
        return true;
    }
}

void Conta::exibeDados()
{
    std::cout << "Titular: " << titular_ << '\n';
    std::cout << "Número: " << numero_ << '\n';
    std::cout << "Tipo: " << tipo_ << '\n';
}

string Conta::printCSV()
{
    string linha{};
    linha = linha + std::to_string(senha_) + ',' + std::to_string(numero_) + ','
            + '\"' + trimChar(titular_, '\"') + '\"' + ',' + '\"'
            + trimChar(tipo_, '\"') + '\"' + ',' + printFloat(saldo_, 2);
    return linha;
}

string Conta::trimChar(string campo, char caractere)
{
    campo.erase(std::remove(campo.begin(), campo.end(), caractere),
                campo.end());
    return campo;
}

string Conta::printFloat(double valor, int precisao)
{
    std::stringstream stream{};
    stream << std::fixed << std::setprecision(precisao) << valor;
    string s{stream.str()};
    return s;
}

void Conta::deposito(double valor)
{
    if (valor > 0)
    {
        saldo_ += valor;
    }
    else
    {
        std::cout << "Valor inválido!\n";
    }
}

void Conta::saque(int senha, double valor)
{
    if (senha == senha_)
    {
        if (valor < saldo_)
        {
            saldo_ -= valor;
            std::cout << "Saque de R$ " << valor << " realizado com sucesso\n";
        }
        else
        {
            std::cout << "Saldo insuficiente!\n";
        }
    }
    else
    {
        std::cout << "Senha inválida!\n";
    }
}

void Conta::transferencia(double valor, Conta *destino)
{
    if (valor < 0)
    {
        std::cout << "Valor inválido!\n";
    }
    else if (valor > saldo_)
    {
        std::cout << "Saldo insuficiente!\n";
    }
    else if (!destino)
    {
        std::cout << "Destinatário inválido!\n";
    }
    else
    {
        saldo_ -= valor;
        destino->saldo_ += valor;
        std::cout << "Transferencia de R$ " << valor << " realizada para "
                  << destino->titular_ << '\n';
    }
}
