# Existe 40 versoes diferentes do qr code :/.

*E AGORA? QUAL DEVO USAR?*

 
 <p align="justify">
 	Para definir a versão a ser usada existe uma [tabela]< a href = "https://www.thonky.com/qr-code-tutorial/character-capacities"></p> que é enorme :/
 	mas nosso programa fara isso de forma automatizada. Para isso separaremos as tabelas em 4 arquivos
 	correspondentes aos modos L, M, Q e H. cada linha tera 4 numeros , para modos Numerico, Alphanumerico,byte e kanji(ele nao faz mal para ninguém, deixa ele ue :D , mentira da trabalho tirar). e cada linha corresponde a versão usada (sao 40 linhas hehe).
</p>


 <p align="justify">
 	O algoritimo é simples:
 </p>
 <p align="justify">
 	abrir arquivo txt de acordo com o modo de correcao
 	<p></p>
 	ler um linha 
 	<p></p>
 	verificar se para o modo de codifição tal versão for maior ou igual que a quantidade de caracteres da sua mensagem
 	<p></p>
 	salvar valor encontrado
 	<p></p>
 	caso de erro retornar um erro
</p>



# linguagem C
```C
void codificar(QR &qr) {
	int error = 0;
	error  = determinarMenorVersao(qr,error);
	error  = identicador_de_modo(qr,error);
	error  = contagem_de_caracteres(qr,error);
	error  = codificarDados(qr,error);
	error  = dividir_em_blocos(qr,error);
	if(error){
		if(qr->tentar_todos_modos_de_correcao && qr->modo_correcao >L){
			qr->modo_correcao--;
			codificar(qr);
			return ;
		}
		exit(-1);
	}
}
```
# linguagem C++ 
```Cpp
void codificar() {
	try{
		determinarMenorVersao();
	 	identicador_de_modo();
		contagem_de_caracteres();
		codificarDados();
		dividir_em_blocos();
	}catch(QR_exception e){
		if(tentar_todos_modos_de_correcao){
			modo_correcao--;
			codificar();
			return;
		}
		throw (QR_exception("mensagem nao suportada"));
	}
}
```
# linguagem Python
```Python
def codificar(self):
    try:
    	self.determinarMenorVersao()
	 	self.identicador_de_modo()
		self.contagem_de_caracteres()
		self.codificarDados()
		self.dividir_em_blocos()
    except Exception as e:
    	if self.tentar_todos_modos_de_correcao and self.modo_correcao > L:
    		self.modo_correcao-=1
    		codificar()
    		return
    	raise QR_exception("mensagem nao suportada")
```
# linguagem Lua \0/
```lua
function QR:codificar()
    local function _codifcar()
       --print('tentando com', self.modo_correcao)
        a = 1/0
        self.determinarMenorVersao()
        self.identicador_de_modo()
        self.contagem_de_caracteres()
        self.codificarDados()
        self.dividir_em_blocos()
    end
    :: catch ::
    local status , err = pcall(_codifcar)
    if not status then
        if self.tentar_todos_modos_de_correcao and self.modo_correcao > L then
            self.modo_correcao = self.modo_correcao - 1
            goto catch
        else
            error("mensagem nao suportada\n"..err )
        end
    end
end
```
# linguagem Java
```Java
public void codificar(){
   
}
```
# linguagem JavaScript
```javaScript
codificar(){
  
}
```
