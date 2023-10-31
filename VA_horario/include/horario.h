#ifndef HORARIO_H
#define HORARIO_H

class Horario
{
  public:
    Horario(int = 12, int = 0, int = 0);

    // Getters
    int getHora() const;
    int getMinuto() const;
    int getSegundo() const;

    // Setters
    void setHorario(int, int, int);
    void setHora(int);
    void setMinuto(int);
    void setSegundo(int);

    void imprimeHorario() const;

  private:
    int hora;
    int minuto;
    int segundo;
};

#endif // !HORARIO_H