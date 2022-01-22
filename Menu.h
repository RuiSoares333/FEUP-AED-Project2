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

    static int getNumInput();
    static int getStrInput();
};


#endif //PROJETO2_MENU_H
