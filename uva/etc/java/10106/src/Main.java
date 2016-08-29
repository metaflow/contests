import java.math.BigInteger;
import java.util.Scanner;

class Main {
    public static void main(String[] args) {
        new Main().run();
    }

    private void run() {
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNextBigInteger()) {
            BigInteger a = scanner.nextBigInteger();
            BigInteger b = scanner.nextBigInteger();
            System.out.println(a.multiply(b).toString());
        }
    }
}
