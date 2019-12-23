#include "QR.h"
#include <cmath>

#define NUMERICO 1
#define ALPHANUMERICO 2
#define BYTE 3

#define  L 1
#define  M 2
#define  Q 3
#define  H 4
enum {
    Msg_n_suport = 1, nivel_n_suportado = 2, file_not_found = 3
};

string err2str(int code);

void QR::analise() {
    modo_codificacao = NUMERICO;
    for (const char *c = msg.c_str(); *c; c += 1) {
        if (isdigit(*c))
            continue;
        if (isupper(*c) || *c == ' ' || *c == '$' || *c == '*' || *c == '+' || *c == '.' || *c == '/' ||
            *c == ':') {
            modo_codificacao = ALPHANUMERICO;
            continue;
        }
        modo_codificacao = BYTE;
        break;
    }
}

void QR::codificar() {
    if (!this->tentar_todos_modos_de_correcao) {
        this->modo_correcao = H;
    }
    while (this->modo_correcao >= L) {
        this->error = 0;
        determinarMenorVersao();
        indicadorModo();
//     contagem_de_caracteres();
//     codificarDados();
//     this->error dividir_em_blocos();
        if (this->error) {
            if (!this->tentar_todos_modos_de_correcao && this->modo_correcao > L) {
                this->modo_correcao--;
                continue;
            }
            this->modo_correcao = -1;

        }
        return;
    }

}

void QR::determinarMenorVersao() {
    FILE *tabela = nullptr;
    int caracteres[4];
    switch (modo_correcao) {
        case H:
            tabela = fopen("../src/tabelas/versoes/H.txt", "r");
            break;
        case Q:
            tabela = fopen("../srg/tabelas/versoes/Q.txt", "r");
            break;
        case M:
            tabela = fopen("../src/tabelas/versoes/M.txt", "r");
            break;
        case L:
            tabela = fopen("../src/tabelas/versoes/L.txt", "r");
            break;
    }
    if (!tabela) {
        error = file_not_found;
        return;
    }
    for (int i = 0; i < 40 && !feof(tabela); ++i) {
        fscanf(tabela, "%d %d %d %d", caracteres, caracteres + 1, caracteres + 2, caracteres + 3);
        if (tamanhoMensagem <= caracteres[modo_codificacao - 1]) {
            capacidadeCaracteres = caracteres[modo_codificacao - 1];
            versao = i + 1;
            fclose(tabela);
            return;
        }
    }
    fclose(tabela);
    error = nivel_n_suportado;
}

string dec2bin(int number, int bits) {
    string ans = "";
    for (; bits > 0; bits--) {
        ans = to_string(number % 2) + ans;
        number = number / 2;
    }
    return ans;
}

void QR::indicadorModo() {
    strbits = dec2bin(pow(2, modo_codificacao), 4);
}

std::ostream &operator<<(std::ostream &os, QR &v) {
    if (v.error) {
        os << "erro: " << err2str(v.error);
        return os;
    }
    os << "msg: " << v.msg <<
       "\nmodo de codificacao: " << v.modo_codificacao <<
       "\nModo de correcao: " << v.modo_correcao <<
       "\nVersao: " << v.versao <<
       "\nTamanho da msg: " << v.tamanhoMensagem <<
       "\ncapacidade de caracteres: " << v.capacidadeCaracteres <<
       "\nStr bits : " << v.strbits;
    return os;
}

string err2str(int code) {
    switch (code) {
        case Msg_n_suport:
            return "mensagem nao suportada";
        case nivel_n_suportado:
            return "nivel_n_suportado nao suportada";
        case file_not_found:
            return "Arquivo nao encontrado";
        case 0:
            return "";
    }
    return "falha na geracao do qr";
}