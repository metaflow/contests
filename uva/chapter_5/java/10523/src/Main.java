import java.math.BigInteger;
import java.util.Scanner;

class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNextInt()) {
            int n = scanner.nextInt();
            BigInteger a = BigInteger.valueOf(scanner.nextInt());
            BigInteger result = BigInteger.ZERO;
            for (int i = 1; i <= n; i++) {
                result = result.add(BigInteger.valueOf(i).multiply(a.pow(i)));
            }
            System.out.println(result.toString());
        }
    }
}