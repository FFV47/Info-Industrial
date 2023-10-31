#include "banco.h"
#include "conta.h"
#include "conta_corrente.h"
#include "conta_poupanca.h"
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

Banco::Banco(const fs::path &path, const string &header, const int senha)
    : header_(header),
      senha_gerente_(senha)
{
    abrirArquivo(path);
    lerContasArquivo();
}

Banco::~Banco()
{
    for (int i{}; i < num_contas_; i++)
    {
        delete contas_[i];
    }
    delete[] contas_;
    arquivo_input_.close();
}

Conta *Banco::buscaConta(int numero)
{
    for (int i = 0; i < num_contas_; i++)
    {
        if (numero == contas_[i]->getNumero())
        {
            return contas_[i];
        }
    }
    return nullptr;
}

bool Banco::validaGerente(int senha)
{
    if (senha_gerente_ != senha)
    {
        std::cout << "Senha inválida!";
        return false;
    }
    else
    {
        return true;
    }
}

vector<string> Banco::splitString(const string &linha)
{
    char sep = ',';
    string dado{};
    vector<string> dados;
    // Converte a string em stream (permite a string ser lida uma entrada de
    // dados)
    std::stringstream stream{linha};

    // Armazena os dados da conta na referida linha do arquivo CSV no vetor de
    // strings "dados"
    while (std::getline(stream, dado, sep))
    {
        dados.push_back(dado);
    }

    return dados;
}

void Banco::abrirArquivo(const fs::path &path)
{
    try
    {
        arquivo_input_.open(path);
    }
    catch (const std::exception &e)
    {
        std::cout << "\nErro ao abrir base de dados\n";
        std::cout << e.what() << '\n';
    }
}

void Banco::lerContasArquivo()
{
    try
    {
        if (arquivo_input_.is_open())
        {
            //* Validação do cabeçalho do arquivo

            string line_read{};
            // Descarta a primeira linha
            std::getline(arquivo_input_, line_read);

            // Leitura do cabeçalho do arquivo
            std::getline(arquivo_input_, line_read);

            // Compara o header do arquivo com o da classe
            // Se o cabeçalho estiver correto, é realizada a leitura do número
            // de contas cadastradas
            int sep_pos = line_read.find(":");

            if (line_read.substr(0, sep_pos) == header_)
            {
                num_contas_ = std::stoi(line_read.substr(sep_pos + 1));
            }
            else
            {
                throw std::runtime_error("Erro de leitura do cabeçalho\n");
            }

            //* Leitura dos dados

            contas_ = new Conta *[num_contas_];

            vector<string> dados;

            for (int i{}; i < num_contas_; i++)
            {
                std::getline(arquivo_input_, line_read);
                dados = splitString(line_read);
                if (dados[3] == "\"Corrente\"")
                {
                    contas_[i] = new ContaCorrente(
                        std::stoi(dados[0]), std::stoi(dados[1]), dados[2],
                        dados[3], std::stod(dados[4]), std::stoul(dados[5]));
                }
                else
                {
                    contas_[i] = new ContaPoupanca(
                        std::stoi(dados[0]), std::stoi(dados[1]), dados[2],
                        dados[3], std::stod(dados[4]), std::stod(dados[5]));
                }
            }
        }
        else
        {
            throw std::runtime_error("Arquivo não está aberto\n");
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Arquivo corrompido - Erro: " << e.what() << '\n';
    }
}

void Banco::exibirContas()
{
    std::cout << "\nContas cadastradas: " << num_contas_ << '\n';
    for (int i{}; i < num_contas_; i++)
    {
        std::cout << "\nConta " << contas_[i]->getNumero() << '\n';
        std::cout << "Titular: " << contas_[i]->getTitular() << '\n';
        std::cout << "Tipo: " << contas_[i]->getTipo() << '\n';
    }
    std::cout << '\n';
}

void Banco::cadastrarConta()
{
    try
    {
        Conta **temp_contas = new Conta *[num_contas_ + 1];

        for (int i{}; i < num_contas_; i++)
        {
            temp_contas[i] = contas_[i];
        }

        int senha{}, tipo{};
        unsigned long cartao;
        string titular{};
        double saldo{}, taxa{};
        std::cout << "\nCadastro de novo cliente\n\n";
        std::cout << "Titular: ";
        std::cin >> titular;
        std::cout << "Senha: ";
        std::cin >> senha;
        do
        {
            std::cout << "Tipo:\n";
            std::cout << "1 -> Corrente\n2 -> Poupança\n";
            std::cout << "Opção: ";
            std::cin >> tipo;
        } while (tipo != 1 && tipo != 2);
        std::cout << "Saldo: ";
        std::cin >> saldo;
        if (tipo == 1)
        {
            std::cout << "Número do cartão: ";
            std::cin >> cartao;
            temp_contas[num_contas_] = new ContaCorrente(
                senha, num_contas_ + 1, titular, "Corrente", saldo, cartao);
        }
        else
        {
            std::cout << "Taxa de rendimento da poupança (em decimal): ";
            std::cin >> taxa;
            temp_contas[num_contas_] = new ContaPoupanca(
                senha, num_contas_ + 1, titular, "Poupanca", saldo, taxa);
        }

        num_contas_++;
        delete[] contas_;

        contas_ = temp_contas;
        temp_contas = nullptr;

        std::cout << "\nConta criada com sucesso!\n";
        std::cout << "Salvando no banco de dados...\n";

        salvarContas();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Banco::salvarContas()
{
    try
    {
        std::ofstream outFile;
        outFile.open(fs::current_path() / "contas.csv",
                     std::ofstream::out | std::ofstream::trunc);
        if (!outFile.is_open())
            throw std::runtime_error("Arquivo CSV não está aberto\n");

        outFile << "\%Contas banco\n";
        outFile << header_ << ": " << num_contas_ << '\n';

        for (int i{}; i < num_contas_; i++)
        {
            outFile << contas_[i]->printCSV() << '\n';
        }
        outFile.close();

        std::cout << "Contas salvas com sucesso!\n\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Banco::atendimentoGeral()
{
    int gerente{};

    std::cout << "\nBem-vindo ao sistema de atendimento do banco\n";
    do
    {
        std::cout << "Escolha o tipo de acesso\n";
        std::cout << "0 -> Cliente\n";
        std::cout << "1 -> Gerente\n";
        std::cout << "9 -> Sair\n";
        std::cout << "Opção: ";
        std::cin >> gerente;
        if (gerente == 9)
        {
            throw std::runtime_error("Saindo...");
        }

    } while (gerente != 1 && gerente != 0);

    if (gerente == 1)
    {
        atendimentoGerente();
    }
    else
    {
        atendimentoCliente();
    }
}

void Banco::atendimentoGerente()
{
    int senha_input{};
    char sair{};

    std::cout << "\nSistema de gerenciamento do Banco\n\n";
    std::cout << "Digite a senha de Gerente: ";
    std::cin >> senha_input;

    try
    {
        if (validaGerente(senha_input))
        {
            std::cout << "\nAcesso permitido\n\n";
            while (1)
            {
                int opção{};
                std::cout << "Menu de operações do Gerente\n";
                std::cout << "1 - Cadastrar novo cliente\n";
                std::cout << "2 - Ver contas\n";
                std::cout << "3 - Voltar ao menu inicial\n";
                std::cout << "4 - Sair\n";
                std::cout << "Opção escolhida: ";
                std::cin >> opção;
                switch (opção)
                {
                case 1:
                    cadastrarConta();
                    break;
                case 2:
                    exibirContas();
                    break;
                case 3:
                    atendimentoGeral();
                    break;
                case 4:
                    throw std::runtime_error("Saindo...");
                default:
                    std::cout << "Opção inválida! Tente novamente!\n\n";
                }
            }
        }
        else
        {
            std::cout << "\nSenha inválida! Acesso negado\n";
            std::cout << "Deseja continuar [s/n] ? ";
            std::cin >> sair;
            if (sair == 's')
            {
                std::cout << "Desconectando do sistema...\n\n";
            }
            else if (sair == 'n')
            {
                std::cout << "Retornando ao acesso do gerente...\n\n";
                atendimentoCliente();
            }
            else
                std::cout << "\nOpção inválida!\n";
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Banco::atendimentoCliente()
{
    Conta *conta_cliente;
    int num_conta{};

    std::cout << "\nSistema de atendimento ao cliente\n\n";
    do
    {
        std::cout << "Digite o número da conta: ";
        std::cin >> num_conta;
        conta_cliente = buscaConta(num_conta);
        if (conta_cliente == nullptr)
            std::cout << "Conta inválida! Tente novamente\n\n";
    } while (conta_cliente == nullptr);

    if (conta_cliente->getTipo() == "Corrente")
    {
        atendimentoCorrente(static_cast<ContaCorrente *>(conta_cliente));
    }
    else
    {
        atendimentoPoupanca(static_cast<ContaPoupanca *>(conta_cliente));
    }
}

void Banco::atendimentoCorrente(ContaCorrente *cliente)
{
    int senha_input{};
    char sair{};
    std::cout << "Digite sua senha: ";
    std::cin >> senha_input;
    if (cliente->validaSenha(senha_input))
    {
        std::cout << '\n';
        while (1)
        {
            int opção{};
            double valor{};
            std::cout << "Olá, " << cliente->getTitular() << '\n';
            std::cout << "Menu da conta corrente\n";
            std::cout << "1 - Saque\n";
            std::cout << "2 - Depósito\n";
            std::cout << "3 - Ver saldo\n";
            std::cout << "4 - Ver número do cartao\n";
            std::cout << "5 - Voltar ao menu de Acesso\n";
            std::cout << "6 - Acessar outra conta\n";
            std::cout << "7 - Sair\n";
            std::cout << "Opção escolhida: ";
            std::cin >> opção;
            switch (opção)
            {
            case 1:
                std::cout << "\nDigite o valor do saque: ";
                std::cin >> valor;
                cliente->saque(senha_input, valor);
                std::cout << '\n';
                salvarContas();
                break;
            case 2:
                std::cout << "\nDigite o valor do depósito: ";
                std::cin >> valor;
                cliente->deposito(valor);
                std::cout << '\n';
                salvarContas();
                break;
            case 3:
                std::cout << std::fixed << std::setprecision(2);
                std::cout << "\nSaldo: R$ " << cliente->getSaldo(senha_input)
                          << "\n\n";
                break;
            case 4:
                std::cout << "\nNúmero do cartão: " << cliente->getCartao()
                          << "\n\n";
                break;
            case 5:
                atendimentoGeral();
                break;
            case 6:
                atendimentoCliente();
                break;
            case 7:
                throw std::runtime_error("Saindo...");
            default:
                std::cout << "\nOpção inválida! Tente novamente!\n\n";
            }
        }
    }
    else
    {
        std::cout << "\nSenha inválida! Acesso negado\n";
        std::cout << "Deseja continuar [s/n] ? ";
        std::cin >> sair;
        if (sair == 's')
        {
            std::cout << "Desconectando do sistema...\n\n";
        }
        else if (sair == 'n')
        {
            std::cout << "Retornando ao acesso do cliente...\n\n";
            atendimentoCliente();
        }
        else
            std::cout << "Opção inválida!\n";
    }
}

void Banco::atendimentoPoupanca(ContaPoupanca *cliente)
{
    int senha_input{};
    char sair{};
    std::cout << "Digite sua senha: ";
    std::cin >> senha_input;
    if (cliente->validaSenha(senha_input))
    {
        std::cout << '\n';
        while (1)
        {
            int opção{};
            double valor{};
            std::cout << "Olá, " << cliente->getTitular() << '\n';
            std::cout << "Menu da conta poupança\n";
            std::cout << "1 - Saque\n";
            std::cout << "2 - Depósito\n";
            std::cout << "3 - Ver saldo\n";
            std::cout << "4 - Ver taxa de rendimento\n";
            std::cout << "5 - Simular investimento\n";
            std::cout << "6 - Voltar ao menu de Acesso\n";
            std::cout << "7 - Acessar outra conta\n";
            std::cout << "8 - Sair\n";
            std::cout << "Opção escolhida: ";
            std::cin >> opção;
            switch (opção)
            {
            case 1:
                std::cout << "\nDigite o valor do saque: ";
                std::cin >> valor;
                cliente->saque(senha_input, valor);
                std::cout << '\n';
                salvarContas();
                break;
            case 2:
                std::cout << "\nDigite o valor do depósito: ";
                std::cin >> valor;
                cliente->deposito(valor);
                std::cout << '\n';
                salvarContas();
                break;
            case 3:
                std::cout << std::fixed << std::setprecision(2);
                std::cout << "\nSaldo: R$ " << cliente->getSaldo(senha_input)
                          << "\n\n";
                break;
            case 4:
                std::cout << "\nTaxa de rendimento: "
                          << cliente->getTaxa() * 100 << " %\n\n";
                break;
            case 5:
                std::cout << "\nDigite o número de meses para a simulação: ";
                std::cin >> valor;
                cliente->simulaRendimento((unsigned int)valor);
                break;
            case 6:
                atendimentoGeral();
                break;
            case 7:
                atendimentoCliente();
                break;
            case 8:
                throw std::runtime_error("Saindo...");
            default:
                std::cout << "\nOpção inválida! Tente novamente!\n\n";
            }
        }
    }
    else
    {
        std::cout << "\nSenha inválida! Acesso negado\n";
        std::cout << "Deseja continuar [s/n] ? ";
        std::cin >> sair;
        if (sair == 's')
        {
            std::cout << "Desconectando do sistema...";
        }
        else if (sair == 'n')
        {
            std::cout << "Retornando ao acesso do cliente...\n\n";
            atendimentoCliente();
        }
        else
            std::cout << "\nOpção inválida!\n";
    }
}