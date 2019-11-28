//
// Created by PC on 27/11/2019.
//

#ifndef QR_CPP_QR_H
#define QR_CPP_QR_H

#include <iostream>
#include <cctype>
#include <utility>

using namespace std;


class QR{
public:
    string msg= "";
    int modo_codificacao=0;

    explicit QR(string msg) {
        this->msg = std::move(msg);
        this->tamanhoMensagem = this->msg.length();
    }
    void analise() ;
    void codificar() ;
    bool tentar_todos_modos_de_correcao=0;
    int modo_correcao=0;
    int error=0;
    int tamanhoMensagem=0;
    int capacidadeCaracteres=0;
    int versao=0;

    void determinarMenorVersao();
    friend std::ostream &operator<<(std::ostream &os, QR &v);
};
#endif //QR_CPP_QR_H
