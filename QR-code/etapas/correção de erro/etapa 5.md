# linguagem C e C++ 
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
# linguagem Python
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
# linguagem Lua \0/
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
# linguagem Java
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
# linguagem Java-script
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
