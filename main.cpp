#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream file;
    file.open("../dataset/stops.csv");
    cout << file.is_open();
    return 0;
}
