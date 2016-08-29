import java.math.BigInteger;
import java.util.Scanner;

class Main {
    static BigInteger fibonacci(int n) {
        BigInteger a = BigInteger.valueOf(0);
        BigInteger b = BigInteger.valueOf(1);
        while (n-- > 0) {
            BigInteger c = a.add(b);
            a = b;
            b = c;
        }
        return a;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNextInt()) {
            int n = scanner.nextInt();
            System.out.println(fibonacci(n + 2).toString());
        }
    }
}
