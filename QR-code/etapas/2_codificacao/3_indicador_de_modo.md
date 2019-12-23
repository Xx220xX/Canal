# Indicador de Modo :D
> Cada modo de codificação possui uma representação
> nesta seção sera adicionado a mensagem o indicador de modo.
> A tabela abaixo indica o modo e o correspondente indicador

| Modo de codificação | Indicador de modo | forma decimal |
| :---- | :---- | :---- |
| Númerico | 0001 | 1 |
| Alfanumerico | 0010 | 2 |
| Byte | 0100 | 4 |
| Kanji| 1000 | 8 |


Antes consulte esta [seção](dec2bin.md) onde possui uma função para passar decimal para binario.

####  Algoritimo
 
```python
    O indicador de modo sera dado por 2^(modo_codificacao-1)
    converta o numero gerado em binario 
    salve na mensagem de bits
```


# linguagem C
```C
void indicadorModo(QR *qr){
    dec2bin(qr->bits,pow(2,qr->modo_codificacao-1),4);
}
```
# linguagem C++ 
```Cpp

void QR::indicadorModo(){
    strbits = dec2bin(pow(2,qr->modo_codificacao-1),4);
}
```
# linguagem Python
```Python

def indicadorModo(self):
    self.strbits = dec2bin(2**(self.modo_codificacao-1),4)

```
# linguagem Lua \0/
```lua
function QR:indicadorModo()
    self.strbits = dec2bin(2^(self.modo_codificacao-1),4)
end
```
# linguagem Java
```Java
private void indicadorModo(){
    this.strbits = dec2bin(Math.pow(2,modo_codificacao-1),4);
}
```
# linguagem JavaScript
```javaScript
indicadorModo(){
    this.strbits = dec2bin(Math.pow(2,this.modo_codificacao -1),4)
}
```
