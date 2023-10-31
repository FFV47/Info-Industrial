#include "empacotador.h"
#include <iostream>

int main()
{
    Empacotador::imprimeTotalEmpacotados();
    Empacotador e1(1), e2(2);

    e1.empacotar(10);
    e2.empacotar(20);
    e1.empacotar(30);

    e1.imprimeNumEmpacotados();
    e2.imprimeNumEmpacotados();

    e1.imprimeTotalEmpacotados();

    Empacotador::imprimeTotalEmpacotados();

    return 0;
}