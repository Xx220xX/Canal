public class Main {
    public static void main(String[] args) throws QR.QR_exception {
        QR qr = new QR("ANFJ494AF");
        qr.analise();
        qr.codificar();
    }
}
