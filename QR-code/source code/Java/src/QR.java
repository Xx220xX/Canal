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


    private String msg;
    private int modo_codificacao = MODO_CODIFICACAO.NUMERICO;

    private int modoCorrecao = MODO_CORRECAO.H;
    private boolean modoCorrecaoForcado = false;

    public QR(String msg, int modoCorrecao) {
        this.msg = msg;
        this.modoCorrecao = modoCorrecao;
        this.modoCorrecaoForcado = true;
    }

    public QR(String msg) {
        this.msg = msg;
    }

    /**
     * ETAPA 1
     **/
    public void analise() {
        List<Character> caracteres = Arrays.asList(' ', '$', '*', '+', '.', '/', ':');
        for (char c : msg.toCharArray()) {
            if (Character.isDigit(c))
                continue;
            if (Character.isAlphabetic(c) && Character.isUpperCase(c) || caracteres.contains(c)) {
                modo_codificacao = MODO_CODIFICACAO.ALPHANUMERICO;
                continue;
            }
            modo_codificacao = MODO_CODIFICACAO.BYTE;
            break;
        }
    }

    /**
     * ETAPA 2 codificacao
     */

    public void codificacao() throws QRException {
        try {
            System.out.println("tentando com modo " + modoCorrecao);
            determinarMenorVersao();
            /*colocarIndicadorDeModo();
            contarCaracteres();
            codificarDados();
            divirEmBlocos();*/

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
        throw new QRException.MODO_CORRECAO_NAO_SUPORTADO("erro forcado");
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
}
