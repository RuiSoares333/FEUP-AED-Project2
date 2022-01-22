//
// Created by Lucas Gaming on 22/01/2022.
//

#include "Menu.h"

using namespace std;

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

int Menu::getNumInput() {
    int input = -1;
    try{
        cin >> input;
    } catch(const std::exception& e){
        cout << e.what();
        cout << "Esta etapa so aceita numeros! Por favor evite letras e simbolos";
    }
    return input;
}

int Menu::getStrInput() {
    int input = -1;
    try{
        cin >> input;
    } catch(const std::exception& e){
        cout << e.what();
        cout << "Ocorreu um Problema. Por favor Contacte os Administradores do Sistema";
    }
    return input;
}