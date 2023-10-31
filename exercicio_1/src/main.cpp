#include "imc.h"
#include <iomanip>
#include <iostream>

int main()
{
    float peso{}, altura{}, imc{};
    std::cout << "Digite seu peso em kg: ";
    std::cin >> peso;
    std::cout << "Digite sua altura em metros: ";
    std::cin >> altura;
    imc = calc_imc(peso, altura);
    // fixa precisão de duas casas para cout
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Seu índice de massa corporal é: " << imc << std::endl;

    if (imc < 18.5)
    {
        std::cout << "Você está abaixo do peso" << '\n';
    }
    else if (imc >= 18.5 && imc <= 24.9)
    {
        std::cout << "Você está com o peso normal" << '\n';
    }
    else if (imc >= 25 && imc <= 29.9)
    {
        std::cout << "Você está acima do peso" << '\n';
    }
    else if (imc >= 30)
    {
        std::cout << "Você está obeso" << '\n';
    }
    return 0;
}