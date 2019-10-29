# :D
Nesta estapa deve-se verificar em qual modo iremos codificar nossa mensagem
a logica é bem simples:
<p  align="justify" > iniciar o modo como <b>NUMERICO</b></p>
<p  align="justify">Percorrer a mensagem inteira</p>
<p  align="justify">Se encontrar uma numero - não fazer nada.</p>
<p  align="justify">Se encontrar uma letra maiuscula - mudar para modo <b>ALPHANUMERICO</b></p>
<p  align="justify">Caso as consdições acima nao forem satisfeitas - mudar para modo <b>BYTE</b> e parar a busca.</p>




# linguagem C
```C
void analise(QR &qr) {
        qr->modo_codificacao = NUMERICO;
        for (const char *c = qr->msg; *c; c += 1) {
            if (isdigit(*c))
                continue;
            if (isupper(*c)) {
                qr->modo_codificacao = ALPHANUMERICO;
                continue;
            }
            qr->modo_codificacao = BYTE;
            break;
        }
    }
```
# linguagem C++ 
```Cpp
void analise() {
        modo_codificacao = NUMERICO;
        for (const char *c = msg.c_str(); *c; c += 1) {
            if (isdigit(*c))
                continue;
            if (isupper(*c)) {
                modo_codificacao = ALPHANUMERICO;
                continue;
            }
            modo_codificacao = BYTE;
            break;
        }
    }
```
# linguagem Python
```Python
def analise(self):
    self.modo_codificacao = NUMERICO
    for c in self.msg:
        if c.isdigit():
            continue
        if 'A' <= c <= 'Z':
            self.modo_codificacao = ALPHANUMERICO
            continue
        self.modo_codificacao = BYTE
        break

```
# linguagem Lua \0/
```lua
function QR:analise()
    local c ;
    self.modo_codificacao = NUMERICO
    for i = 1,#self.msg do
        c = self.msg:byte(i)
        if c>=48 and c<=57 then
        elseif c>=65 and c<=91 then
            self.modo_codificacao = ALPHANUMERICO
        else
            self.modo_codificacao = BYTE
            break
        end
    end
end

```
# linguagem Java
```Java
public void analise(){
    for(char c:msg.toCharArray()){
        if(Character.isDigit(c))
            continue;
        if(Character.isAlphabetic(c) && Character.isUpperCase(c) ){
            modo_codificacao = MODO_CODIFICACAO.ALPHANUMERICO;
        	continue;
        }
        modo_codificacao = MODO_CODIFICACAO.BYTE;
    	break;
    }
}
```
# linguagem JavaScript
```javaScript
analise(){
    this.modo_codificacao = NUMERICO;
    let c ;
    for (let i = 0;i<this.msg.length;i++){
        c = this.msg.charCodeAt(i);
        if(c>= 48 && c <= 57)
            continue;
        if(c>=65 && c<=91){
            this.modo_codificacao = ALPHANUMERICO;
            continue;
        }
        this.modo_codificacao = BYTE;
        break;
    }
}
```
