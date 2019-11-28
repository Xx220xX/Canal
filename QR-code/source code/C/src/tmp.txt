#include <stdio.h>
#include "QR.h"

int main() {
    int erro=0;
    QR qr = QR_new("1234");
    pQR p_qr = &qr;

    analise(p_qr);
    erro = codificar(p_qr);

    QR_info(p_qr);
    ERROR_PRINT(erro);
    QR_free(p_qr);
    return 0;
}