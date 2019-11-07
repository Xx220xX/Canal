public class Main {
    public static void main(String[] args) throws QR.QRException {
        QR qr = new QR("ANFJ494AF");
        qr.analise();
        qr.codificacao();
    }
}
