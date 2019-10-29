local NUMERICO = 'NUMERICO'
local ALPHANUMERICO = 'ALPHANUMERICO'
local BYTE = 'BYTE'

local QR = {}
QR.__index = QR
function QR:new(msg)
    return setmetatable({msg=msg},self)
end
function QR:analise()
    local c ;
    self.modo_codificacao = NUMERICO
    for i = 1,#self.msg do
        c = self.msg:byte(i)
        if c>=48 and c<=57 then
        elseif c>=65 and c<=91 then
            self.modo_codificacao = ALPHANUMERICO
        else
            self.modo_codificacao = BYTE
            break
        end
    end
end
q = QR:new('454A5')
q:analise()
