import sun.reflect.generics.reflectiveObjects.NotImplementedException;

import java.math.BigInteger;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        new Main().run();
    }

    private void run() {
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNext()) {
            String a = scanner.next();
            String b = scanner.next();
            Map<BigInteger, Integer> m = new HashMap<BigInteger, Integer>();
            for (int x = 2; x <= 36; x++) {
                try {
                    BigInteger i = new BigInteger(a, x);
                    if (m.containsKey(i)) continue;
                    m.put(i, x);
                } catch (NumberFormatException ignored) {
                    continue;
                }
            }
            boolean ok = false;
            for (int y = 2; y <= 36; y++) {
                try {
                    BigInteger i = new BigInteger(b, y);
                    if (m.containsKey(i)) {
                        ok = true;
                        System.out.println(String.format("%s (base %d) = %s (base %d)",
                                a, m.get(i), b, y));
                        break;
                    }
                } catch (NumberFormatException ignored) {
                    continue;
                }
            }
            if (!ok) {
                System.out.println(String.format("%s is not equal to %s in any base 2..36", a, b));
            }
        }
    }
}
