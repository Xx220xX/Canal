local NUMERICO = 'NUMERICO'
local ALPHANUMERICO = 'ALPHANUMERICO'
local BYTE = 'BYTE'

local QR = {}
QR.__index = QR

QR.new = function ( mensagem )
			return setmetatable({msg = mensagem},QR)
		end

QR.__tostring = function (this)
	s = ''
	for k,v in pairs(this) do
		s = s.. k..': '..v..'\n'
	end
	return s
end

QR.analise = function (this )
	this.modo_codificacao = NUMERICO
	for i = 1,#this.msg  do
		c =this.msg:byte(i)
		if  c>= 48 and c<=57  then 
		elseif c>= 65 and c<= 91 then
			this.modo_codificacao = ALPHANUMERICO
		else 
			this.modo_codificacao = BYTE

			break
		end
	end

end

q = QR.new('http://github.com')
q:analise()
print(q)
--[[
]]