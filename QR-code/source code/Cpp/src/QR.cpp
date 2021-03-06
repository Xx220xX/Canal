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
int tabela_quantidade_caracteres[][3] = {{10, 12, 14},
                                         {9,  11, 13},
                                         {8,  16, 16},
                                         {8,  10, 12}};

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
        contagemCaracteres();
        codificarDados();
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
    strbits = dec2bin(pow(2, modo_codificacao - 1), 4);
}

void QR::contagemCaracteres() {
    int bits = 0;
    if (versao >= 27)
        bits = 2;
    else if (versao >= 10)
        bits = 1;
    bits = tabela_quantidade_caracteres[modo_codificacao - 1][bits];
    strbits += dec2bin(tamanhoMensagem, bits);
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

void QR::codificarDados() {
    string part, bloco;
    int number;
    if (modo_codificacao == NUMERICO) {
        for (int i = 0; i < tamanhoMensagem; i += 3) {
            part = msg.substr(i, i + 3);
            number = stoi(part);
            bloco = dec2bin(number, number < 10 ? 4 : number < 100 ? 7 : 10);
            strbits += bloco;
        }
    } else if (modo_codificacao == ALPHANUMERICO) {
        for (int i = 0; i < tamanhoMensagem; i += 2) {
            part = msg.substr(i, i + 2);
            if (part.length() == 1) {
                number = convert(part[0]);
                bloco = dec2bin(number, 6);
            } else {
                number = convert(part[0]) * 45 + convert(part[1]);
                bloco = dec2bin(number, 11);
            }
            strbits += bloco;
        }
    } else if (modo_codificacao == BYTE) {
        for (int i = 0; i < tamanhoMensagem; i ++) {
            bloco = dec2bin(msg[i], 8);
            cout<<msg[i]<<' '<<bloco<<endl;
            strbits += bloco;
        }
    }
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