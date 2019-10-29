NUMERICO = 'Numerico'
ALPHANUMERICO = 'ALPHANUMERICO'
BYTE = 'BYTE'

import re


class QR:
    def __init__(self, msg):
        self.msg = msg

        # etapa 1-7 analise de dados

    def analise(self):
        self.modo_codificao = NUMERICO
        for c in self.msg:
            if c.isdigit():
                continue
            if 'A' <= c <= 'Z':
                self.modo_codificao = ALPHANUMERICO
                continue
            self.modo_codificao = BYTE
            break
        print(self.modo_codificao)


a = QR('OLÁ')
a.analise()
