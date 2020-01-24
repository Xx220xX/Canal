#include "QR.h"
#include <math.h>

int tabela_quantidade_caracteres[][3] = {{10, 12, 14},
                                         {9,  11, 13},
                                         {8,  16, 16},
                                         {8,  10, 12}};
                                         
int numeroPalavras[][24] = {
                {19, 7, 1, 19, 0, 0, 16, 10, 1, 16, 0, 0, 13, 13, 1, 13, 0, 0, 9, 17, 1, 9, 0, 0},
                {34, 10, 1, 34, 0, 0, 28, 16, 1, 28, 0, 0, 22, 22, 1, 22, 0, 0, 16, 28, 1, 16, 0, 0},
                {55, 15, 1, 55, 0, 0, 44, 26, 1, 44, 0, 0, 34, 18, 2, 17, 0, 0, 26, 22, 2, 13, 0, 0},
                {80, 20, 1, 80, 0, 0, 64, 18, 2, 32, 0, 0, 48, 26, 2, 24, 0, 0, 36, 16, 4, 9, 0, 0},
                {108, 26, 1, 108, 0, 0, 86, 24, 2, 43, 0, 0, 62, 18, 2, 15, 2, 16, 46, 22, 2, 11, 2, 12},
                {136, 18, 2, 68, 0, 0, 108, 16, 4, 27, 0, 0, 76, 24, 4, 19, 0, 0, 60, 28, 4, 15, 0, 0},
                {156, 20, 2, 78, 0, 0, 124, 18, 4, 31, 0, 0, 88, 18, 2, 14, 4, 15, 66, 26, 4, 13, 1, 14},
                {194, 24, 2, 97, 0, 0, 154, 22, 2, 38, 2, 39, 110, 22, 4, 18, 2, 19, 86, 26, 4, 14, 2, 15},
                {232, 30, 2, 116, 0, 0, 182, 22, 3, 36, 2, 37, 132, 20, 4, 16, 4, 17, 100, 24, 4, 12, 4, 13},
                {274, 18, 2, 68, 2, 69, 216, 26, 4, 43, 1, 44, 154, 24, 6, 19, 2, 20, 122, 28, 6, 15, 2, 16},
                {324, 20, 4, 81, 0, 0, 254, 30, 1, 50, 4, 51, 180, 28, 4, 22, 4, 23, 140, 24, 3, 12, 8, 13},
                {370, 24, 2, 92, 2, 93, 290, 22, 6, 36, 2, 37, 206, 26, 4, 20, 6, 21, 158, 28, 7, 14, 4, 15},
                {428, 26, 4, 107, 0, 0, 334, 22, 8, 37, 1, 38, 244, 24, 8, 20, 4, 21, 180, 22, 12, 11, 4, 12},
                {461, 30, 3, 115, 1, 116, 365, 24, 4, 40, 5, 41, 261, 20, 11, 16, 5, 17, 197, 24, 11, 12, 5, 13},
                {523, 22, 5, 87, 1, 88, 415, 24, 5, 41, 5, 42, 295, 30, 5, 24, 7, 25, 223, 24, 11, 12, 7, 13},
                {589, 24, 5, 98, 1, 99, 453, 28, 7, 45, 3, 46, 325, 24, 15, 19, 2, 20, 253, 30, 3, 15, 13, 16},
                {647, 28, 1, 107, 5, 108, 507, 28, 10, 46, 1, 47, 367, 28, 1, 22, 15, 23, 283, 28, 2, 14, 17, 15},
                {721, 30, 5, 120, 1, 121, 563, 26, 9, 43, 4, 44, 397, 28, 17, 22, 1, 23, 313, 28, 2, 14, 19, 15},
                {795, 28, 3, 113, 4, 114, 627, 26, 3, 44, 11, 45, 445, 26, 17, 21, 4, 22, 341, 26, 9, 13, 16, 14},
                {861, 28, 3, 107, 5, 108, 669, 26, 3, 41, 13, 42, 485, 30, 15, 24, 5, 25, 385, 28, 15, 15, 10, 16},
                {932, 28, 4, 116, 4, 117, 714, 26, 17, 42, 0, 0, 512, 28, 17, 22, 6, 23, 406, 30, 19, 16, 6, 17},
                {1006, 28, 2, 111, 7, 112, 782, 28, 17, 46, 0, 0, 568, 30, 7, 24, 16, 25, 442, 24, 34, 13, 0, 0},
                {1094, 30, 4, 121, 5, 122, 860, 28, 4, 47, 14, 48, 614, 30, 11, 24, 14, 25, 464, 30, 16, 15, 14, 16},
                {1174, 30, 6, 117, 4, 118, 914, 28, 6, 45, 14, 46, 664, 30, 11, 24, 16, 25, 514, 30, 30, 16, 2, 17},
                {1276, 26, 8, 106, 4, 107, 1000, 28, 8, 47, 13, 48, 718, 30, 7, 24, 22, 25, 538, 30, 22, 15, 13, 16},
                {1370, 28, 10, 114, 2, 115, 1062, 28, 19, 46, 4, 47, 754, 28, 28, 22, 6, 23, 596, 30, 33, 16, 4, 17},
                {1468, 30, 8, 122, 4, 123, 1128, 28, 22, 45, 3, 46, 808, 30, 8, 23, 26, 24, 628, 30, 12, 15, 28, 16},
                {1531, 30, 3, 117, 10, 118, 1193, 28, 3, 45, 23, 46, 871, 30, 4, 24, 31, 25, 661, 30, 11, 15, 31, 16},
                {1631, 30, 7, 116, 7, 117, 1267, 28, 21, 45, 7, 46, 911, 30, 1, 23, 37, 24, 701, 30, 19, 15, 26, 16},
                {1735, 30, 5, 115, 10, 116, 1373, 28, 19, 47, 10, 48, 985, 30, 15, 24, 25, 25, 745, 30, 23, 15, 25, 16},
                {1843, 30, 13, 115, 3, 116, 1455, 28, 2, 46, 29, 47, 1033, 30, 42, 24, 1, 25, 793, 30, 23, 15, 28, 16},
                {1955, 30, 17, 115, 0, 0, 1541, 28, 10, 46, 23, 47, 1115, 30, 10, 24, 35, 25, 845, 30, 19, 15, 35, 16},
                {2071, 30, 17, 115, 1, 116, 1631, 28, 14, 46, 21, 47, 1171, 30, 29, 24, 19, 25, 901, 30, 11, 15, 46, 16},
                {2191, 30, 13, 115, 6, 116, 1725, 28, 14, 46, 23, 47, 1231, 30, 44, 24, 7, 25, 961, 30, 59, 16, 1, 17},
                {2306, 30, 12, 121, 7, 122, 1812, 28, 12, 47, 26, 48, 1286, 30, 39, 24, 14, 25, 986, 30, 22, 15, 41, 16},
                {2434, 30, 6, 121, 14, 122, 1914, 28, 6, 47, 34, 48, 1354, 30, 46, 24, 10, 25, 1054, 30, 2, 15, 64, 16},
                {2566, 30, 17, 122, 4, 123, 1992, 28, 29, 46, 14, 47, 1426, 30, 49, 24, 10, 25, 1096, 30, 24, 15, 46, 16},
                {2702, 30, 4, 122, 18, 123, 2102, 28, 13, 46, 32, 47, 1502, 30, 48, 24, 14, 25, 1142, 30, 42, 15, 32, 16},
                {2812, 30, 20, 117, 4, 118, 2216, 28, 40, 47, 7, 48, 1582, 30, 43, 24, 22, 25, 1222, 30, 10, 15, 67, 16},
                {2956, 30, 19, 118, 6, 119, 2334, 28, 18, 47, 31, 48, 1666, 30, 34, 24, 34, 25, 1276, 30, 20, 15, 61, 16}
        };

void expandSize(pQR qr, int bits);

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
    char *modos= "LMQH?";
    printf("%c",modos[q->modo_correcao-1]);
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
        completaBits(qr);
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
    char file[] = "../src/tabelas/versoes/H.txt";
    file[23]= "LMQH"[q->modo_correcao];
    int i;
    tabela = fopen(file, "r");
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
    dec2bin(qr->strbits, (int)pow(2, qr->modo_codificacao - 1), 4);
}

void contagemCaracteres(pQR qr) {
    int bits = 0;
    if (qr->versao >= 27)
        bits = 2;
    else if (qr->versao >= 10)
        bits = 1;
    bits = tabela_quantidade_caracteres[qr->modo_codificacao - 1][bits];
    expandSize(qr, bits);
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
        expandSize(qr, bits);
        strcat(qr->strbits, bloco);
    }
}
void completaBits(pQR qr){
   qr->numeroPalavras = numeroPalavras[qr->versao-1][6*(qr->modo_correcao-1)];
   while(strlen(qr->strbits)%8){
   	 expandSize(qr, 1);
   	 strcat(qr->strbits, "0");
   	}
   while(strlen(qr->strbits)+16<=qr->numeroPalavras){
   	expandSize(qr, 16);
   	strcat(qr->strbits,"1110110000010001");
   	}
   	if(strlen(qr->strbits)<qr->numeroPalavras){
   		expandSize(qr, 8);
   		strcat(qr->strbits,"11101100");
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
            expandSize(qr, 11);
        } else{
            number = convert(qr->msg[i]);
            dec2bin(bloco, number, 6);
            expandSize(qr, 6);
        }
        strcat(qr->strbits,bloco);
    }
}

void codificarByte(pQR qr) {
    char *c;
    char bloco[9];
    for(c = qr->msg;*c;c+=1){
        dec2bin(bloco,*c,8);
        expandSize(qr, 8);
        strcat(qr->strbits,bloco);
    }
}


void expandSize(pQR qr, int bits){
    qr->strbits = (char *) realloc(qr->strbits, qr->size_strbits + bits);
    qr->size_strbits += bits;
}


void dec2bin(char *buff, int number, int bits) {
    buff[bits--] = 0;
    for (; bits >= 0; bits--) {
        buff[bits] = number % 2 + '0';
        number = number / 2;
    }
}
int bin2dec(char *bin) {
    int l = strlen(bin),pot=1,ans=0,i;
    for(i=0;i<l;i++,pot*=2)
    	ans+= (bin[l-i-1]-'0')*pot;
    return ans;
}

