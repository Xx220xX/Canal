# Contagem de caracteres :)
> Finalmente chegamos na codificação 
> para cada modo de codificação utiliza-se um algoritmo diferente
* [NUMERICO](5_numerico.md)
* [AlFANUMERICO](5_alfanumerico.md)
* [BYTE](5_byte.md)

####  Algoritimo
 
```python
    concatenar a strbits com o binario gerado do numero 
        de caracteres contido na mensagem
```


# linguagem C
```C
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
```
# linguagem C++ 
```Cpp
void QR::contagemCaracteres() {
    int bits = 0;
    if(versao >=27)
        bits = 2;
    else if (versao>=10)
        bits = 1;
    bits = tabela_quantidade_caracteres[modo_codificacao-1][bits];
    strbits += dec2bin(tamanhoMensagem,bits);
}
```
# linguagem Python
```Python
    def contagemCaracteres(self):
        if self.versao >= 27:
            bits = 2
        elif self.versao >= 10:
            bits = 1
        else:
            bits = 0
        bits = tabela['quantidade de caracteres'][self.modo_codificao][bits]
        self.strbits = self.strbits + dec2bin(self.tamanho_da_mensagem, bits)
```
# linguagem Lua \0/
```lua
function QR:contagemCaracteres()
        local bits = 1
        if self.versao >= 27 then
            bits = 3
        elseif self.versao >= 10 then
            bits = 2
        end
        bits = tabela.quantidadeCaracteres[self.modo_codificacao][bits]
        self.strbits = self.strbits .. dec2bin(self.tamanho_da_mensagem, bits)
end
```
# linguagem Java
```Java
 public void contagemCaracteres(){
        strbits+= dec2bin(tamanho_da_mensagem,Tabela.quantidadeCaracteres[modo_codificacao-1][versao>=27?2:versao>=10?1:0]);
    }
```
# linguagem JavaScript
```javaScript
contagemCaracteres(){
       this.strbits+= dec2bin(this.msg.length,tabela.quantidadeCaracteres[this.modo_codificacao][this.versao>=27?2:this.versao>=10?1:0]);
    }
```
