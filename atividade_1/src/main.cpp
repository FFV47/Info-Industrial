#include "conta.h"
#include <cstdio>
#include <iostream>

int main()
{
    Conta contas[2] = {{1, 12, "Carlos"}, {2, 34, "Manoel", "Poupança", 2000}};

    contas[0].exibeDados();
    std::cout << "Saldo: " << contas[0].getSaldo(12) << "\n\n";
    contas[1].exibeDados();
    std::cout << "Saldo: " << contas[1].getSaldo(34) << "\n\n";

    contas[1].transferencia(300, &contas[0]);

    printf("\n");
    std::cout << "Saldo das contas após transferência...\n\n";
    std::cout << "Saldo de " << contas[0].m_titular << ": " << contas[0].getSaldo(12) << "\n";
    std::cout << "Saldo de " << contas[1].m_titular << ": " << contas[1].getSaldo(34) << "\n";

    return 0;
}