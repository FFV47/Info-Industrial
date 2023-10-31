#include "banco.h"
#include "conta.h"
#include <iostream>

Banco::Banco()
{
    m_contas[0] = {1234, 1, "Jose", "Corrente", 300};
    m_contas[1] = {1234, 2, "João", "Poupança", 800};
    m_contas[2] = {1234, 3, "Maria", "Corrente", 1000};
    m_contas[3] = {1234, 4, "Madalena", "Poupança", 2000};
}

Banco::~Banco()
{
}

Conta *Banco::buscaConta(int numero)
{
    for (int i = 0; i < MAX_CONTAS; i++)
    {
        if (numero == m_contas[i].m_numero)
        {
            return &m_contas[i];
        }
    }
    return nullptr;
}

void Banco::atendimento()
{
    Conta *contaCliente;
    int numConta, senhaIn;
    bool atend = true;

    std::cout << "Bem-vindo ao sistema de atendimento do banco\n";
    std::cout << "Digite o número da conta: ";
    std::cin >> numConta;
    contaCliente = buscaConta(numConta);

    if (contaCliente == nullptr)
    {
        std::cout << "Conta inválida!\n";
    }
    else
    {
        std::cout << "Digite sua senha: ";
        std::cin >> senhaIn;
        if (contaCliente->validaSenha(senhaIn))
        {
            std::cout << "\nOlá, " << contaCliente->m_titular << '\n';
            while (atend)
            {
                int opção;
                double valor;
                std::cout << "Menu de operações\n";
                std::cout << "1 - Saque\n";
                std::cout << "2 - Depósito\n";
                std::cout << "3 - Ver Saldo\n";
                std::cout << "4 - Voltar ao Menu Inicial\n";
                std::cout << "5 - Sair\n";
                std::cout << "Opção escolhida: ";
                std::cin >> opção;
                switch (opção)
                {
                case 1:
                    std::cout << "Digite o valor do saque: ";
                    std::cin >> valor;
                    contaCliente->saque(senhaIn, valor);
                    std::cout << '\n';
                    break;
                case 2:
                    std::cout << "Digite o valor do depósito: ";
                    std::cin >> valor;
                    contaCliente->deposito(valor);
                    std::cout << '\n';
                    break;
                case 3:
                    std::cout << "Saldo: " << contaCliente->getSaldo(senhaIn) << "\n\n";
                    break;
                case 4:
                    atendimento();
                    break;
                case 5:
                    atend = false;
                    break;
                default:
                    std::cout << "Opção inválida! Tente novamente!\n\n";
                }
            }
        }
        else
        {
            std::cout << "Senha inválida! Acesso negado\n";
        }
    }
}