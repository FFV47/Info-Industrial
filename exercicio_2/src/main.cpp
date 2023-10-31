#include "mylib.h"
#include <iostream>
#include <string.h>

int main()
{
    char expr[4]{};
    float result{};

    expr[0] = '3';
    result = equacao(expr);
    std::cout << "y(3) = " << result << '\n';

    strcpy(expr, "3!");
    result = equacao(expr);
    std::cout << "y(3!) = " << result << '\n';

    strcpy(expr, "2^3");
    result = equacao(expr);
    std::cout << "y(2^3) = " << result << '\n';
}