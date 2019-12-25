
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
    Msg_n_suport = 1, nivel_n_suportado, file_not_found
} Error;
typedef struct {
    char *msg, *strbits;
    int modo_correcao,
            modo_corecao_forcado,
            modo_codificacao;

    int error;

    int tamanhoMensagem, size_strbits;
    int capacidadeCaracteres;
    int versao;

} QR, *pQR;

QR QR_new(const char *);

void QR_free(pQR);

void analise(pQR);

int codificar(pQR);

void determinarMenorVersao(pQR);

void indicadorModo(pQR);

void contagemCaracteres(pQR);
void codificarDados(pQR);
void ERROR_PRINT(int);

void QR_info(pQR);

void dec2bin(char *, int, int);

#endif //QR_C_QR_H
