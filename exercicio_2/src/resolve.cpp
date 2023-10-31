#include <math.h>

float fatorial(int n)
{
    if (n == 1)
        return (1);
    else
    {
        return n * fatorial(n - 1);
    }
}

float equacao(char *expression)
{
    float num{};
    float a{fatorial(5)}, b{fatorial(4)}, c{fatorial(3)};
    if (expression[1] == '!')
    {
        num = fatorial(expression[0] - '0');
    }
    else if (expression[1] == '^')
    {
        num = pow(expression[0] - '0', expression[2] - '0');
    }
    else
    {
        num = expression[0] - '0';
    }
    return a * pow(num, 3) + b * pow(num, 2) + c * num + 2;
}