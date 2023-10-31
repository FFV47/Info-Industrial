#include "pilha.hpp"
#include <cstdio>
#include <iostream>
#include <string>

using std::string;

template <typename T> void imprimeVetor(T *p, int tam)
{
    for (int i{}; i < tam; i++)
    {
        std::cout << "Posição: " << i << " Valor: " << p[i] << '\n';
    }
}

int main()
{
    // int arr[] = {1, 2, 3, 4};
    // char arr2[] = "string";
    // double num = 123.127;

    // imprimeVetor(arr, 4);
    // printf("\n");
    // imprimeVetor(arr2, 6);
    // printf("\n");
    // printf("%s\n\n", arr2);
    // printf("Numero: %.2f", num);

    int tamPilha, numRemove;
    string in, out;

    std::cout << "Digite o tamanho da pilha: ";
    std::cin >> tamPilha;

    Pilha<string> p1(tamPilha);

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