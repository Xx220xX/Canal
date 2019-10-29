
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
        int H = 3;
    }

    private String msg;
    private int modo_correcao = MODO_CORRECAO.H;

    public QR(String msg, int modo_correcao, int modo_codificacao) {
        this.msg = msg;
        this.modo_correcao = modo_correcao;
        this.modo_codificacao = modo_codificacao;
        this.tentar_todos_modos_de_correcao = false;
    }

    private boolean   tentar_todos_modos_de_correcao = true;

    public QR(String msg) {
        this.msg = msg;
    }

    private int modo_codificacao = MODO_CODIFICACAO.NUMERICO;

    // ETAPA 1
    public void analise() {
        for (char c : msg.toCharArray()) {
            if (Character.isDigit(c))
                continue;
            if (Character.isAlphabetic(c) && Character.isUpperCase(c)) {
                modo_codificacao = MODO_CODIFICACAO.ALPHANUMERICO;
                continue;
            }
            modo_codificacao = MODO_CODIFICACAO.BYTE;
            break;
        }
        System.out.println(modo_codificacao);
    }

    //ETAPA 2 codificacao
    public void codificar() throws QR_exception {
        try {
            determinarMenorVersao();
//            identicador_de_modo();
//            contagem_de_caracteres();
//            codificarDados();
//            dividir_em_blocos();

        } catch (QR_exception.MODO_CORRECAO e) {
            if (tentar_todos_modos_de_correcao && modo_correcao > MODO_CORRECAO.L) {
                modo_correcao--;
                codificar();
                return;
            }
            throw new QR_exception("mensagem não suportada");
        }
    }

    private void determinarMenorVersao() throws QR_exception.MODO_CORRECAO {
    }


    public class QR_exception extends Throwable {
        public QR_exception(String msg) {
            super(msg);
        }

        public class MODO_CORRECAO extends QR_exception {
            public MODO_CORRECAO(String msg) {
                super(msg);
            }
        }
    }

}
