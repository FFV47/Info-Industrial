#include "banco.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

int main()
{
    fs::path arquivo = fs::current_path() / "contasbanco.txt";
    Banco banco1(arquivo, "Contas cadastradas", 1234);
    banco1.atendimentoGeral();
    return 0;
}
