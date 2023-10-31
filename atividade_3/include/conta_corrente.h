#ifndef CONTA_CORRENTE_H
#define CONTA_CORRENTE_H

#include "conta.h"

class ContaCorrente : public Conta
{
  public:
    ContaCorrente(const int senha,
                  const int numero,
                  const string &titular,
                  const string &tipo,
                  const double saldo,
                  const unsigned long cartao);
    ~ContaCorrente() = default;
    string printCSV();
    unsigned long getCartao();

  private:
    unsigned long num_cartao_;
};

#endif // CONTA_CORRENTE_H