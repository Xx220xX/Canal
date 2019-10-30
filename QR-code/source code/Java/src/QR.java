import java.util.*;

public class QR {
    public interface MODO_CODIFICACAO {
        int NUMERICO = 1;
        int ALPHANUMERICO = 2;
        int BYTE = 3;
    }

    private String msg;
    private int modo_codificacao = MODO_CODIFICACAO.NUMERICO;



    public QR(String msg) {
        this.msg = msg;
    }

    /** ETAPA 1**/
    public void analise(){
        List<Character>caracteres = Arrays.asList(' ', '$', '*', '+', '.', '/', ':');
        for(char c:msg.toCharArray()){
            if(Character.isDigit(c))
                continue;
            if(Character.isAlphabetic(c) && Character.isUpperCase(c) || caracteres.contains(c)){
                modo_codificacao = MODO_CODIFICACAO.ALPHANUMERICO;
                continue;
            }
            modo_codificacao = MODO_CODIFICACAO.BYTE;
            break;
        }
    }

    /** ETAPA 2 codificacao*/


}
