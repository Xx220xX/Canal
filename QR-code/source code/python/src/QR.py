NUMERICO = 1
ALPHANUMERICO = 2
BYTE = 3
L = 1
M = 2
Q = 3
H = 4


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
            if 'A' <= c <= 'Z' or c in [' ','$','*','+','.','/']:
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
            # self.contagem_de_caracteres()
            # self.codificarDados()
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
