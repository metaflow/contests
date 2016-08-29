import java.util.Scanner;
import java.util.StringTokenizer;
import java.util.regex.Pattern;

class Main {
    public static void main(String[] args) {
        new Main().run();
    }

    String vowel ="aeoiuy";
    Pattern five = Pattern.compile(String.format("^[^%1$s]*([%1$s]+[^%1$s]+){5}$", vowel));
    Pattern seven = Pattern.compile(String.format("^[^%1$s]*([%1$s]+[^%1$s]+){7}$", vowel));

    private void run() {
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            if (line.equals("e/o/i")) break;
            StringTokenizer tokenizer = new StringTokenizer(line, "/");
            String s = tokenizer.nextToken() + "/";
            if (!five.matcher(s).matches()) {
                System.out.println("1");
                continue;
            }
            s = tokenizer.nextToken() + "/";
            if (!seven.matcher(s).matches()) {
                System.out.println("2");
                continue;
            }
            s = tokenizer.nextToken() + "/";
            if (!five.matcher(s).matches()) {
                System.out.println("3");
                continue;
            }
            System.out.println("Y");
        }
    }
}
