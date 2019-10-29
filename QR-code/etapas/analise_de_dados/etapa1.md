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
