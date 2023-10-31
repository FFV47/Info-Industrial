#ifndef CONTA_H
#define CONTA_H

#include <string>

using std::string;

class Conta
{
  public:
    Conta(const int senha,
          const int numero,
          const string &titular,
          const string &tipo,
          const double saldo);
    virtual ~Conta() = default;

    // Getters
    int getNumero();
    string getTitular();
    string getTipo();
    double getSaldo(int senha);
    // Setters
    void setSaldo(double valor);
    void setSenha(int senha);

    bool validaSenha(int senha);
    void exibeDados();
    virtual string printCSV();
    string trimChar(string campo, char caractere);
    string printFloat(double valor, int precisao);

    void deposito(double valor);
    void saque(int senha, double valor);
    void transferencia(double valor, Conta *destino);

  protected:
    int numero_;
    string titular_;
    string tipo_;
    double saldo_;
    int senha_;
};

#endif // !CONTA_H