//
// Created by Lucas Gaming on 22/01/2022.
//

#include "Menu.h"

using namespace std;

/// Mostra no ecrã as opções de escolha de caminho
void Menu::drawEscolhaTipoCam(){
    cout << "--- Qual o tipo de caminho que deseja?" << endl;
    cout << "1 - Menos paragens" << endl;
    cout << "2 - Menor distancia" << endl << endl;
}

/// Mostra no ecrã a opção para andar entre paragens ou não
void Menu::drawEscolhaPe(){
    cout << "--- Pretende poder andar a pe entre paragens? (Max 100m)" << endl;
    cout << "1 - Sim" << endl;
    cout << "2 - Nao" << endl << endl;
}

/// Mostra no ecrã as opções para escolha da paragem
void Menu::drawEscolhaCor(){
    cout << "--- Como Pretende Escolher a Paragem?" << endl;
    cout << "1 - Mais Proxima" << endl;
    cout << "2 - Escolher de uma Lista num Certo Raio" << endl << endl;
    cout << "0 - Sair" << endl;
}

/// Mostra no ecrã a opção para escolha de horário diurno ou noturno
void Menu::drawEscolhaDN() {
    cout << "--- Escolha o Tipo de Horario ---" << endl;
    cout << "1 - Dia" << endl;
    cout << "2 - Noite" << endl << endl;
    cout << "0 - Sair" << endl;
}

/// Mostra no ecrã as opções de como escolher a viagem
void Menu::drawEscolhaParCor() {
    cout << "--- Como Pretende Escolher a sua Viagem? ---" << endl;
    cout << "1 - Nomes das Paragens" << endl;
    cout << "2 - Coordenadas" << endl << endl;
    cout << "0 - Sair" << endl;
}

/// Mostra no ecrã o pedido para o código da paragem de origem, se a variável origem for true, ou a de destino, se origem for false
/// \param origem true se a paragem for a de origem, false se for a de destino
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

/// Mostra no ecrã o pedido das coordenadas da origem ou do destino, conforme a variável origem
/// \param origem true se a paragem for a de origem, false se for a de destino
/// \param lat true se quisermos pedir a latitude, false se quisermos pedir a longitude
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

/// Mostra no ecrã uma mensagem de erro se tentarmos inserir inputs que não sejam números inteiros
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

/// Mostra no ecrã uma mensagem de erro se não se conseguir ler a string
string Menu::getStrInput() {
    string input = "";
    try{
        cin >> input;
    } catch(const std::exception& e){
        cout << e.what();
        cout << "Ocorreu um Problema. Por favor Contacte os Administradores do Sistema" << endl;
    }
    return input;
}

/// Mostra no ecrã uma mensagem de erro se tentarmos inserir inputs que não sejam doubles
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

