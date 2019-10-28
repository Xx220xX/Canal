# QR Code
> Para fazer um Qr code deve seguir algumas etapas
> 1.  analisar dados
> 2.  codificacao de dados
> 3.  correcao de erros
> 4.  estrutura de dados
> 5.  Colocar dados na matriz
> 6.  Mascaramento de dados
> 7.  informação de formato e  versao



<<<<<<< HEAD
=======
###### Campo de galoes 2^8
> É um conjunto numerico limitado de 0 a 255 onde todas operacoes resultarao neste intervalo

###### Gerar potencias de 2
> se um numero for maior igual  que 2^8 entao deve-se fazer 256 xor 285
>2^9 = 2^8*2 = 2^8 xor 285 * 2 = 29*2=58
C:
```C
unsigned int galoi(unsigned int numero) {
    unsigned int a;
    if (numero >= 256U && (numero ^ 285U) < 256U)
        return numero ^ 285U;
    if (numero > 256U) {
        a = 2U * galoi(numero / 2U);
        if (a > 256U && (a ^ 285U) < 256U)
            return a ^ 285U;
        return a;
    }
    return numero;
}
```
Python:
```Python
def galoi(numero):
    if numero >= 256 and (numero ^ 285) < 256:
        return numero ^ 285
    if numero > 256:
        a = 2 * galoi(numero // 2)
        if a > 256 and (a ^ 285) < 256:
            return a ^ 285
        return a
    return numero

```
LUA:
```lua
function galoi(numero) 
    if numero >= 256 and (numero ~ 285) < 256 then
        return numero ~ 285
    end
    if numero > 256 then
        a = 2 * galoi(math.floor(numero // 2))
        if a > 256 and (a ~ 285) < 256 then
            return a ~ 285
        end
        return a
    end
    return numero
end

```
Java:
```Java
public static int galoi(int numero){
        int a;
        if (numero >= 256 && (numero ^ 285) < 256)
        return numero ^ 285;
        if (numero > 256) {
            a = 2 * galoi(numero / 2);
            if (a > 256 && (a ^ 285) < 256)
                return a ^ 285;
            return a;
        }
        return numero;
    }
```
javascript:
```javascript
function galoi(numero) {
    if (numero >= 256 && (numero ^ 285) < 256 ){
        return numero ^ 285;
    }
    if (numero > 256 ){
        a = 2 * galoi(numero /2);
        if(a > 256 && (a ^ 285) < 256 )
            return a ^ 285;
        
        return a;
    }
    return numero;
}
```
>>>>>>> 80d97bb51551d4a1e6ca143b3eb574a28ab67a7a
