#include <iostream>

using namespace std;

#include "QR.h"

int main() {
    QR q = QR("HELLO WORLD");
    q.analise();
    q.codificar();
    cout<<q;


    return 0;
}