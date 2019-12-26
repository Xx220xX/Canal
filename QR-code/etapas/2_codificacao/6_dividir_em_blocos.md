# Completar string de bits

> - Deve-se encontrar o numero de palavras chaves que o qr terá. Para isso deve-se consultar a [tabela ](table.md).
> > você pode pegar a tabela em formato de matriz [aqui](tablematriz.md)
> - Complete com 0 a string de bits ate o tamanho ser um multiplo de 8
> - Para saber quantos bits a string de bits deve conter você deve multiplicar o total de palavras por 8 obtendo o numero de bits total
> - Complete a String de bits com 11101100 00010001 até conter o numero total de bits
> > 11101100 00010001 equivale a 236 e 17




####  Algoritimo
 
```Fortran
    Enquanto modulo por 8 do tamanho da string de bits diferente de zero faça
       string de bits <-- string de bits concatenado com "0"
    Enquanto tamanho da string de bits somado 16 menor ou igual ao numero de palavras vezes 8 faça
       string de bits <-- string de bits concatenado com "1110110000010001"
    Se  tamanho da string de bits menor que o  numero de palavras vezes 8 faça
       string de bits <-- string de bits concatenado com "11101100"
```

# linguagem C
```C



```
# linguagem C++ 
```Cpp

```
# linguagem Python
```Python

```
# linguagem Lua \0/
```lua

```
# linguagem Java
```Java
 
```
# linguagem JavaScript
```javaScript

```
