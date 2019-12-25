#include "QR.h"
#include <math.h>

int tabela_quantidade_caracteres[][3] = {{10, 12, 14},
                                         {9,  11, 13},
                                         {8,  16, 16},
                                         {8,  10, 12}};

void addletters(pQR qr, int bits);

void codificarNumerico(pQR qr);

void codificarByte(pQR qr);

void codificarAlphaumerico(pQR qr);

void ERROR_PRINT(int erro) {
    switch (erro) {
        case Msg_n_suport:
            printf("mensagem nao suportada!");
            break;
        case nivel_n_suportado:
            printf("nivel nao suportado!");
            break;
        case file_not_found:
            printf("Arquivo nao encontrado");
            break;

    }
    printf("\n");
}

QR QR_new(const char *msg) {
    QR q = {0};
    q.tamanhoMensagem = strlen(msg);
    q.msg = (char *) calloc(q.tamanhoMensagem + 1, sizeof(char));
    snprintf(q.msg, q.tamanhoMensagem + 1, "%s", msg);
    return q;
}

void QR_free(pQR q) {
    if (q->msg)
        free(q->msg);
    if (q->strbits)
        free(q->strbits);
}

void QR_info(pQR q) {
    if (q->error) {
        ERROR_PRINT(q->error);
        return;
    }
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
            printf("Q.txt");
            break;
        case H:
            printf("H");
            break;
        default:
            printf("Ainda nao definido");
    }
    printf("\n");
    printf("Versao: %d\n", q->versao);
    printf("capacidade de caracteres: %d\n", q->capacidadeCaracteres);
    printf("quantidade de caracteres: %d\n", q->tamanhoMensagem);
    printf("str bits: %s\n", q->strbits);

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
    if (!qr->modo_corecao_forcado) {
        qr->modo_correcao = H;

    }
    while (qr->modo_correcao >= L) {
        qr->error = 0;
        determinarMenorVersao(qr);
        indicadorModo(qr);
        contagemCaracteres(qr);
        codificarDados(qr);
//     qr->error dividir_em_blocos(qr);
        if (qr->error) {
            if (!qr->modo_corecao_forcado && qr->modo_correcao > L) {
                qr->modo_correcao--;
                continue;
            }
            qr->modo_correcao = -1;
            return qr->error;
        }
        return 0;
    }
    return Msg_n_suport;
}

void determinarMenorVersao(pQR q) {
    FILE *tabela = 0;
    int caracteres[4];
    int i;
    switch (q->modo_correcao) {
        case H:
            tabela = fopen("../src/tabelas/versoes/H.txt", "r");
            break;
        case Q:
            tabela = fopen("../src/tabelas/versoes/Q.txt", "r");
            break;
        case M:
            tabela = fopen("../src/tabelas/versoes/M.txt", "r");
            break;
        case L:
            tabela = fopen("../src/tabelas/versoes/L.txt", "r");
            break;
    }
    if (!tabela) {
        q->error = file_not_found;
        return;
    }
    for (i = 0; i < 40 && !feof(tabela); ++i) {
        fscanf(tabela, "%d %d %d %d", caracteres, caracteres + 1, caracteres + 2, caracteres + 3);
        if (q->tamanhoMensagem <= caracteres[q->modo_codificacao - 1]) {
            q->capacidadeCaracteres = caracteres[q->modo_codificacao - 1];
            q->versao = i + 1;
            fclose(tabela);
            return;
        }
    }
    fclose(tabela);
    q->error = Msg_n_suport;
}

void indicadorModo(pQR qr) {
    qr->strbits = (char *) realloc(qr->strbits, 5);
    qr->size_strbits = 5;
    dec2bin(qr->strbits, pow(2, qr->modo_codificacao - 1), 4);
}

void contagemCaracteres(pQR qr) {
    int bits = 0;
    if (qr->versao >= 27)
        bits = 2;
    else if (qr->versao >= 10)
        bits = 1;
    bits = tabela_quantidade_caracteres[qr->modo_codificacao - 1][bits];
    addletters(qr, bits);
    dec2bin(qr->strbits + 4, qr->tamanhoMensagem, bits);
}

void codificarDados(pQR qr) {
    if (qr->modo_codificacao == NUMERICO) {
        codificarNumerico(qr);
    } else if (qr->modo_codificacao == ALPHANUMERICO) {
        codificarAlphaumerico(qr);
    } else if (qr->modo_codificacao == BYTE) {
        codificarByte(qr);
    }
}

void codificarNumerico(pQR qr) {
    int i = 0, number, bits;
    char grupo[4], bloco[11];
    for (; i < qr->tamanhoMensagem; i += 3) {
        snprintf(grupo, 4, "%s", qr->msg + i);
        number = atoi(grupo);
        bits = number < 10 ? 4 : number < 100 ? 7 : 10;
        dec2bin(bloco, number, bits);
        addletters(qr, bits);
        strcat(qr->strbits, bloco);
    }
}

int convert(char c) {
    if (c <= '9' && c >= '0')
        return c - '0';
    if (c <= 'Z' && c >= 'A')
        return c - 'A' + 10;
    if (c == ' ')return 36;
    else if (c == '$')
        return 37;
    else if (c == '%')
        return 38;
    else if (c == '*')
        return 39;
    else if (c == '+')
        return 40;
    else if (c == '-')
        return 41;
    else if (c == '.')
        return 42;
    else if (c == '/')
        return 43;
    else if (c == ':')
        return 44;
}

void codificarAlphaumerico(pQR qr) {
    int i, number;
    char bloco[12];
    for (i = 0; i < qr->tamanhoMensagem; i += 2) {
        if (qr->msg[i + 1]) {
            number = convert(qr->msg[i]) * 45 + convert(qr->msg[i + 1]);
            dec2bin(bloco, number, 11);
            addletters(qr,11);
        } else{
            number = convert(qr->msg[i]);
            dec2bin(bloco, number, 6);
            addletters(qr,6);
        }
        strcat(qr->strbits,bloco);
    }
}

void codificarByte(pQR qr) {
    char *c;
    char bloco[9];
    for(c = qr->msg;*c;c+=1){
        dec2bin(bloco,*c,8);
        addletters(qr,8);
        strcat(qr->strbits,bloco);
    }
}


void addletters(pQR qr, int size) {
    qr->strbits = (char *) realloc(qr->strbits, qr->size_strbits + size);
    qr->size_strbits += size;
}


void dec2bin(char *buff, int number, int bits) {
    buff[bits--] = 0;
    for (; bits >= 0; bits--) {
        buff[bits] = number % 2 + '0';
        number = number / 2;
    }
}