#include "empacotador.h"
#include <iostream>

int Empacotador::totalEmpacotados = 0;

Empacotador::Empacotador(int id) : id(id), numEmpacotados(0)
{
}

void Empacotador::empacotar(int numPacotes)
{
    this->numEmpacotados += numPacotes;
    Empacotador::totalEmpacotados += numPacotes;
}

int Empacotador::getNumEmpacotados()
{
    return this->numEmpacotados;
}

int Empacotador::getTotalEmpacotados()
{
    return Empacotador::totalEmpacotados;
}

void Empacotador::imprimeNumEmpacotados()
{
    std::cout << "Empacotador " << this->id << " empacotou " << this->getNumEmpacotados() << " pacotes\n";
}

void Empacotador::imprimeTotalEmpacotados()
{
    std::cout << "Total de empacotados: " << Empacotador::totalEmpacotados << '\n';
}