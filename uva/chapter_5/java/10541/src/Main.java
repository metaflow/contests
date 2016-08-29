import java.math.BigInteger;
import java.util.Scanner;

class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int tcc = scanner.nextInt();
        while (tcc-- > 0) {
            int n = scanner.nextInt();
            int k = scanner.nextInt();
            int filled = 0;
            for (int i = 0; i < k; ++i) filled += scanner.nextInt();
            System.out.println(f(n - filled - k + 1, k + 1));
        }
    }

    private static BigInteger[][] m = new BigInteger[201][201];

    private static BigInteger f(int c, int p) {
        if (c < 0 || p <= 0) return BigInteger.ZERO;
        if (m[c][p] == null) {
            if (c == 0) {
                m[c][p] = BigInteger.ONE;
            } else {
                m[c][p] = f(c - 1, p).add(f(c, p - 1));
            }
        }
        return m[c][p];
    }
}