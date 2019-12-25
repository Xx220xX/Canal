NUMERICO = 1
ALPHANUMERICO = 2
BYTE = 3
L = 1
M = 2
Q = 3
H = 4
tabela = {'quantidade de caracteres': [[10, 12, 14], [9, 11, 13], [8, 16, 16], [8, 10, 12]],}


class QR_exception(Exception):
    def __init__(self, *args: object) -> None:
        super().__init__(*args)


def dec2bin(number, bits):
    ans = ''
    for i in range(bits):
        ans = str(number % 2) + ans
        number = number // 2
    return ans


class QR:
    def __init__(self, msg, forcar_modo_de_correcao=False):
        self.capacidadeCaracteres = None
        self.msg = msg
        self.tamanho_da_mensagem = len(msg)
        self.modo_correcao_forcado = forcar_modo_de_correcao
        self.modo_correcao = H
        self.versao = None
        self.strbits = None
        # etapa 1-7 analise de dados

    def __repr__(self):
        s = ''
        for i, v in self.__dict__.items():
            s += f'{str(i).replace("_", " ")} : {v}\n'
        return s

    def analise(self):
        self.modo_codificao = NUMERICO
        for c in self.msg:
            if c.isdigit():
                continue
            if 'A' <= c <= 'Z' or c in [' ', '$', '*', '+', '.', '/']:
                self.modo_codificao = ALPHANUMERICO
                continue
            self.modo_codificao = BYTE
            break

    def codificar(self, flag=None):
        if not self.modo_correcao_forcado and flag != 'repeat':
            self.modo_correcao = H
        try:
            self.determinarMenorVersao()
            self.indicadorModo()
            self.contagemCaracteres()
            self.codificarDados()
            # self.dividir_em_blocos()
        except QR_exception as e:
            if self.modo_correcao_forcado and self.modo_correcao > L:
                self.modo_correcao -= 1
                self.codificar('repeat')
                return
            raise QR_exception("mensagem nao suportada")

    def determinarMenorVersao(self):
        titulo = ['L', 'M', 'Q', 'H']
        tabela = open(f"tabelas/versoes/{titulo[self.modo_correcao - 1]}.txt", "r", encoding='utf-8')
        for i in range(40):
            caracteres = [int(j) for j in tabela.readline().split(' ')]
            if self.tamanho_da_mensagem <= caracteres[self.modo_codificao - 1]:
                self.capacidadeCaracteres = caracteres[self.modo_codificao - 1]
                self.versao = i + 1
                tabela.close()
                return
        tabela.close()
        raise QR_exception('modo nao suportado')

    def indicadorModo(self):
        self.strbits = dec2bin(2 ** (self.modo_codificao - 1), 4)

    def contagemCaracteres(self):
        if self.versao >= 27:
            bits = 2
        elif self.versao >= 10:
            bits = 1
        else:
            bits = 0
        bits = tabela['quantidade de caracteres'][self.modo_codificao][bits]
        self.strbits = self.strbits + dec2bin(self.tamanho_da_mensagem, bits)

    def codificarDados(self):
        if self.modo_codificao == NUMERICO:
            self.codificarNumerico()
        elif self.modo_codificao == ALPHANUMERICO:
            self.codificarAlphaumerico()
        elif self.modo_codificao == BYTE:
            self.codificarByte()

    def codificarNumerico(self):
        i = 0
        while i < self.tamanho_da_mensagem:
            number = int(self.msg[i:i + 3])
            bloco = dec2bin(number, number < 10 and 4 or number < 100 and 7 or 10)
            self.strbits += bloco
            i += 3

    def codificarAlphaumerico(self):
        def converter(c):
            if '0' < c < '9':
                return int(c)
            if 'A' < c < 'Z':
                return ord(c) - ord('A') + 10
            return {' ': 36, '$': 37, '%': 38, '*': 39, '+': 40, '-': 41, '.': 42, '/': 43, ':': 44}[c]

        i = 0
        while i < self.tamanho_da_mensagem:
            dupla = self.msg[i:i + 2]
            print(f'"{dupla}"',end=' -> ')
            if len(dupla) == 1:
                number = converter(dupla)
                bloco = dec2bin(number, 6)
            else:
                number = converter(dupla[0]) * 45 + converter(dupla[1])
                bloco = dec2bin(number, 11)
            print(bloco)
            self.strbits += bloco
            i += 2

    def codificarByte(self):
        for c in self.msg:
            bloco = dec2bin(ord(c), 8)
            self.strbits += bloco
