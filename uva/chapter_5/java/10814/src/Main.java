import sun.reflect.generics.reflectiveObjects.NotImplementedException;

import java.math.BigInteger;
import java.util.Scanner;

class Main {
    public static void main(String[] args) {
        new Main().run();
    }

    private void run() {
        Scanner s = new Scanner(System.in);
        int tcc = s.nextInt();
        while (tcc-- > 0) {
            BigInteger a = s.nextBigInteger();
            s.next();
            BigInteger b = s.nextBigInteger();
            BigInteger gcd = a.gcd(b);
            System.out.println(String.format("%s / %s", a.divide(gcd), b.divide(gcd)));
        }
    }
}
