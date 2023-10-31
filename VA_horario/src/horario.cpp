#include "horario.h"
#include <iomanip>
#include <iostream>

Horario::Horario(int h, int m, int s)
{
    setHorario(h, m, s);
}

void Horario::setHorario(int h, int m, int s)
{
    setHora(h);
    setMinuto(m);
    setSegundo(s);
}

void Horario::setHora(int h)
{
    hora = (h >= 0 && h < 24) ? h : 0;
}

void Horario::setMinuto(int m)
{
    minuto = (m >= 0 && m < 60) ? m : 0;
}

void Horario::setSegundo(int s)
{
    segundo = (s >= 0 && s < 60) ? s : 0;
}

int Horario::getHora() const
{
    return hora;
}
int Horario::getMinuto() const
{
    return minuto;
}
int Horario::getSegundo() const
{
    return segundo;
}

void Horario::imprimeHorario() const
{
    std::cout << std::setfill('0') << std::setw(2) << getHora() << ':' << std::setw(2) << getMinuto() << ':'
              << std::setw(2) << getSegundo() << '\n';
}