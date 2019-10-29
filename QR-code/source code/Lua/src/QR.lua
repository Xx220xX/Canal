local NUMERICO = 'NUMERICO'
local ALPHANUMERICO = 'ALPHANUMERICO'
local BYTE = 'BYTE'

local L = 1
local M = 2
local Q = 3
local H = 4

local QR = {}
QR.__index = QR
function QR:new(msg)
    return setmetatable({ msg = msg, modo_correcao = H ,tentar_todos_modos_de_correcao = true}, self)
end
function QR:analise()
    local c;
    self.modo_codificacao = NUMERICO
    for i = 1, #self.msg do
        c = self.msg:byte(i)
        if c >= 48 and c <= 57 then
        elseif c >= 65 and c <= 91 then
            self.modo_codificacao = ALPHANUMERICO
        else
            self.modo_codificacao = BYTE
            break
        end
    end
end
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
q = QR:new('454A5')
q:analise()
q:codificar()