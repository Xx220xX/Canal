import java.util.*;

public class QR {
    public interface MODO_CODIFICACAO {
        int NUMERICO = 1;
        int ALPHANUMERICO = 2;
        int BYTE = 3;
    }

    public interface MODO_CORRECAO {
        int L = 1;
        int M = 2;
        int Q = 3;
        int H = 4;
    }


    private String msg, strbits;
    private int modo_codificacao = MODO_CODIFICACAO.NUMERICO;
    private int tamanho_da_mensagem;

    private int modoCorrecao = MODO_CORRECAO.H;
    private boolean modoCorrecaoForcado = false;

    private int versao;
    private int capacidade;
    private int numeroPalavras;


    public QR(String msg, int modoCorrecao) {
        this.msg = msg;
        this.modoCorrecao = modoCorrecao;
        this.modoCorrecaoForcado = true;
    }

    public QR(String msg) {
        this.msg = msg;
        this.tamanho_da_mensagem = msg.length();
    }

    @Override
    public String toString() {
        return " msg = '" + msg + "\'\n" +
                " tamanho da mensagem = " + tamanho_da_mensagem + '\n' +
                " modo de codificacao = " + new String[]{"Numerico", "Alfanumerico", "Byte"}[modo_codificacao - 1] + '\n' +
                " modo de correcao = " + new String[]{"L", "M", "Q", "H"}[modoCorrecao - 1] + '\n' +
                " modo de correcao forcado = " + modoCorrecaoForcado + '\n' +
                " versão = " + versao + '\n' +
                " capacidade = " + capacidade + '\n' +
                " numero total de palavras chaves = " + numeroPalavras + '\n' +
                " strbits = '" + strbits + '\'' + '\n'
                ;
    }

    /**
     * ETAPA 1
     **/
    public void analise() {
        List<Character> caracteres = Arrays.asList(' ', '$', '*', '+', '.', '/', ':');
        for (char c : msg.toCharArray()) {
            if (Character.isDigit(c))
                continue;
            if (Character.isUpperCase(c) || caracteres.contains(c)) {
                modo_codificacao = MODO_CODIFICACAO.ALPHANUMERICO;
                continue;
            }
            modo_codificacao = MODO_CODIFICACAO.BYTE;
            break;
        }
    }

    /**
     * ETAPA 2 codificacao
     **/
    public void codificacao() throws QRException {
        try {
            determinarMenorVersao();
            indicadorModo();
            contagemCaracteres();
            codificarDados();
            completaBits();

        } catch (QRException.MODO_CORRECAO_NAO_SUPORTADO e) {
            if (!modoCorrecaoForcado && modoCorrecao > MODO_CORRECAO.L) {
                modoCorrecao--;
                codificacao();
                return;
            }
            throw new QRException("Mensagem não suportada");
        }
    }

    private void determinarMenorVersao() throws QRException.MODO_CORRECAO_NAO_SUPORTADO {
        for (int i = 0; i < 40; i++) {
            if (this.tamanho_da_mensagem <= Tabela.versoes[this.modoCorrecao - 1][i][this.modo_codificacao]) {
                this.versao = i + 1;
                this.capacidade = Tabela.versoes[this.modoCorrecao - 1][i][this.modo_codificacao];
                return;
            }
        }
        throw new QRException.MODO_CORRECAO_NAO_SUPORTADO("erro forcado");
    }

    public void indicadorModo() {
        strbits = dec2bin((int) Math.pow(2, modo_codificacao - 1), 4);
    }

    public void contagemCaracteres() {
        strbits += dec2bin(tamanho_da_mensagem, Tabela.quantidadeCaracteres[modo_codificacao - 1][versao >= 27 ? 2 : versao >= 10 ? 1 : 0]);
    }

    private int convert(char c) throws QRException {
        if (c <= '9' && c >= '0')
            return c - '0';
        if (c <= 'Z' && c >= 'A')
            return c - 'A' + 10;
        if (c == ' ') return 36;
        else if (c == '$')
            return 37;
        else if (c == '%')
            return 38;
        else if (c == '*')
            return 39;
        else if (c == '+')
            return 40;
        else if (c == '-')
            return 41;
        else if (c == '.')
            return 42;
        else if (c == '/')
            return 43;
        else if (c == ':')
            return 44;
        throw new QRException("Algo deu errado");
    }

    public void codificarDados() throws QRException {
        String part, bloco;
        int number = 0;
        StringBuilder s = new StringBuilder();
        if (modo_codificacao == MODO_CODIFICACAO.NUMERICO) {
            for (int i = 0; i < tamanho_da_mensagem; i += 3) {
                part = sub(msg, i, i + 3);
                number = Integer.parseInt(part);
                bloco = dec2bin(number, number < 10 ? 4 : number < 100 ? 7 : 10);
                s.append(bloco);
            }
        } else if (modo_codificacao == MODO_CODIFICACAO.ALPHANUMERICO) {
            for (int i = 0; i < tamanho_da_mensagem; i += 2) {
                part = sub(msg, i, i + 2);
                if (part.length() == 1) {
                    number = convert(part.charAt(0));
                    bloco = dec2bin(number, 6);
                } else {
                    number = convert(part.charAt(0)) * 45 + convert(part.charAt(1));
                    bloco = dec2bin(number, 11);
                }
                s.append(bloco);
            }
        } else {
            for (char c : msg.toCharArray()) {
                bloco = dec2bin((int) c, 8);
                s.append(bloco);
            }
        }
        strbits += s.toString();
    }

    public void completaBits() {
        numeroPalavras = Tabela.numeroPalavras[versao - 1][6 * (modoCorrecao - 1)];
        while (strbits.length() % 8 != 0)
            strbits += "0";
        while (strbits.length()+16<=numeroPalavras*8)
            strbits+= dec2bin(236,8)+ dec2bin(17,8);
        if(strbits.length()<numeroPalavras*8)
            strbits+= dec2bin(236,8);

    }


    public String dec2bin(int number, int bits) {
        StringBuilder ans = new StringBuilder();
        for (; bits > 0; bits--) {
            ans.insert(0, number % 2);
            number = number / 2;
        }
        return ans.toString();
    }

    private String sub(String s, int begin, int end) {
        StringBuilder ans = new StringBuilder();
        int length = s.length();
        for (int i = begin; i < length && i < end; i++)
            ans.append(s.charAt(i));
        return ans.toString();
    }

    public static class QRException extends Exception {
        public QRException(String msg) {
            super(msg);
        }

        public static class MODO_CORRECAO_NAO_SUPORTADO extends QRException {
            public MODO_CORRECAO_NAO_SUPORTADO(String msg) {
                super(msg);
            }
        }
    }

    protected interface Tabela {
        int[][][] versoes = {{{41, 25, 17, 10}, {77, 47, 32, 20}, {127, 77, 53, 32}, {187, 114, 78, 48}, {255, 154, 106, 65}, {322, 195, 134, 82}, {370, 224, 154, 95}, {461, 279, 192, 118}, {552, 335, 230, 141}, {652, 395, 271, 167}, {772, 468, 321, 198}, {883, 535, 367, 226}, {1022, 619, 425, 262}, {1101, 667, 458, 282}, {1250, 758, 520, 320}, {1408, 854, 586, 361}, {1548, 938, 644, 397}, {1725, 1046, 718, 442}, {1903, 1153, 792, 488}, {2061, 1249, 858, 528}, {2232, 1352, 929, 572}, {2409, 1460, 1003, 618}, {2620, 1588, 1091, 672}, {2812, 1704, 1171, 721}, {3057, 1853, 1273, 784}, {3283, 1990, 1367, 842}, {3517, 2132, 1465, 902}, {3669, 2223, 1528, 940}, {3909, 2369, 1628, 1002}, {4158, 2520, 1732, 1066}, {4417, 2677, 1840, 1132}, {4686, 2840, 1952, 1201}, {4965, 3009, 2068, 1273}, {5253, 3183, 2188, 1347}, {5529, 3351, 2303, 1417}, {5836, 3537, 2431, 1496}, {6153, 3729, 2563, 1577}, {6479, 3927, 2699, 1661}, {6743, 4087, 2809, 1729}, {7089, 4296, 2953, 1817}}
                , {{34, 20, 14, 8}, {63, 38, 26, 16}, {101, 61, 42, 26}, {149, 90, 62, 38}, {202, 122, 84, 52}, {255, 154, 106, 65}, {293, 178, 122, 75}, {365, 221, 152, 93}, {432, 262, 180, 111}, {513, 311, 213, 131}, {604, 366, 251, 155}, {691, 419, 287, 177}, {796, 483, 331, 204}, {871, 528, 362, 223}, {991, 600, 412, 254}, {1082, 656, 450, 277}, {1212, 734, 504, 310}, {1346, 816, 560, 345}, {1500, 909, 624, 384}, {1600, 970, 666, 410}, {1708, 1035, 711, 438}, {1872, 1134, 779, 480}, {2059, 1248, 857, 528}, {2188, 1326, 911, 561}, {2395, 1451, 997, 614}, {2544, 1542, 1059, 652}, {2701, 1637, 1125, 692}, {2857, 1732, 1190, 732}, {3035, 1839, 1264, 778}, {3289, 1994, 1370, 843}, {3486, 2113, 1452, 894}, {3693, 2238, 1538, 947}, {3909, 2369, 1628, 1002}, {4134, 2506, 1722, 1060}, {4343, 2632, 1809, 1113}, {4588, 2780, 1911, 1176}, {4775, 2894, 1989, 1224}, {5039, 3054, 2099, 1292}, {5313, 3220, 2213, 1362}, {5596, 3391, 2331, 1435}}
                , {{27, 16, 11, 7}, {48, 29, 20, 12}, {77, 47, 32, 20}, {111, 67, 46, 28}, {144, 87, 60, 37}, {178, 108, 74, 45}, {207, 125, 86, 53}, {259, 157, 108, 66}, {312, 189, 130, 80}, {364, 221, 151, 93}, {427, 259, 177, 109}, {489, 296, 203, 125}, {580, 352, 241, 149}, {621, 376, 258, 159}, {703, 426, 292, 180}, {775, 470, 322, 198}, {876, 531, 364, 224}, {948, 574, 394, 243}, {1063, 644, 442, 272}, {1159, 702, 482, 297}, {1224, 742, 509, 314}, {1358, 823, 565, 348}, {1468, 890, 611, 376}, {1588, 963, 661, 407}, {1718, 1041, 715, 440}, {1804, 1094, 751, 462}, {1933, 1172, 805, 496}, {2085, 1263, 868, 534}, {2181, 1322, 908, 559}, {2358, 1429, 982, 604}, {2473, 1499, 1030, 634}, {2670, 1618, 1112, 684}, {2805, 1700, 1168, 719}, {2949, 1787, 1228, 756}, {3081, 1867, 1283, 790}, {3244, 1966, 1351, 832}, {3417, 2071, 1423, 876}, {3599, 2181, 1499, 923}, {3791, 2298, 1579, 972}, {3993, 2420, 1663, 1024}}
                , {{17, 10, 7, 4}, {34, 20, 14, 8}, {58, 35, 24, 15}, {82, 50, 34, 21}, {106, 64, 44, 27}, {139, 84, 58, 36}, {154, 93, 64, 39}, {202, 122, 84, 52}, {235, 143, 98, 60}, {288, 174, 119, 74}, {331, 200, 137, 85}, {374, 227, 155, 96}, {427, 259, 177, 109}, {468, 283, 194, 120}, {530, 321, 220, 136}, {602, 365, 250, 154}, {674, 408, 280, 173}, {746, 452, 310, 191}, {813, 493, 338, 208}, {919, 557, 382, 235}, {969, 587, 403, 248}, {1056, 640, 439, 270}, {1108, 672, 461, 284}, {1228, 744, 511, 315}, {1286, 779, 535, 330}, {1425, 864, 593, 365}, {1501, 910, 625, 385}, {1581, 958, 658, 405}, {1677, 1016, 698, 430}, {1782, 1080, 742, 457}, {1897, 1150, 790, 486}, {2022, 1226, 842, 518}, {2157, 1307, 898, 553}, {2301, 1394, 958, 590}, {2361, 1431, 983, 605}, {2524, 1530, 1051, 647}, {2625, 1591, 1093, 673}, {2735, 1658, 1139, 701}, {2927, 1774, 1219, 750}, {3057, 1852, 1273, 784}}
        };
        int[][] quantidadeCaracteres = {{10, 12, 14},
                {9, 11, 13},
                {8, 16, 16},
                {8, 10, 12}};
        int[][] numeroPalavras = {
                {19, 7, 1, 19, 0, 0, 16, 10, 1, 16, 0, 0, 13, 13, 1, 13, 0, 0, 9, 17, 1, 9, 0, 0},
                {34, 10, 1, 34, 0, 0, 28, 16, 1, 28, 0, 0, 22, 22, 1, 22, 0, 0, 16, 28, 1, 16, 0, 0},
                {55, 15, 1, 55, 0, 0, 44, 26, 1, 44, 0, 0, 34, 18, 2, 17, 0, 0, 26, 22, 2, 13, 0, 0},
                {80, 20, 1, 80, 0, 0, 64, 18, 2, 32, 0, 0, 48, 26, 2, 24, 0, 0, 36, 16, 4, 9, 0, 0},
                {108, 26, 1, 108, 0, 0, 86, 24, 2, 43, 0, 0, 62, 18, 2, 15, 2, 16, 46, 22, 2, 11, 2, 12},
                {136, 18, 2, 68, 0, 0, 108, 16, 4, 27, 0, 0, 76, 24, 4, 19, 0, 0, 60, 28, 4, 15, 0, 0},
                {156, 20, 2, 78, 0, 0, 124, 18, 4, 31, 0, 0, 88, 18, 2, 14, 4, 15, 66, 26, 4, 13, 1, 14},
                {194, 24, 2, 97, 0, 0, 154, 22, 2, 38, 2, 39, 110, 22, 4, 18, 2, 19, 86, 26, 4, 14, 2, 15},
                {232, 30, 2, 116, 0, 0, 182, 22, 3, 36, 2, 37, 132, 20, 4, 16, 4, 17, 100, 24, 4, 12, 4, 13},
                {274, 18, 2, 68, 2, 69, 216, 26, 4, 43, 1, 44, 154, 24, 6, 19, 2, 20, 122, 28, 6, 15, 2, 16},
                {324, 20, 4, 81, 0, 0, 254, 30, 1, 50, 4, 51, 180, 28, 4, 22, 4, 23, 140, 24, 3, 12, 8, 13},
                {370, 24, 2, 92, 2, 93, 290, 22, 6, 36, 2, 37, 206, 26, 4, 20, 6, 21, 158, 28, 7, 14, 4, 15},
                {428, 26, 4, 107, 0, 0, 334, 22, 8, 37, 1, 38, 244, 24, 8, 20, 4, 21, 180, 22, 12, 11, 4, 12},
                {461, 30, 3, 115, 1, 116, 365, 24, 4, 40, 5, 41, 261, 20, 11, 16, 5, 17, 197, 24, 11, 12, 5, 13},
                {523, 22, 5, 87, 1, 88, 415, 24, 5, 41, 5, 42, 295, 30, 5, 24, 7, 25, 223, 24, 11, 12, 7, 13},
                {589, 24, 5, 98, 1, 99, 453, 28, 7, 45, 3, 46, 325, 24, 15, 19, 2, 20, 253, 30, 3, 15, 13, 16},
                {647, 28, 1, 107, 5, 108, 507, 28, 10, 46, 1, 47, 367, 28, 1, 22, 15, 23, 283, 28, 2, 14, 17, 15},
                {721, 30, 5, 120, 1, 121, 563, 26, 9, 43, 4, 44, 397, 28, 17, 22, 1, 23, 313, 28, 2, 14, 19, 15},
                {795, 28, 3, 113, 4, 114, 627, 26, 3, 44, 11, 45, 445, 26, 17, 21, 4, 22, 341, 26, 9, 13, 16, 14},
                {861, 28, 3, 107, 5, 108, 669, 26, 3, 41, 13, 42, 485, 30, 15, 24, 5, 25, 385, 28, 15, 15, 10, 16},
                {932, 28, 4, 116, 4, 117, 714, 26, 17, 42, 0, 0, 512, 28, 17, 22, 6, 23, 406, 30, 19, 16, 6, 17},
                {1006, 28, 2, 111, 7, 112, 782, 28, 17, 46, 0, 0, 568, 30, 7, 24, 16, 25, 442, 24, 34, 13, 0, 0},
                {1094, 30, 4, 121, 5, 122, 860, 28, 4, 47, 14, 48, 614, 30, 11, 24, 14, 25, 464, 30, 16, 15, 14, 16},
                {1174, 30, 6, 117, 4, 118, 914, 28, 6, 45, 14, 46, 664, 30, 11, 24, 16, 25, 514, 30, 30, 16, 2, 17},
                {1276, 26, 8, 106, 4, 107, 1000, 28, 8, 47, 13, 48, 718, 30, 7, 24, 22, 25, 538, 30, 22, 15, 13, 16},
                {1370, 28, 10, 114, 2, 115, 1062, 28, 19, 46, 4, 47, 754, 28, 28, 22, 6, 23, 596, 30, 33, 16, 4, 17},
                {1468, 30, 8, 122, 4, 123, 1128, 28, 22, 45, 3, 46, 808, 30, 8, 23, 26, 24, 628, 30, 12, 15, 28, 16},
                {1531, 30, 3, 117, 10, 118, 1193, 28, 3, 45, 23, 46, 871, 30, 4, 24, 31, 25, 661, 30, 11, 15, 31, 16},
                {1631, 30, 7, 116, 7, 117, 1267, 28, 21, 45, 7, 46, 911, 30, 1, 23, 37, 24, 701, 30, 19, 15, 26, 16},
                {1735, 30, 5, 115, 10, 116, 1373, 28, 19, 47, 10, 48, 985, 30, 15, 24, 25, 25, 745, 30, 23, 15, 25, 16},
                {1843, 30, 13, 115, 3, 116, 1455, 28, 2, 46, 29, 47, 1033, 30, 42, 24, 1, 25, 793, 30, 23, 15, 28, 16},
                {1955, 30, 17, 115, 0, 0, 1541, 28, 10, 46, 23, 47, 1115, 30, 10, 24, 35, 25, 845, 30, 19, 15, 35, 16},
                {2071, 30, 17, 115, 1, 116, 1631, 28, 14, 46, 21, 47, 1171, 30, 29, 24, 19, 25, 901, 30, 11, 15, 46, 16},
                {2191, 30, 13, 115, 6, 116, 1725, 28, 14, 46, 23, 47, 1231, 30, 44, 24, 7, 25, 961, 30, 59, 16, 1, 17},
                {2306, 30, 12, 121, 7, 122, 1812, 28, 12, 47, 26, 48, 1286, 30, 39, 24, 14, 25, 986, 30, 22, 15, 41, 16},
                {2434, 30, 6, 121, 14, 122, 1914, 28, 6, 47, 34, 48, 1354, 30, 46, 24, 10, 25, 1054, 30, 2, 15, 64, 16},
                {2566, 30, 17, 122, 4, 123, 1992, 28, 29, 46, 14, 47, 1426, 30, 49, 24, 10, 25, 1096, 30, 24, 15, 46, 16},
                {2702, 30, 4, 122, 18, 123, 2102, 28, 13, 46, 32, 47, 1502, 30, 48, 24, 14, 25, 1142, 30, 42, 15, 32, 16},
                {2812, 30, 20, 117, 4, 118, 2216, 28, 40, 47, 7, 48, 1582, 30, 43, 24, 22, 25, 1222, 30, 10, 15, 67, 16},
                {2956, 30, 19, 118, 6, 119, 2334, 28, 18, 47, 31, 48, 1666, 30, 34, 24, 34, 25, 1276, 30, 20, 15, 61, 16}
        };
    }
}
