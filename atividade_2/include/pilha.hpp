#ifndef PILHA_HPP
#define PILHA_HPP

template <typename T>
class Pilha
{
  public:
    Pilha(int tam = 10);
    ~Pilha();
    bool insere(const T &valor);
    virtual bool remove(T &valorOut);
    virtual bool estaVazia() const;
    bool estaCheia() const;

  protected:
    int top_;
    T *pPtr_;

  private:
    int tam_;
};

template <typename T>
Pilha<T>::Pilha(int tam)
{
    tam_ = tam > 0 ? tam : 10;
    top_ = -1;
    pPtr_ = new T[tam];
}

template <typename T>
Pilha<T>::~Pilha()
{
    delete[] pPtr_;
}

template <typename T>
bool Pilha<T>::insere(const T &valor)
{
    if (!estaCheia())
    {
        pPtr_[++top_] = valor;
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
bool Pilha<T>::remove(T &valorOut)
{
    if (!estaVazia())
    {
        valorOut = pPtr_[top_--];
        return true;
    }
    else
        return false;
}

template <typename T>
bool Pilha<T>::estaVazia() const
{
    return top_ == -1;
}

template <typename T>
bool Pilha<T>::estaCheia() const
{
    return top_ == tam_ - 1;
}

#endif // !PILHA_HPP