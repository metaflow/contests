import java.math.BigInteger;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        new Main().run();
    }

    private void run() {
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNext()) {
            String number = scanner.next();
            int from = scanner.nextInt();
            int to = scanner.nextInt();
            String s = new BigInteger(number, from).toString(to);
            if (s.length() > 7) s = "ERROR";
            System.out.println(String.format("%7s", s.toUpperCase()));
        }
    }
}
