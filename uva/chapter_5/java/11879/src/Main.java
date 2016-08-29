import java.math.BigInteger;
import java.util.Scanner;

class Main {
    public static void main(String[] args) {
        new Main().run();
    }

    private void run() {
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNextBigInteger()) {
            BigInteger b = scanner.nextBigInteger();
            if (b.equals(BigInteger.ZERO)) break;
            int a = 0;
            if (b.mod(BigInteger.valueOf(17)).longValue() == 0) {
                a = 1;
            }
            System.out.println(String.format("%d", a));
        }
    }
}