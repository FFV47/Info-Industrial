#ifndef FILA_HPP
#define FILA_HPP

#include "pilha.hpp"

template <typename T>
class Fila : public Pilha<T>
{
  public:
    Fila(int tam = 10);
    ~Fila();
    bool remove(T &valorOut);
    bool estaVazia() const;

  private:
    int first_{};
};

template <typename T>
Fila<T>::Fila(int tam) : Pilha<T>(tam)
{}

template <typename T>
Fila<T>::~Fila<T>()
{}

template <typename T>
bool Fila<T>::remove(T &valorOut)
{
    if (!Pilha<T>::estaVazia())
    {
        valorOut = Pilha<T>::pPtr_[first_++];
        return true;
    }
    else
        return false;
}

template <typename T>
bool Fila<T>::estaVazia() const
{
    return first_ == Pilha<T>::top_;
}

#endif // FILA_HPP