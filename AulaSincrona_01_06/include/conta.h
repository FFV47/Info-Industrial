#ifndef CONTA_H
#define CONTA_H
#include <string>

using std::string;
class Conta
{
  private:
    double m_saldo;
    int m_senha;

  public:
    Conta();
    Conta(int senha, int numero, string titular, string tipo, double saldo);
    ~Conta();
    int m_numero;
    string m_titular;
    string m_tipo;
    void exibeDados();
    double getSaldo(int senha);
    void setSaldo(double valor);
    void setSenha(int novaSenha);
    void deposito(double valor);
    void saque(int senha, double valor);
    bool validaSenha(int senha);
};

#endif