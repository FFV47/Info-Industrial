#include "pilha.hpp"
#include <iostream>
#include <string>

int main()
{
    int tamPilha, numRemove, in, out;

    std::cout << "Digite o tamanho da pilha: ";
    std::cin >> tamPilha;

    Pilha<int> p1(tamPilha);

    std::cout << "Inserindo os dados na pilha...\n";

    for (int i = 0; i < tamPilha; i++)
    {
        std::cout << "Digite o elemento " << i << " da pilha: ";
        std::cin >> in;
        p1.insere(in);
    }

    std::cout << "Removendo os elementos da pilha...\n";

    do
    {
        std::cout << "Digite o número de elementos a serem removidos: ";
        std::cin >> numRemove;
    } while (numRemove > tamPilha || numRemove < 1);

    while (numRemove)
    {
        p1.remove(out);
        std::cout << "Elemento " << out << " Removido\n";
        numRemove--;
    }

    return 0;
}