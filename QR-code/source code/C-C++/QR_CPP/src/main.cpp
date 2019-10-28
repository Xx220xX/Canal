#include <iostream>
#include <cctype>
using namespace std;
#define NUMERICO 1
#define ALPHANUMERICO 2
#define BYTE 3
class QR{
public:
    string msg;
    int modo_codificacao;
    QR(string msg){
        this->msg = msg;
    }
    void analise(){
        modo_codificacao = NUMERICO;
        for (const char *c = msg.c_str(); *c ;c +=1) {
            if(isdigit(*c)){
                continue;
            }
            if(*c>='A'&&*c<='Z'){
                modo_codificacao = ALPHANUMERICO;
                continue;
            }
            modo_codificacao = BYTE;
            break;
        }
        cout<<modo_codificacao;
    }
};
int main(){
    QR q = QR("545854854Á94");
    q.analise();
    return 0;
}