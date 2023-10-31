#ifndef EMPACOTADOR_H
#define EMPACOTADOR_H

class Empacotador
{
  public:
    Empacotador(int);
    void empacotar(int);
    int getNumEmpacotados();
    int getTotalEmpacotados();
    void imprimeNumEmpacotados();
    static void imprimeTotalEmpacotados();

  private:
    int id;
    int numEmpacotados;
    static int totalEmpacotados;
};

#endif // !EMPACOTADOR_H