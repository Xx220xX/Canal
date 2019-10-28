import cmath


def myre(o):
    if isinstance(o, (complex, int, float)):
        return '%.4g |%.4g °' % (abs(o), cmath.phase(o) * 180 / cmath.pi)
    return str(o)


class Carga:
    def __init__(self, Z, estrela=True, neutro=True):
        if estrela:
            self.Za = Z[0]
            self.Zb = Z[1]
            self.Zc = Z[2]
            aux = self.Za * self.Zb + self.Zb * self.Zc + self.Zc * self.Za
            self.Zab = aux / self.Zc
            self.Zbc = aux / self.Za
            self.Zac = aux / self.Zb
        else:
            self.Zab = Z[0]
            self.Zbc = Z[1]
            self.Zca = Z[2]
            aux = self.Zab + self.Zbc + self.Zca
            self.Za = self.Zab * self.Zac / aux
            self.Zb = self.Zab * self.Zbc / aux
            self.Zc = self.Zac * self.Zbc / aux
        self.neutro = neutro

    def __repr__(self):
        return f'\n   za = {myre(self.Za)}\n   zb = {myre(self.Zb)}\n   zc = {myre(self.Zc)}\nneutro %s' \
               % (self.neutro and 'conectado ' or 'desconectado')


class T:
    def __init__(self, E, carga, impedancia_de_linha):
        self.ean = E[0]
        self.ebn = E[1]
        self.ecn = E[2]
        self.sequencia = 'CBA'
        if cmath.phase(self.ean) - cmath.phase(self.ebn) > 0:
            self.sequencia = 'ABC'
        self.z_l = impedancia_de_linha
        self.carga = carga

    def calcular(self):

        ya = 1 / (self.carga.Za + self.z_l)
        yb = 1 / (self.carga.Zb + self.z_l)
        yc = 1 / (self.carga.Zc + self.z_l)
        if not self.carga.neutro:
            self.VNn = (self.ean * ya + self.ebn * yb + self.ecn * yc) / (ya + yb + yc)
        else:
            self.VNn = 0
        self.Ia = (self.ean - self.VNn) * ya
        self.Ib = (self.ebn - self.VNn) * yb
        self.Ic = (self.ecn - self.VNn) * yc
        self.tensao_carga_a = self.carga.Za * self.Ia
        self.tensao_carga_b = self.carga.Zb * self.Ib
        self.tensao_carga_c = self.carga.Zc * self.Ic

        self.defasagem_a =  '%.4g°'%((cmath.phase(self.tensao_carga_a)-cmath.phase(self.Ia))*180/cmath.pi)
        self.defasagem_b =  '%.4g°'%((cmath.phase(self.tensao_carga_b)-cmath.phase(self.Ib))*180/cmath.pi)
        self.defasagem_c =  '%.4g°'%((cmath.phase(self.tensao_carga_c)-cmath.phase(self.Ic))*180/cmath.pi)
        self.potencia_aparente_fornecida = self.ean * self.Ia.conjugate() + self.ebn * self.Ib.conjugate() + self.ecn * self.Ic.conjugate()
        self.P_fornecido = '%.4f' % self.potencia_aparente_fornecida.real
        self.Q_fornecido = '%.4f' % self.potencia_aparente_fornecida.imag
        self.potencia_aparente_consumida = self.carga.Za.real * abs(self.Ia) ** 2 + \
                                           self.carga.Zb.real * abs(self.Ib) ** 2 + \
                                           self.carga.Zc.real * abs(self.Ic) ** 2 + \
                                           1j * (self.carga.Za.imag * abs(self.Ia) ** 2 + \
                                                 self.carga.Zb.imag * abs(self.Ib) ** 2 + \
                                                 self.carga.Zc.imag * abs(self.Ic) ** 2)
        self.P_consumido = '%.4f' % self.potencia_aparente_consumida.real
        self.Q_consumido = '%.4f' % self.potencia_aparente_consumida.imag

    def __repr__(self):
        s = ''
        for k, v in self.__dict__.items():
            s += f'{k} : {myre(v)}\n'
        return s


def fase(modulo, angulo):
    angulo = angulo * cmath.pi / 180
    return modulo * cmath.cos(angulo) + modulo * cmath.sin(angulo) * 1j


e1 = T((fase(86.6, -90), fase(86.6, 30), fase(86.6, 150)), Carga((fase(6, 0), fase(6, 30), fase(5, 45)), neutro=False),
       10)
e2 = T((fase(86.6, 150), fase(86.6, -90), fase(86.6, 30)), Carga((fase(6, 0), fase(6, 30), fase(5, 45)), neutro=False),
       10)
e1.calcular()
e2.calcular()
print(e1)
print(e2)
