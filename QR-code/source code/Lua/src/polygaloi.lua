local log = {1,2,4,8,16,32,64,128,29,58,116,232,205,135,19,38,76,152,45,90,180,117,234,201,143,3,6,12,24,48,96,192,157,39,78,156,37,74,148,53,106,212,181,119,238,193,159,35,70,140,5,10,20,40,80,160,93,186,105,210,185,111,222,161,95,190,97,194,153,47,94,188,101,202,137,15,30,60,120,240,253,231,211,187,107,214,177,127,254,225,223,163,91,182,113,226,217,175,67,134,17,34,68,136,13,26,52,104,208,189,103,206,129,31,62,124,248,237,199,147,59,118,236,197,151,51,102,204,133,23,46,92,184,109,218,169,79,158,33,66,132,21,42,84,168,77,154,41,82,164,85,170,73,146,57,114,228,213,183,115,230,209,191,99,198,145,63,126,252,229,215,179,123,246,241,255,227,219,171,75,150,49,98,196,149,55,110,220,165,87,174,65,130,25,50,100,200,141,7,14,28,56,112,224,221,167,83,166,81,162,89,178,121,242,249,239,195,155,43,86,172,69,138,9,18,36,72,144,61,122,244,245,247,243,251,235,203,139,11,22,44,88,176,125,250,233,207,131,27,54,108,216,173,71,142,1}
local ant = {0,1,25,2,50,26,198,3,223,51,238,27,104,199,75,4,100,224,14,52,141,239,129,28,193,105,248,200,8,76,113,5,138,101,47,225,36,15,33,53,147,142,218,240,18,130,69,29,181,194,125,106,39,249,185,201,154,9,120,77,228,114,166,6,191,139,98,102,221,48,253,226,152,37,179,16,145,34,136,54,208,148,206,143,150,219,189,241,210,19,92,131,56,70,64,30,66,182,163,195,72,126,110,107,58,40,84,250,133,186,61,202,94,155,159,10,21,121,43,78,212,229,172,115,243,167,87,7,112,192,247,140,128,99,13,103,74,222,237,49,197,254,24,227,165,153,119,38,184,180,124,17,68,146,217,35,32,137,46,55,63,209,91,149,188,207,205,144,135,151,178,220,252,190,97,242,86,211,171,20,42,93,158,132,60,57,83,71,109,65,162,31,45,67,216,183,123,164,118,196,23,73,236,127,12,111,246,108,161,59,82,41,157,85,170,251,96,134,177,187,204,62,90,203,89,95,176,156,169,160,81,11,245,22,235,122,117,44,215,79,174,213,233,230,231,173,232,116,214,244,234,168,80,88,175}
function bxor (a,b)
  local r = 0
  for i = 0, 7 do
    local x = a / 2 + b / 2
    if x ~= math.floor (x) then
      r = r + 2^i
    end
    a = math.floor (a / 2)
    b = math.floor (b / 2)
  end
  return math.floor(r)
end

local function somaGaloi(a,b)
	if a==-1 or a==nil then return b end
	if b == -1 or b == nil then return a end
	if a==b then return -1 end
	-- if your lua don't have xor botwise
	return ant[bxor(log[a+1],log[b+1])]
	--return ant[log[a+1]~log[b+1]]
end

local function multGaloi(a,b)
	if a==-1 or b==-1 then return -1 end
	local ans = a+b
	if ans>=255 then ans = ans%255 end
	return ans
end

local function bin2dec(str)
	str = str:reverse()
	local p,ans = 1,0
	for i=1,#str do
		ans = ans+ (str:byte(i)-("0"):byte(1))*p
		p = p*2
	end
	return ans
end

local function prt(a) 
   for k,i in ipairs(a) do
   io.write(i..' ')
   end
   print()
end

local function multPolyGaloi(p1,p2)
	local ans ={}
	for i=1,(#p1 + #p2) do ans[i] = -1 end
	for i=0,#p1-1 do
		for j=0,#p2-1 do
			if(ans[i+j+1]==-1) then
				ans[i+j+1] = multGaloi(p1[i+1],p2[j+1])
			else 
				ans[i+j+1] = somaGaloi(ans[i+j+1],multGaloi(p1[i+1],p2[j+1]))
			end
		end
	end
	local ansf ={}
	for i=1,#ans do
	   if ans[i]  == -1 then break end
	   ansf[i]=ans[i]
	end
	return ansf
end

local function geraPoly(n)
	if n<7 then
		error('\no numero de codigo de corretores deve ser maior que 7')
	end
	ans = {21, 102, 238, 149, 146, 229, 87, 0}
	for i=7,n-1 do
		ans = multPolyGaloi(ans,{i,0})
	end
	return ans
end
table.copyi = function (a,begin ,finish)
	begin = begin and begin >0 and begin or 1
	finish = finish~=nil and (finish < 0 and (#a + finish >0)and (#a+finish) or finish <= #a and finish ) or #a
 	local ans,j={},1
 	for i=begin,finish do ans[j]=a[i] j=j+1 end
 	return ans
 end
 table.cat = function (a,b) 
     local ans = {table.unpack(a)}
     for i,v in ipairs(b) do table.insert(ans,v) end
     return ans
 end
 table.mult = function(t,n)
 	local ans = {}
 	for i=1,n do ans = table.cat(ans,t) end
 	return ans
 end
table.map = function(a,f)
	local ans={};
	for i,v in ipairs(a) do ans[i] = f(v,i) end
	return ans
end

local function divPolyGaloi(num,den)
	local num,den,ld,ans= table.copyi(num),table.copyi(den),#den,{}
	local ln,div= #num
	num = table.cat(table.mult({-1},ld-1),num)
	den = table.cat(table.mult({-1},#num - ld),den)
	for etapas=1,ln do
		print('etapa ',etapas)
		div = table.map(den,function (v,i) return 
		multGaloi(num[#num],v) end)
		num = table.map(num,function(v,i) return somaGaloi(v,div[i]) end)
		num = table.copyi(num,1,-1)
		den = table.copyi(den,2)
	end
	local ans,l={},#num
	prt(num)
	for i=0,l-1 do
		if num[l-i] ~= -1 then
			ans[i+1] = log[num[l-i]+1]
		end
	end
	return ans
end

local function codigoCorretores(stbit,ncode)
	local num,den ={},nil
	for i=0,#stbit-1,8 do
		table.insert(num,bin2dec(stbit:sub(i+1,i+8))) 
		end
	den = geraPoly(ncode)
	codigo = divPolyGaloi(num,den)
	return codigo
end

codigo= codigoCorretores('01100100011110100110010001111010011001000111101000000110011000101001000110111011100110111010000101001110111011100101110000000101',10)

prt(codigo)
print("end")
print([[[129, 56, 95, 81, 170, 235, 43, 33, 47, 183]
codigos
[196, 35, 39, 119, 235, 215, 231, 226, 93, 23]
]])
--print("100, 122, 100, 122, 100, 122, 6, 98, 145, 187, 155, 161, 78, 238, 92, 5")
for k,v in pairs(_G)do
print(k,v)
end