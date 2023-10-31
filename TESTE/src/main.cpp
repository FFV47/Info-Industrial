#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::ifstream;
using std::string;

#include <iostream>

#include <iostream>
#include <string>

class C1
{
  protected:
    int v1;
    int v2;

  public:
    C1(int valor1, int valor2) : v1(valor1), v2(valor2) {}
    virtual int calcular() { return v1 + v2; }
};

class C2 : public C1
{
  public:
    C2(int valor1, int valor2) : C1(valor1, valor2) {}
    int calcular() { return v1 * v2 / 5; }
};

int main()
{
    C1 ob1 = {4, 5};
    C2 ob2 = {9, 8};
    C1 objetos[] = {ob1, ob2};
    C1 *pobjetos[] = {&ob1, &ob2};

    std::cout << objetos[1].calcular() << '\n';
    std::cout << pobjetos[1]->calcular() << '\n';

    return 0;
}