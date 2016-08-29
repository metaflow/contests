import java.math.BigInteger;
import java.util.Scanner;

class Main {
    public static void main(String[] args) {
        new Main().run();
    }



    private void run() {
        BigInteger a = BigInteger.ONE;
        BigInteger b = BigInteger.ZERO;
        BigInteger fib[] = new BigInteger[5001];
        for (int i = 0; i < fib.length; i++) {
            fib[i] = b;
            BigInteger t = b;
            b = a;
            a = a.add(t);
        }
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNextInt()) {
            int n = scanner.nextInt();
            System.out.println(String.format("The Fibonacci number for %d is %s", n, fib[n].toString()));
        }
    }
}
