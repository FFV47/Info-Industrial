#ifndef DADOS_CONTA_H
#define DADOS_CONTA_H

#include <string>

struct Cliente
{
    int senha;
    int numero;
    std::string titular;
    std::string tipo;
    double saldo;
};

struct clienteCorrente : Cliente
{
    int cartao;
};

struct clientePoupanca : Cliente
{
    double taxa;
};

#endif // DADOS_CONTA_H