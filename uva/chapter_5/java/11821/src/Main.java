import java.math.BigDecimal;
import java.util.Scanner;

class Main {
    public static void main(String[] args) {
        new Main().run();
    }

    private void run() {
        Scanner s = new Scanner(System.in);
        int tcc = s.nextInt();
        while (tcc-- > 0) {
            BigDecimal a = BigDecimal.ZERO;
            while (true) {
                String t = s.next();//.trim();
                if (t.equals("0")) break;
                BigDecimal b = new BigDecimal(t);
                a = a.add(b);
            }
            // http://bugs.sun.com/bugdatabase/view_bug.do?bug_id=6480539
            if (a.compareTo(BigDecimal.ZERO) == 0) {
                System.out.println("0");
            } else {
                System.out.println(a.stripTrailingZeros().toPlainString());
            }
        }
    }
}


//time: 1:30:00