import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

class Main {
    public static void main(String[] args) {
        new Main().run();
    }
    Pattern pascal = Pattern.compile("([+-])?\\d+(?<decimal>\\.\\d+)?(?<exponent>[eE]([+-])?\\d+)?");

    private void run() {
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine().trim();
            if (line.equals("*")) break;
            Matcher matcher = pascal.matcher(line);
            if (matcher.matches() &&
                (matcher.group("decimal") != null || matcher.group("exponent") != null)) {
                System.out.println(String.format("%s is legal.", line));
            } else {
                System.out.println(String.format("%s is illegal.", line));
            }
        }
    }
}
