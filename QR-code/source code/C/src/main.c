#include <stdio.h>
#include "QR.h"

int main() {
    QR qr = QR_new("A man");
    pQR p_qr = &qr;

    analise(p_qr);
    ERROR_PRINT(codificar(p_qr));

    QR_info(p_qr);
    QR_free(p_qr);
    return 0;
}