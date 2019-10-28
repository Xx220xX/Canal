NUMERICO = 1
ALPHANUMERICO = 2
BYTE = 3


class QR_CODE:
    def __init__(self, msg):
        self.msg = msg

    # etapa 1-7 analise de dados
    def analise(self):
        self.codificao = NUMERICO
        for c in self.msg:

            if c.isdigit():
                continue
            if c.isalnum() and c.isupper():
                print(c)
                self.codificao = ALPHANUMERICO
                continue
            self.codificao = BYTE
            break


        if self.codificao == NUMERICO:
            print('NUMERICO')
        elif self.codificao == ALPHANUMERICO:
            print('ALPHANUMERICO')
        else:
            print('BYTE')

