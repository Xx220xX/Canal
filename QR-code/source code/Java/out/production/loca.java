import java.io.*;
import java.nio.file.PathMatcher;
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
        String[] str = new String[]{"L","M","Q","H"};

    }

    private String msg;
    private int lenght ;

    @Override
    public String toString() {
        return "QR{" +
                "msg='" + msg + '\'' +
                ", lenght=" + lenght +
                ", modo_correcao=" + modo_correcao +
                ", version=" + version +
                ", tentar_todos_modos_de_correcao=" + tentar_todos_modos_de_correcao +
                ", modo_codificacao=" + modo_codificacao +
                '}';
    }

    private int modo_correcao = MODO_CORRECAO.H;
    private int version ;
    private boolean   tentar_todos_modos_de_correcao = true;

    public QR(String msg, int modo_correcao, int modo_codificacao) {
        this(msg);
        this.modo_correcao = modo_correcao;
        this.modo_codificacao = modo_codificacao;
        this.tentar_todos_modos_de_correcao = false;
    }

    public QR(String msg) {
        this.msg = msg;
        this.lenght = msg.length();
    }


    private int modo_codificacao = MODO_CODIFICACAO.NUMERICO;

    // ETAPA 1
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

    private void determinarMenorVersao() throws QR_exception {
        // abrir arquivo
        String filename = "../tabelas/caracteres_por_versao/"+ MODO_CORRECAO.str[modo_correcao-1]+".txt";

        try( BufferedReader br = new BufferedReader(new FileReader(filename))){
            String line = "";
            version = 0;
            for(;;){
                line = br.readLine();
                if(line == null)break;

                version++;
                if(version>40){
                    throw new QR_exception("Não existe uma versão para esta mensagem");
                }
                int caracteres = 0;
                Scanner sc = new Scanner(line);
                for (int i = 0 ;i<modo_codificacao;i++){
                    caracteres = sc.nextInt();
                }
                if(caracteres>=lenght){
                    break;
                }
            }
        } catch (IOException e) {
            throw new QR_exception("table not find");
        }
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
