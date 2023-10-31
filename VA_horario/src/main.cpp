#include "horario.h"
#include <iostream>

int main()
{
    const Horario h1(15, 42);
    h1.imprimeHorario();

    Horario h2(21, 56);
    h2.imprimeHorario();
    return 0;
}