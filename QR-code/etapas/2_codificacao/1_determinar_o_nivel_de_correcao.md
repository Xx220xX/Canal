# Existem 4 tipos de modo de correcao
 1. L (low)  7% 
 2. M (medim) 15%
 3. Q (Quartile) 25%  
 4. H (Hight) 30%

 <p align="justify">
 	Para este QR tentaremos codificar no maior modo.
 	Para isso usaremos a recursão para caso falhe com o modo H 
 	tente novamente com o modo Q e caso falhe com L retorna um erro.
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
  public void codificar() throws QR_exception {
        try {
            determinarMenorVersao();
//            identicador_de_modo();
//            contagem_de_caracteres();
//            codificarDados();
//            dividir_em_blocos();

        } catch (QR_exception.MODO_CORRECAO e) {
            if (tentar_todos_modos_de_correcao && modo_correcao > MODO_CORRECAO.L) {
                modo_correcao--;
                codificar();
                return;
            }
            throw new QR_exception("mensagem não suportada");
        }
    }
```
# linguagem JavaScript
```javaScript
codificar(){
  
}
```
