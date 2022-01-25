//
// Created by Lucas Gaming on 22/01/2022.
//

#ifndef PROJETO2_MENU_H
#define PROJETO2_MENU_H

#include "string"
#include "iostream"

using namespace std;

class Menu {
public:
    static void drawEscolhaDN();
    static void drawEscolhaParCor();
    static void drawInputPar(bool origem);
    static void drawInputCoord(bool origem, bool lat);

    static int getNumInput();
    static string getStrInput();
    static double getDoubleInput();
};


#endif //PROJETO2_MENU_H
