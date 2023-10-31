#ifndef PILHA_H
#define PILHA_H

template <typename T> class Pilha
{
  public:
    Pilha(int = 10);
    ~Pilha();
    bool insere(const T &valor);
    bool remove(T &valorOut);
    bool estaVazia() const;
    bool estaCheia() const;

  private:
    int tam;
    int top;
    T *pPtr;
};

template <typename T> Pilha<T>::Pilha(int tam)
{
    this->tam = tam > 0 ? tam : 10;
    top = -1;
    pPtr = new T[tam];
}

template <typename T> Pilha<T>::~Pilha()
{
    delete[] pPtr;
}

template <typename T> bool Pilha<T>::insere(const T &valor)
{
    if (!estaCheia())
    {
        pPtr[++top] = valor;
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T> bool Pilha<T>::remove(T &valorOut)
{
    if (!estaVazia())
    {
        valorOut = pPtr[top--];
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T> bool Pilha<T>::estaVazia() const
{
    return top == -1;
}

template <typename T> bool Pilha<T>::estaCheia() const
{
    return top == tam - 1;
}

#endif // !PILHA_H