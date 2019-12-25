local NUMERICO, ALPHANUMERICO, BYTE = 1, 2, 3;
local L, M, Q, H = 1, 2, 3, 4;
local tabela = { vesoes = { { { 41, 25, 17, 10 }, { 77, 47, 32, 20 }, { 127, 77, 53, 32 }, { 187, 114, 78, 48 }, { 255, 154, 106, 65 }, { 322, 195, 134, 82 }, { 370, 224, 154, 95 }, { 461, 279, 192, 118 }, { 552, 335, 230, 141 }, { 652, 395, 271, 167 }, { 772, 468, 321, 198 }, { 883, 535, 367, 226 }, { 1022, 619, 425, 262 }, { 1101, 667, 458, 282 }, { 1250, 758, 520, 320 }, { 1408, 854, 586, 361 }, { 1548, 938, 644, 397 }, { 1725, 1046, 718, 442 }, { 1903, 1153, 792, 488 }, { 2061, 1249, 858, 528 }, { 2232, 1352, 929, 572 }, { 2409, 1460, 1003, 618 }, { 2620, 1588, 1091, 672 }, { 2812, 1704, 1171, 721 }, { 3057, 1853, 1273, 784 }, { 3283, 1990, 1367, 842 }, { 3517, 2132, 1465, 902 }, { 3669, 2223, 1528, 940 }, { 3909, 2369, 1628, 1002 }, { 4158, 2520, 1732, 1066 }, { 4417, 2677, 1840, 1132 }, { 4686, 2840, 1952, 1201 }, { 4965, 3009, 2068, 1273 }, { 5253, 3183, 2188, 1347 }, { 5529, 3351, 2303, 1417 }, { 5836, 3537, 2431, 1496 }, { 6153, 3729, 2563, 1577 }, { 6479, 3927, 2699, 1661 }, { 6743, 4087, 2809, 1729 }, { 7089, 4296, 2953, 1817 } }
, { { 34, 20, 14, 8 }, { 63, 38, 26, 16 }, { 101, 61, 42, 26 }, { 149, 90, 62, 38 }, { 202, 122, 84, 52 }, { 255, 154, 106, 65 }, { 293, 178, 122, 75 }, { 365, 221, 152, 93 }, { 432, 262, 180, 111 }, { 513, 311, 213, 131 }, { 604, 366, 251, 155 }, { 691, 419, 287, 177 }, { 796, 483, 331, 204 }, { 871, 528, 362, 223 }, { 991, 600, 412, 254 }, { 1082, 656, 450, 277 }, { 1212, 734, 504, 310 }, { 1346, 816, 560, 345 }, { 1500, 909, 624, 384 }, { 1600, 970, 666, 410 }, { 1708, 1035, 711, 438 }, { 1872, 1134, 779, 480 }, { 2059, 1248, 857, 528 }, { 2188, 1326, 911, 561 }, { 2395, 1451, 997, 614 }, { 2544, 1542, 1059, 652 }, { 2701, 1637, 1125, 692 }, { 2857, 1732, 1190, 732 }, { 3035, 1839, 1264, 778 }, { 3289, 1994, 1370, 843 }, { 3486, 2113, 1452, 894 }, { 3693, 2238, 1538, 947 }, { 3909, 2369, 1628, 1002 }, { 4134, 2506, 1722, 1060 }, { 4343, 2632, 1809, 1113 }, { 4588, 2780, 1911, 1176 }, { 4775, 2894, 1989, 1224 }, { 5039, 3054, 2099, 1292 }, { 5313, 3220, 2213, 1362 }, { 5596, 3391, 2331, 1435 } }
, { { 27, 16, 11, 7 }, { 48, 29, 20, 12 }, { 77, 47, 32, 20 }, { 111, 67, 46, 28 }, { 144, 87, 60, 37 }, { 178, 108, 74, 45 }, { 207, 125, 86, 53 }, { 259, 157, 108, 66 }, { 312, 189, 130, 80 }, { 364, 221, 151, 93 }, { 427, 259, 177, 109 }, { 489, 296, 203, 125 }, { 580, 352, 241, 149 }, { 621, 376, 258, 159 }, { 703, 426, 292, 180 }, { 775, 470, 322, 198 }, { 876, 531, 364, 224 }, { 948, 574, 394, 243 }, { 1063, 644, 442, 272 }, { 1159, 702, 482, 297 }, { 1224, 742, 509, 314 }, { 1358, 823, 565, 348 }, { 1468, 890, 611, 376 }, { 1588, 963, 661, 407 }, { 1718, 1041, 715, 440 }, { 1804, 1094, 751, 462 }, { 1933, 1172, 805, 496 }, { 2085, 1263, 868, 534 }, { 2181, 1322, 908, 559 }, { 2358, 1429, 982, 604 }, { 2473, 1499, 1030, 634 }, { 2670, 1618, 1112, 684 }, { 2805, 1700, 1168, 719 }, { 2949, 1787, 1228, 756 }, { 3081, 1867, 1283, 790 }, { 3244, 1966, 1351, 832 }, { 3417, 2071, 1423, 876 }, { 3599, 2181, 1499, 923 }, { 3791, 2298, 1579, 972 }, { 3993, 2420, 1663, 1024 } }
, { { 17, 10, 7, 4 }, { 34, 20, 14, 8 }, { 58, 35, 24, 15 }, { 82, 50, 34, 21 }, { 106, 64, 44, 27 }, { 139, 84, 58, 36 }, { 154, 93, 64, 39 }, { 202, 122, 84, 52 }, { 235, 143, 98, 60 }, { 288, 174, 119, 74 }, { 331, 200, 137, 85 }, { 374, 227, 155, 96 }, { 427, 259, 177, 109 }, { 468, 283, 194, 120 }, { 530, 321, 220, 136 }, { 602, 365, 250, 154 }, { 674, 408, 280, 173 }, { 746, 452, 310, 191 }, { 813, 493, 338, 208 }, { 919, 557, 382, 235 }, { 969, 587, 403, 248 }, { 1056, 640, 439, 270 }, { 1108, 672, 461, 284 }, { 1228, 744, 511, 315 }, { 1286, 779, 535, 330 }, { 1425, 864, 593, 365 }, { 1501, 910, 625, 385 }, { 1581, 958, 658, 405 }, { 1677, 1016, 698, 430 }, { 1782, 1080, 742, 457 }, { 1897, 1150, 790, 486 }, { 2022, 1226, 842, 518 }, { 2157, 1307, 898, 553 }, { 2301, 1394, 958, 590 }, { 2361, 1431, 983, 605 }, { 2524, 1530, 1051, 647 }, { 2625, 1591, 1093, 673 }, { 2735, 1658, 1139, 701 }, { 2927, 1774, 1219, 750 }, { 3057, 1852, 1273, 784 } }
}, quantidadeCaracteres = { { 10, 12, 14 }, { 9, 11, 13 }, { 8, 16, 16 }, { 8, 10, 12 } }
};
local QR = {}
QR.__index = QR
function QR.new(msg)
    local log = io.open('log.md', 'w')
    return setmetatable({ msg = msg, modo_correcao = H, tentar_todos_modos_de_correcao = true, tamanho_da_mensagem = #msg, log = log }, QR)
end

function QR:table(...)
    self.log:write('|')
    for i, v in pairs({ ... }) do
        self.log:write(v .. ' | ')
    end
    self.log:write('\n')
end
function QR:print(msg)
    self.log:write(msg .. '\n')
end

function QR:__tostring()
    local s = ''
    for k, v in pairs(self) do
        s = s .. k .. '  ' .. tostring(v) .. '\n'
    end
    return s;
end
function QR:analise()
    self:print('## Analise')
    local c;
    self.modo_codificacao = NUMERICO
    for i = 1, #self.msg do
        c = self.msg:byte(i)
        if c >= 48 and c <= 57 then
        elseif (c >= 65 and c <= 91) or c == (' '):byte() or c == ('$'):byte() or c == ('*'):byte() or c == ('+'):byte() or c == ('.'):byte() or c == ('/'):byte() or c == (':'):byte() then
            self.modo_codificacao = ALPHANUMERICO
        else
            self.modo_codificacao = BYTE
            break
        end
    end
    self:print(self.modo_codificacao == ALPHANUMERICO and 'ALPHANUMERICO' or self.modo_codificacao == NUMERICO and 'NUMERICO' or self.modo_codificacao == BYTE and 'BYTE')
end

function QR:codificar()
    self:print('## Codificar')
    local function _codifcar()
        self:determinarMenorVersao()
        self:indicadorModo()
        self:contagemCaracteres()
        self:codificarDados()
        --[[ self:dividir_em_blocos()--]]
    end
    :: catch ::
    local status, err = pcall(_codifcar)
    if not status then
        if self.tentar_todos_modos_de_correcao and self.modo_correcao > L then
            self.modo_correcao = self.modo_correcao - 1
            goto catch
        else
            error("mensagem nao suportada\n" .. err)
        end
    end
end
local function dec2bin(number, bits)
    local ans = ''
    number = math.floor(number)
    for i = 1, bits do
        ans = number % 2 .. ans
        number = math.floor(number / 2)
    end
    return ans
end
function QR:determinarMenorVersao()
    for i = 1, #tabela.vesoes do
        if self.tamanho_da_mensagem <= tabela.vesoes[self.modo_correcao][i][self.modo_codificacao] then
            self.versao = i
            self.capacidade = tabela.vesoes[self.modo_correcao][i][self.modo_codificacao]
            self:print('#### Menor versão\n Versão ' .. i)
            return
        end
    end
    error('nao tem nesse modo de correcao')
end
function QR:indicadorModo()
    self:print('#### Indicador de modo')
    self:print('| indicador de modo | \n | :---- |\n| ' .. dec2bin(2 ^ (self.modo_codificacao - 1), 4) .. ' |')
    self.strbits = dec2bin(2 ^ (self.modo_codificacao - 1), 4)
end
function QR:contagemCaracteres()
    local bits = 1
    if self.versao >= 27 then
        bits = 3
    elseif self.versao >= 10 then
        bits = 2
    end

    bits = tabela.quantidadeCaracteres[self.modo_codificacao][bits]
    self:print('#### Contagem de caracteres\n| Tamanho da mensagem | bits | binario |\n | :---- | :---- | :---- |')
    self.strbits = self.strbits .. dec2bin(self.tamanho_da_mensagem, bits)
    self:table(self.tamanho_da_mensagem, bits, dec2bin(self.tamanho_da_mensagem, bits))
end
function QR:codificarDados()
    local i, part, bloco
    self:print('#### Codificação')
    if self.modo_codificacao == NUMERICO then
        self:print('| numero | bits | binary |\n | :----: | :----: | :---- |')
        i = 1
        while i <= self.tamanho_da_mensagem do
            part = self.msg:sub(i, i + 2)
            number = tonumber(part)
            bloco = dec2bin(number, number < 10 and 4 or number < 100 and 7 or 10)
            self.strbits = self.strbits .. bloco
            self:table(number, (number < 10 and 4 or number < 100 and 7 or 10), bloco)
            i = i + 3
        end
    elseif self.modo_codificacao == ALPHANUMERICO then
        local esp = {}
        for i, v in pairs({ ' ', '$', '%', '*', '+', '-', '.', '/', '=' }) do
            esp[v] = i
        end
        local convert = function(c)
            if c <= '9' and c >= '0' then
                return tonumber(c)
            end
            if c <= 'Z' and c >= 'A' then
                return c:byte(1) - ('A'):byte(1) + 10
            end
            return esp[c]
        end
        self:print('| Dupla | 1° | 2° | resultado | bits | binario |\n| :----: | :----: | :---- | :----: | :----: | :----: |')
        i = 1
        while i <= self.tamanho_da_mensagem do
            part = self.msg:sub(i, i + 1)
            number = #part == 1 and convert(part:sub(1, 1)) or convert(part:sub(1, 1)) * 45 + convert(part:sub(2, 2))
            bloco = dec2bin(number, #part == 1 and 6 or 11)
            self.strbits = self.strbits .. bloco
            self:table(part,  convert(part:sub(1, 1)), #part == 2 and convert(part:sub(2, 2)) or '-' , number, #part == 1 and 6 or 11, bloco)
            i = i + 2
        end
    elseif self.modo_codificacao == BYTE then
        self:table('Letra', 'Byte', 'binary')
        self:table(':----:', ':----:', ':----:')
        for i = 1, self.tamanho_da_mensagem do
            number = self.msg:byte(i)
            bloco = dec2bin(number, 8)
            self.strbits = self.strbits .. bloco
            self:table(self.msg:sub(i, i), number, bloco)
        end
    end
end
q = QR.new('ORLD,')
q:analise()
q:codificar()
print(q)