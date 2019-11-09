#include "QR.h"


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
            printf("Q.txt");
            break;
        case H:
            printf("H");
            break;
        default:
            printf("Ainda nao definido");
    }
    printf("\n");
    printf("Versao: %d\n",q->versao);
    printf("capacidade de caracteres: %d\n",q->capacidadeCaracteres);
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
//     qr->error dividir_em_blocos(qr);
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

void determinarMenorVersao(pQR q) {
    FILE *tabela = 0;
    int caracteres[4];
    int i;
    switch (q->modo_correcao){
        case H:
            tabela = fopen("../src/tabelas/versoes/H.txt","r");
            break;
    case Q:
            tabela = fopen("../src/tabelas/versoes/Q.txt","r");
            break;
    case M:
            tabela = fopen("../src/tabelas/versoes/M.txt","r");
            break;
        case L:
            tabela = fopen("../src/tabelas/versoes/L.txt","r");
            break;
    }
    if(!tabela){
        q->error = file_not_found;
        return;
    }
    for ( i = 0; i < 40 && !feof(tabela); ++i) {
        fscanf(tabela,"%d %d %d %d",caracteres,caracteres+1,caracteres+2,caracteres+3);
        if(q->tamanhoMensagem<= caracteres[q->modo_codificacao-1]){
            q->capacidadeCaracteres = caracteres[q->modo_codificacao-1];
            q->versao = i+1;
            return;
        }
    }
    q->error = nivel_n_suportado;
}


