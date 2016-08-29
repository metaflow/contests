import java.math.BigInteger;
import java.util.Scanner;

class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        while (true) {
            int n = scanner.nextInt();
            if (n == 0) return;
            System.out.println(f(n));
        }
    }

    private static BigInteger[][] memo_c = new BigInteger[301][301];
    private static BigInteger[] memo_f = new BigInteger[301];

    private static BigInteger c(int n, int k) {
      if (memo_c[n][k] == null) {
        if (n == k || k == 0) {
          memo_c[n][k] = BigInteger.ONE;
        } else {
          memo_c[n][k] = c(n - 1, k).add(c(n - 1, k - 1));
        }
      }
      return memo_c[n][k];
    }

    private static BigInteger f(int n) {
      if (memo_f[n] == null) {
        if (n == 1 || n == 0) {
          memo_f[n] = BigInteger.ONE;
          return memo_f[n];
        }
        BigInteger a = BigInteger.ZERO;
        for (int i = 0; i < n; i++) {
          a = a.add(c(n-1, i).multiply(f(i)).multiply(f(n - 1 - i)));
        }
        memo_f[n] = BigInteger.valueOf(n).multiply(a);
      }
      return memo_f[n];
    }
}
