#ifndef SENSOR_VAZAO_H
#define SENSOR_VAZAO_H

#include "medicao.h"
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::ifstream;
using std::vector;

class SensorVazao
{
  public:
    SensorVazao(const string &path, const vector<string> &headers);
    ~SensorVazao();
    bool abrirArquivo(const string &path);
    bool lerDados();
    void imprimeDados();
    int salvarDados(const string &path,
                    const string &inicio = "",
                    const string &final = "");

    //* Getters
    string getID();
    string getUnidade();
    int getNumMed();
    int getPeriodoAmostragem();
    double getDado(const string &horario);

  private:
    vector<Medicao> dados_;
    vector<string> headers_;
    string id_;
    string unidade_;
    int numMed_;
    int Ts_;
    ifstream file_;
};

#endif // SENSOR_VAZAO_H
