#ifndef CONTA_H
#define CONTA_H

#include <string>

using std::string;

class Conta
{
  public:
    Conta();
    Conta(int numero, int senha, string titular, string tipo = "Corrente", double saldo = 1000);
    int m_numero;
    string m_titular;
    string m_tipo;
    void exibeDados();
    double getSaldo(int senha);
    void setSaldo(double valor);
    void setSenha(int senha);
    void deposito(double valor);
    void saque(int senha, double valor);
    void transferencia(double valor, Conta *destino);

  private:
    double m_saldo;
    int m_senha;
};

#endif // !CONTA_H