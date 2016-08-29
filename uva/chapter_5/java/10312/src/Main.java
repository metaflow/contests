import java.math.BigInteger;
import java.util.Scanner;

class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNextInt()) {
            int n = scanner.nextInt();
            System.out.println(F(n));
        }
    }

    private static BigInteger F(int n) {
        return A(n).subtract(B(n));
    }

    static BigInteger[] bm = new BigInteger[27];

    private static BigInteger B(int n) {
        if (n <= 2) return BigInteger.ONE;
        if (bm[n] == null) {
            bm[n] = BigInteger.ZERO;
            for (int i = 1; i < n; ++i) bm[n] = bm[n].add(B(i).multiply(B(n - i)));
        }
        return bm[n];
    }

    static BigInteger[] ba = new BigInteger[27];

    private static BigInteger A(int n) {
        if (n <= 2) return BigInteger.ONE;
        if (ba[n] == null) {
            ba[n] = A(n-1).multiply(BigInteger.valueOf(3));
            for (int i = 2; i <= n - 2; ++i) {
                ba[n] = ba[n].add(A(i).multiply(A(n - i)).multiply(BigInteger.valueOf(2)));
            }

        }
        return ba[n];
    }
}
