public class Main {
    public static void main(String[] args) throws QR.QRException {
        QR qr = new QR("HELLO WORLD");
        qr.analise();
        qr.codificacao();
        System.out.println(qr);
    }
}
