import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

class Main {
    public static void main(String[] args) {
        new Main().run();
    }

    private void run() {
        Scanner scanner = new Scanner(System.in);
        Pattern p = Pattern.compile("^[+-]?\\d+(?<d>\\.\\d+)?(?<e>e[+-]?\\d+)?$", Pattern.CASE_INSENSITIVE);
        while (true) {
            String s = scanner.nextLine().trim();
            if (s.equals("*")) break;
            Matcher matcher = p.matcher(s);
            boolean ok = matcher.matches() && !(matcher.group("d") == null && matcher.group("e") == null);
            System.out.println(String.format("%s is %s.",
                    s,
                    (ok ? "legal" : "illegal")));
        }
    }
}
