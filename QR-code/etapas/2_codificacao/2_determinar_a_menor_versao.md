# Existe 40 versoes diferentes do qr code :/.
> Cada versão comporta certa quantidade de caracteres.
> Nesta estapa deve-se escolher a menor versão para o seu qr code.

*E AGORA? QUAL DEVO USAR?*

 
 <p align="justify">
 	Para definir a versão a ser usada existe uma 
	<a href = "https://www.thonky.com/qr-code-tutorial/character-capacities">Tabela</a> 
	que é enorme :/
 	mas nosso programa fara isso de forma automatizada. Para isso separaremos as tabelas em 4 arquivos
 	correspondentes aos modos L, M, Q e H. cada linha tera 4 numeros , para modos Numerico, Alphanumerico,byte e kanji(ele nao faz mal para ninguém, deixa ele ue :D , mentira da trabalho tirar). e cada linha corresponde a versão usada (sao 40 linhas hehe).
</p>


 <p align="justify">
 	O algoritimo é simples:
 </p>
 <p align="justify">
 	abrir arquivo txt de acordo com o modo de correcao
 	<p></p>
 	ler um linha 
 	<p></p>
 	verificar se para o modo de codifição tal versão for maior ou igual que a quantidade de caracteres da sua mensagem
 	<p></p>
 	salvar valor encontrado
 	<p></p>
 	caso de erro retornar um erro
</p>



# linguagem C
```C
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
            return;
        }
    }
    q->error = nivel_n_suportado;
}
```
# linguagem C++ 
```Cpp
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
            return;
        }
    }
    error = nivel_n_suportado;
}
```
# linguagem Python
```Python
    def determinarMenorVersao(self):
        titulo = ['L', 'M', 'Q', 'H']
        tabela = open(f"tabelas/versoes/{titulo[self.modo_correcao - 1]}.txt", "r", encoding='utf-8')

        for i in range(40):
            caracteres = [int(j) for j in tabela.readline().split(' ')]
            if self.tamanho_da_mensagem <= caracteres[self.modo_codificao - 1]:
                self.capacidadeCaracteres = caracteres[self.modo_codificao - 1]
                self.versao = i + 1
                tabela.close()
                return
        tabela.close()
        raise QR_exception('modo nao suportado')
```
# linguagem Lua \0/
```lua
function QR:determinarMenorVersao()
    for i=1,#tabelaVesoes do
        if #self.msg<=tabelaVesoes[self.modo_correcao][i][self.modo_codificacao] then
            self.versao = i
            self.capacidade = tabelaVesoes[self.modo_correcao][i][self.modo_codificacao]
            return
        end
    end
    error('nao tem nesse modo de correcao')
end
```
# linguagem Java
```Java
private void determinarMenorVersao() throws QRException.MODO_CORRECAO_NAO_SUPORTADO {
        for (int i = 0; i < 40; i++) {
            if (this.tamanho_da_mensagem <= Tabela.versoes[this.modoCorrecao-1][i][this.modo_codificacao]){
                this.versao = i+1;
                this.capacidade = Tabela.versoes[this.modoCorrecao-1][i][this.modo_codificacao];
                return;
            }
        }
        throw new QRException.MODO_CORRECAO_NAO_SUPORTADO("erro forcado");
    }
```
# linguagem JavaScript
```javaScript
determinarMenorVersao(){
    	for(let i=0;i<40;i++){
   	    	if(this.msg.length <=tabelaVesoes[this.modo_correcao-1][i][this.modo_codificacao]){
	    		this.capacidade = tabelaVesoes[this.modo_correcao-1][i][this.modo_codificacao];
	    		this.versao = i+1;
	    		return;
	    	}
    	}
    	throw Error('mensagem muito longa');
    }
```
