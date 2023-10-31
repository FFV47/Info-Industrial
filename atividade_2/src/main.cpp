#include "fila.hpp"
#include <iostream>
#include <string>

using std::string;

int main()
{
    int tam{}, numRemove{};
    int inPilha{}, outPilha{};

    std::cout << "Digite o tamanho da Pilha: ";
    std::cin >> tam;

    Pilha<int> pilha1(tam);

    std::cout << "Inserindo os dados na Pilha...\n";

    for (int i = 0; i < tam; i++)
    {
        std::cout << "Digite o elemento " << i << " da Pilha: ";
        std::cin >> inPilha;
        pilha1.insere(inPilha);
    }

    std::cout << "Removendo os elementos da Pilha...\n";

    do
    {
        std::cout << "Digite o número de elementos a serem removidos: ";
        std::cin >> numRemove;
    } while (numRemove > tam || numRemove < 1);

    while (numRemove)
    {
        pilha1.remove(outPilha);
        std::cout << "Elemento " << outPilha << " Removido\n";
        numRemove--;
    }

    std::cout << '\n';

    //* Fila
    string inFila{}, outFila{};
    std::cout << "Digite o tamanho da Fila: ";
    std::cin >> tam;

    Fila<string> fila1(tam);

    std::cout << "Inserindo os dados na Fila...\n";

    for (int i = 0; i < tam; i++)
    {
        std::cout << "Digite o elemento " << i << " da Fila: ";
        std::cin >> inFila;
        fila1.insere(inFila);
    }

    std::cout << "Removendo os elementos da Fila...\n";

    do
    {
        std::cout << "Digite o número de elementos a serem removidos: ";
        std::cin >> numRemove;
    } while (numRemove > tam || numRemove < 1);

    while (numRemove)
    {
        fila1.remove(outFila);
        std::cout << "Elemento " << outFila << " removido\n";
        numRemove--;
    }

    return 0;
}