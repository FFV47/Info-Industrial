#ifndef BANCO_H
#define BANCO_H
#define MAX_CONTAS 100
#include "conta.h"

class Banco
{
  public:
    Banco();
    ~Banco();
    Conta *buscaConta(int numero);
    void atendimento();

  private:
    Conta m_contas[MAX_CONTAS];
};

#endif // !BANCO_H