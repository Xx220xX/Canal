# QR Code
> Para fazer um Qr code deve seguir algumas etapas
> 1 -  verificar qual tipo de codificação usar
> 2 -  analisar dados
> 3 -  correcao de erros


### Como fazer?
##### Correção de erros
###### divisão de polinomios
> tendo um polinomio numerador e outro denomidador deve-se pegar o coeficiente do maior grau do numerador e dividir pelo coeficiente do maior grau do denominador, e subtrair esses expoentes, assim obtera um coeficiente de um novo polinomio,criando um polinomio temporario,
>depois deve-se multiplicar esse temporario pelo denominador e subtrar do numerador.

###### Campo de galoes 2^8
> É um conjunto numerico limitado de 0 a 255 onde todas operacoes resultarao neste intervalo

###### Gerar potencias de 2
> se um numero for maior igual  que 2^8 entao deve-se fazer 256 xor 285
>2^9 = 2^8*2 = 2^8 xor 285 * 2 = 29*2=58
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
```java-script
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
