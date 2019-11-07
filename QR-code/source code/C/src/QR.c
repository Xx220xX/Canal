#include "QR.h"


void ERROR_PRINT(int erro) {
    switch (erro) {
        case Msg_n_suport:
            printf("mensagem nao suportada!");
            break;
        case nivel_n_suportado:
            printf("nivel nao suportado!");
            break;
    }
    printf("\n");
}

QR QR_new(const char *msg) {
    QR q = {0};
    q.msg = (char *) calloc(strlen(msg) + 1, sizeof(char));
    snprintf(q.msg, strlen(msg) + 1, "%s", msg);
    return q;
}

void QR_free(pQR q) {
    free(q->msg);
}

void QR_info(pQR q) {
    printf("msg: %s\nmodo de codificacao: ", q->msg);
    switch (q->modo_codificacao) {
        case ALPHANUMERICO:
            printf("ALPHA");
        case NUMERICO:
            printf("NUMERICO");
            break;
        case BYTE:
            printf("BYTE");
            break;
        default:
            printf("error: modo de codificacao nao definido");
    }
    printf("\ncorrecao: ");
    switch (q->modo_correcao) {
        case L:
            printf("L");
            break;
        case M:
            printf("M");
            break;
        case Q:
            printf("Q");
            break;
        case H:
            printf("H");
            break;
        default:
            printf("Ainda nao definido");
    }
    printf("\n");
}

void analise(pQR qr) {
    const char *c;
    qr->modo_codificacao = NUMERICO;
    for (c = qr->msg; *c; c += 1) {
        if (isdigit(*c))
            continue;
        if (isupper(*c) || *c == ' ' || *c == '$' || *c == '*' || *c == '+' || *c == '.' || *c == '/' || *c == ':') {
            qr->modo_codificacao = ALPHANUMERICO;
            continue;
        }
        qr->modo_codificacao = BYTE;
        break;
    }
}

int codificar(QR *qr) {
    if (!qr->tentar_todos_modos_de_correcao) {
        qr->modo_correcao = H;
    }
    while (qr->modo_correcao >= L) {
        qr->error = 0;
        determinarMenorVersao(qr);
//     identicador_de_modo(qr);
//     contagem_de_caracteres(qr);
//     codificarDados(qr);
//    qr->error dividir_em_blocos(qr);
        if (qr->error) {
            if (!qr->tentar_todos_modos_de_correcao && qr->modo_correcao > L) {
                qr->modo_correcao--;

                continue;
            }
            qr->modo_correcao = -1;
            return Msg_n_suport;
        }
        return 0;
    }
    return Msg_n_suport;
}

int determinarMenorVersao(pQR q) {
    if (q->error) {
        return q->error;
    }

    return 0;
}


