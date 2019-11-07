
#ifndef QR_C_QR_H
#define QR_C_QR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define NUMERICO 1
#define ALPHANUMERICO 2
#define BYTE 3

#define  L 1
#define  M 2
#define  Q 3
#define  H 4
enum {
    Msg_n_suport = 1, nivel_n_suportado
} Error;
typedef struct {
    char *msg;
    int modo_correcao,
            tentar_todos_modos_de_correcao,
            modo_codificacao;
    int error;
} QR, *pQR;

QR QR_new(const char *);

void QR_free(pQR);

void analise(pQR);

int codificar(pQR);

int determinarMenorVersao(pQR);


void ERROR_PRINT(int);
void QR_info(pQR);
#endif //QR_C_QR_H
