#include "conta.h"
#include <iostream>
#include <ostream>
#include <string>

Conta::Conta()
{
    m_numero = 0;
    m_senha = 1111;
    m_titular = "Nenhum";
    m_tipo = "Corrente";
    m_saldo = 0;
    std::cout << "Contrutor padrão invocado\n";
}

Conta::Conta(int numero, int senha, string titular, string tipo, double saldo)
{
    m_numero = numero;
    m_senha = senha;
    m_titular = titular;
    m_tipo = tipo;
    if (saldo > 0)
    {
        m_saldo = saldo;
    }
    else
    {
        m_saldo = 0.0;
        std::cout << "Saldo inicial inválido!\nSaldo inicial será R$ 0,00\n";
    }
}

void Conta::exibeDados()
{
    std::cout << "Titular: " << m_titular << '\n';
    std::cout << "Número: " << m_numero << '\n';
    std::cout << "Tipo: " << m_tipo << '\n';
}

double Conta::getSaldo(int senha)
{
    if (senha == m_senha)
    {
        return m_saldo;
    }
    else
    {
        std::cout << "Senha inválida!\n";
        return 1;
    }
}

void Conta::setSaldo(double valor)
{
    m_saldo = valor;
}

void Conta::setSenha(int senha)
{
    m_senha = senha;
}

void Conta::deposito(double valor)
{
    if (valor > 0)
    {
        m_saldo += valor;
    }
    else
    {
        std::cout << "Valor inválido!\n";
    }
}

void Conta::saque(int senha, double valor)
{
    if (senha == m_senha)
    {
        if (valor < m_saldo)
        {
            m_saldo -= valor;
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
    else if (valor > m_saldo)
    {
        std::cout << "Saldo insuficiente!\n";
    }
    else if (!destino)
    {
        std::cout << "Destinatário inválido!\n";
    }
    else
    {
        m_saldo -= valor;
        destino->m_saldo += valor;
        std::cout << "Transferencia de R$ " << valor << " realizada para " << destino->m_titular << '\n';
    }
}