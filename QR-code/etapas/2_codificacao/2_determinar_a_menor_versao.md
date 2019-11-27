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
```
# linguagem C++ 
```Cpp
void determinarMenorVersao() {
	
}
```
# linguagem Python
```Python
def determinarMenorVersao(self):
    
```
# linguagem Lua \0/
```lua
function QR:determinarMenorVersao()
    
end
```
# linguagem Java
```Java
public void determinarMenorVersao(){
   
}
```
# linguagem JavaScript
```javaScript
determinarMenorVersao(){
  
}
```
