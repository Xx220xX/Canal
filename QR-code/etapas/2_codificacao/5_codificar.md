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
void codificarDados(pQR qr) {
    if (qr->modo_codificacao == NUMERICO) {
        codificarNumerico(qr);
    } else if (qr->modo_codificacao == ALPHANUMERICO) {
        codificarAlphaumerico(qr);
    } else if (qr->modo_codificacao == BYTE) {
        codificarByte(qr);
    }
}

void codificarNumerico(pQR qr) {
    int i = 0, number, bits;
    char grupo[4], bloco[11];
    for (; i < qr->tamanhoMensagem; i += 3) {
        snprintf(grupo, 4, "%s", qr->msg + i);
        number = atoi(grupo);
        bits = number < 10 ? 4 : number < 100 ? 7 : 10;
        dec2bin(bloco, number, bits);
        addletters(qr, bits);
        strcat(qr->strbits, bloco);
    }
}


void codificarAlphaumerico(pQR qr) {
    int i, number;
    char bloco[12];
    for (i = 0; i < qr->tamanhoMensagem; i += 2) {
        if (qr->msg[i + 1]) {
            number = convert(qr->msg[i]) * 45 + convert(qr->msg[i + 1]);
            dec2bin(bloco, number, 11);
            addletters(qr,11);
        } else{
            number = convert(qr->msg[i]);
            dec2bin(bloco, number, 6);
            addletters(qr,6);
        }
        strcat(qr->strbits,bloco);
    }
}

void codificarByte(pQR qr) {
    char *c;
    char bloco[9];
    for(c = qr->msg;*c;c+=1){
        dec2bin(bloco,*c,8);
        addletters(qr,8);
        strcat(qr->strbits,bloco);
    }
}
```
# linguagem C++ 
```Cpp
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

```
# linguagem Python
```Python
      def codificarDados(self):
        if self.modo_codificao == NUMERICO:
            self.codificarNumerico()
        elif self.modo_codificao == ALPHANUMERICO:
            self.codificarAlphaumerico()
        elif self.modo_codificao == BYTE:
            self.codificarByte()

    def codificarNumerico(self):
        i = 0
        while i < self.tamanho_da_mensagem:
            number = int(self.msg[i:i + 3])
            bloco = dec2bin(number, number < 10 and 4 or number < 100 and 7 or 10)
            self.strbits += bloco
            i += 3

    def codificarAlphaumerico(self):
        def converter(c):
            if '0' < c < '9':
                return int(c)
            if 'A' < c < 'Z':
                return ord(c) - ord('A') + 10
            return {' ': 36, '$': 37, '%': 38, '*': 39, '+': 40, '-': 41, '.': 42, '/': 43, ':': 44}[c]

        i = 0
        while i < self.tamanho_da_mensagem:
            dupla = self.msg[i:i + 2]
            if len(dupla) == 1:
                number = converter(dupla)
                bloco = dec2bin(number, 6)
            else:
                number = converter(dupla[0]) * 45 + converter(dupla[1])
                bloco = dec2bin(number, 11)
            print(bloco)
            self.strbits += bloco
            i += 2
    def codificarByte(self):
        for c in self.msg:
            bloco = dec2bin(ord(c), 8)
            self.strbits += bloco
```
# linguagem Lua \0/
```lua
function QR:codificarDados()
    local i, part, bloco
    if self.modo_codificacao == NUMERICO then
        i = 1
        while i <= self.tamanho_da_mensagem do
            part = self.msg:sub(i, i + 2)
            number = tonumber(part)
            bloco = dec2bin(number, number < 10 and 4 or number < 100 and 7 or 10)
            self.strbits = self.strbits .. bloco
            i = i + 3
        end
    elseif self.modo_codificacao == ALPHANUMERICO then
        local esp = {}
        for i, v in pairs({ ' ', '$', '%', '*', '+', '-', '.', '/', '=' }) do
            esp[v] = i
        end
        local convert = function(c)
            if c <= '9' and c >= '0' then
                return tonumber(c)
            end
            if c <= 'Z' and c >= 'A' then
                return c:byte(1) - ('A'):byte(1) + 10
            end
            return esp[c]
        end
        i = 1
        while i <= self.tamanho_da_mensagem do
            part = self.msg:sub(i, i + 1)
            number = #part == 1 and convert(part:sub(1, 1)) or convert(part:sub(1, 1)) * 45 + convert(part:sub(2, 2))
            bloco = dec2bin(number, #part == 1 and 6 or 11)
            self.strbits = self.strbits .. bloco
            i = i + 2
        end
    elseif self.modo_codificacao == BYTE then
        for i = 1, self.tamanho_da_mensagem do
            number = self.msg:byte(i)
            bloco = dec2bin(number, 8)
            self.strbits = self.strbits .. bloco
        end
    end
end
```
# linguagem Java
```Java
 
    public void codificarDados() throws QRException {
        String part, bloco;
        int number = 0;
        StringBuilder s = new StringBuilder();
        if (modo_codificacao == MODO_CODIFICACAO.NUMERICO) {
            for (int i = 0; i < tamanho_da_mensagem; i += 3) {
                part = msg.substring(i, i + 3);
                number = Integer.parseInt(part);
                bloco = dec2bin(number, number < 10 ? 4 : number < 100 ? 7 : 10);
                s.append(bloco);
            }
        } else if (modo_codificacao == MODO_CODIFICACAO.ALPHANUMERICO) {
            for (int i = 0; i < tamanho_da_mensagem; i += 2) {
                part = msg.substring(i, i + 2);
                if (part.length() == 1) {
                    number = convert(part.charAt(0));
                    bloco = dec2bin(number, 6);
                } else {
                    number = convert(part.charAt(0)) * 45 + convert(part.charAt(1));
                    bloco = dec2bin(number, 11);
                }
                s.append(bloco);
            }
        } else {
            for (char c : msg.toCharArray()) {
                bloco = dec2bin((int) c, 8);
                s.append(bloco);
            }
        }
        strbits += s.toString();
    }

```
# linguagem JavaScript
```javaScript
    codificarDados(){
 		let convert = (c)=>{
 			if (c <= '9' && c >= '0')
        		return parseInt(c);
    		if (c.charCodeAt(0) <= 'Z'.charCodeAt(0) && c.charCodeAt(0) >= 'A'.charCodeAt(0))
        		return c.charCodeAt(0) - 'A'.charCodeAt(0) + 10;
        	return {' ': 36, '$': 37, '%': 38, '*': 39, '+': 40, '-': 41, '.': 42, '/': 43, ':': 44}[c];	
    	};
    	let part,number,bloco;
    	let sub = (str,begin,finish)=>{
    		let ans = '';
    		for(let i = begin; i<str.length&& i<finish; i++){
    			ans+=str[i];
    		}
    		return ans;
    	};
    	if(this.modo_codificacao==NUMERICO){
    		for (let i=0;i<this.msg.length;i+=3){
    			part = sub(this.msg,i,i+3);
    			print(part);
    			number = parseInt(part);
    			bloco = dec2bin(number, number<10?4:number<100?7:10);
    			this.strbits+=bloco;
    		}
    	}else if(this.modo_codificacao==ALPHANUMERICO){
    		for (let i=0;i<this.msg.length;i+=2){
    			part = sub(this.msg,i,i+2);
    			if (part.length == 1){
    				number = convert(part.charAt(0))
    				bloco = dec2bin(number, 6);	
    			}else{
    				number = convert(part.charAt(0))*45+convert(part.charAt(1))
    				bloco = dec2bin(number, 11);	
    			}  
    			
    			this.strbits+=bloco;
    		}
    	}else if(this.modo_codificacao == BYTE){
    		for(let i=0;i<this.msg.length;i++){
    			number = this.msg.charCodeAt(i);
    			bloco = dec2bin(number, 8);
    			print(this.msg.charAt(i)+' '+bloco)
    			this.strbits+=bloco;
    		}
    	}
    }
}
```
