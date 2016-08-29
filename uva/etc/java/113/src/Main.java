import java.math.BigInteger;
import java.util.Scanner;

class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNextInt()) {
            int n = scanner.nextInt();
            BigInteger t = scanner.nextBigInteger();
            BigInteger a = BigInteger.ONE;
            BigInteger l = BigInteger.valueOf(500000000);
            while (true) {
                BigInteger m = a.add(l);
                int i = m.pow(n).compareTo(t);
                if (i == 0) {
                    a = m;
                    break;
                }
                l = l.divide(BigInteger.valueOf(2));
                if (i == -1) {
                    a = m.add(BigInteger.ONE);
                }
            }
            System.out.println(a.toString());
        }
    }
}
