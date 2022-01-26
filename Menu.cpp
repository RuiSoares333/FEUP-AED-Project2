//
// Created by Lucas Gaming on 22/01/2022.
//

#include "Menu.h"

using namespace std;

void Menu::drawEscolhaTipoCam(){
    cout << "--- Qual o tipo de caminho que deseja?" << endl;
    cout << "1 - Menos paragens" << endl;
    cout << "2 - Menor distancia" << endl << endl;
}

void Menu::drawEscolhaPe(){
    cout << "--- Pretende poder andar a pe entre paragens? (Max 100m)" << endl;
    cout << "1 - Sim" << endl;
    cout << "2 - Nao" << endl << endl;
}

void Menu::drawEscolhaCor(){
    cout << "--- Como Pretende Escolher a Paragem?" << endl;
    cout << "1 - Mais Proxima" << endl;
    cout << "2 - Escolher de uma Lista num Certo Raio" << endl << endl;
    cout << "0 - Sair" << endl;
}

void Menu::drawEscolhaDN() {
    cout << "--- Escolha o Tipo de Horario ---" << endl;
    cout << "1 - Dia" << endl;
    cout << "2 - Noite" << endl << endl;
    cout << "0 - Sair" << endl;
}

void Menu::drawEscolhaParCor() {
    cout << "--- Como Pretende Escolher a sua Viagem? ---" << endl;
    cout << "1 - Nomes das Paragens" << endl;
    cout << "2 - Coordenadas" << endl << endl;
    cout << "0 - Sair" << endl;
}


void Menu::drawInputPar(bool origem) {
    if(origem){
        cout << "--- Indique o Codigo da Paragem de Origem ---" << endl;
        cout << "Origem: ";
    }
    else{
        cout << "--- Indique o Codigo da Paragem de Destino ---" << endl;
        cout << "Destino: ";
    }
}


void Menu::drawInputCoord(bool origem, bool lat) {
    if(origem){
        if(lat){
            cout << "--- Indique as Coordenadas da Latitude da Origem ---" << endl;
            cout << "Latitude: ";
        }
        else{
            cout << "--- Indique as Coordenadas de Longitude da Origem ---" << endl;
            cout << "Longitude: ";
        }
    }
    else{
        if(lat){
            cout << "--- Indique as Coordenadas da Latitude do Destino ---" << endl;
            cout << "Latitude: ";
        }
        else{
            cout << "--- Indique as Coordenadas de Longitude do Destino ---" << endl;
            cout << "Longitude: ";
        }
    }
}


int Menu::getNumInput() {
    int input = -1;
    try{
        cin >> input;
    } catch(const std::exception& e){
        cout << e.what();
        cout << "Esta etapa so aceita numeros! Por favor evite letras e simbolos" << endl;
    }
    return input;
}

string Menu::getStrInput() {
    string input = "";
//    cin >> input;
    try{
        cin >> input;
    } catch(const std::exception& e){
        cout << e.what();
        cout << "Ocorreu um Problema. Por favor Contacte os Administradores do Sistema" << endl;
    }
    return input;
}


double Menu::getDoubleInput() {
    double input = 0.0;
    try{
        cin >> input;
    } catch(const std::exception& e){
        cout << e.what();
        cout << "Esta etapa so aceita numeros com virgula! Por favor evite letras, simbolos e numeros inteiros." << endl;
    }
    return input;
}

