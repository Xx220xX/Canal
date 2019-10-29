
public class QR {
    public interface MODO_CODIFICACAO {
        public static final int NUMERICO = 1;
        public static final int ALPHANUMERICO = 2;
        public static final int BYTE = 3;
    }

    public QR(String msg) {
        this.msg = msg;
    }
    private String msg;
    private int modo_codificacao = MODO_CODIFICACAO.NUMERICO;
    // ETAPA 1
    public void analise(){
        for(char c:msg.toCharArray()){
            if(Character.isDigit(c))
                continue;
            if(Character.isAlphabetic(c) && Character.isUpperCase(c) ){
                modo_codificacao = MODO_CODIFICACAO.ALPHANUMERICO;
                continue;
            }
            modo_codificacao = MODO_CODIFICACAO.BYTE;
            break;
        }
        System.out.println(modo_codificacao);
    }

    public static void main(String[] args) {
        QR qr = new QR("ANFJ494AF");
        qr.analise();
    }
}
