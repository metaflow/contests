import java.math.BigInteger;
import java.util.Scanner;

class Main {
    public static void main(String[] args) {
        new Main().run();
    }

    private void run() {
        Scanner scanner = new Scanner(System.in);
        BigInteger f[] = new BigInteger[1001];
        f[0] = BigInteger.ONE;
        for (int i = 1; i < 1001; i++) f[i] = f[i - 1].multiply(BigInteger.valueOf(i));
        while (scanner.hasNextInt()) {
            int n = scanner.nextInt();
            System.out.println(String.format("%d!", n));
            System.out.println(f[n]);
        }
    }
}

// time : 15:00
