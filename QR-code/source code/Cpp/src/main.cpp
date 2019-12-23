#include <iostream>

using namespace std;

#include "QR.h"

int main() {
    QR q = QR("111");
    q.analise();
    q.codificar();
    cout<<q;
    return 0;
}