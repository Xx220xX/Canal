#include <stdio.h>
#include "QR.h"

int main() {
    QR qr = QR_new("111");
    pQR p_qr = &qr;

    analise(p_qr);
    codificar(p_qr);

    QR_info(p_qr);
    QR_free(p_qr);

    return 0;
}