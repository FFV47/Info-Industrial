#ifndef CONTA_POUPANCA_H
#define CONTA_POUPANCA_H

#include "conta.h"

class ContaPoupanca : public Conta
{
  public:
    ContaPoupanca(const int senha,
                  const int numero,
                  const string &titular,
                  const string &tipo,
                  const double saldo,
                  const double taxa);
    ~ContaPoupanca() = default;
    void simulaRendimento(const unsigned int num_meses);
    double getTaxa();
    string printCSV();

  private:
    double taxa_rend_;
};

#endif // CONTA_POUPANCA_H