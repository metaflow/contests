import java.math.BigInteger;
import java.util.Scanner;

class Main {
    private static int[][] m = new int[367][10];

    public static void main(String[] args) {
        prepare();
        Scanner scanner = new Scanner(System.in);
        while (true) {
            int n = scanner.nextInt();
            if (n == 0) break;
            System.out.println(String.format("%d! --", n));
            int[] v = m[n];
            for (int i = 0; i < 10; ++i) {
                System.out.print(String.format("    (%d)%5d", i, v[i]));
                if (i % 5 == 4) System.out.println();
            }
        }
    }

    private static void prepare() {
        BigInteger a = BigInteger.ONE;
        for (int i = 1; i < 367; ++i) {
            a = a.multiply(BigInteger.valueOf(i));
            String s = a.toString();
            for (int j = 0; j < s.length(); ++j) {
                m[i][s.charAt(j) - '0']++;
            }
        }
    }
}
