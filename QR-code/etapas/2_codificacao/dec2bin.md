## Decimal
É uma base numerica que usamos, a que ensinaram a você.
Existem 10 representações de apenas um algarismo quando esgota-se as 10 então começa a representar com 2 algarismos

por exemplo
> 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
o 10 é a representacao de 1 e 0 seguido por 11, 12, 13.

## Binaria
A base binaria  diferencia-se pois so tem 2 algarismos para representar os numeros.
> 0, 1, 10
Como não existe um terceiro algarismo ja se repete no terceiro termo. A continuação é :
> 11, 100, 101, 110, ...

## Mudança de base
Para mudar de base utiliza-se o algoritmo da divisão. Consiste em pegar o resto da divisao pela base desejada e montar uma sequencia, ao fim invertela.
> 13 / 2 = 6     resto 1
> 6  / 2 = 3     resto 0
> 3  / 2 = 1     resto 1
> 1  / 2 = 0     resto 1
> 
> Logo, 13(10) = 1101(2)

### Codigos
C e C++
```C
void decTo(int dec, char bin[], int base, int bits) {
    bin[bits--] = 0;
    while (bits >= 0) {
        bin[bits] = numToApar(dec % base);
        bits--;
        dec = dec / base;
    }
    if (base != 2) {
        remove0(bin);
    }
}
```



##### linguagem Python
```Python
	bin(number)
```
##### linguagem Lua \0/
```lua
function(number,bits)
	local ans = ''
	for i=0,bits do
		ans = number%2..ans
		number = floor(number/2)
	end
	return ans;
end
```
##### linguagem Java
```Java
Integer.toBinaryString(number)
```
##### linguagem JavaScript
```javaScript
number.toString(2)
```
