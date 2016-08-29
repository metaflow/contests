import java.math.BigInteger;
import java.util.Scanner;

class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int tcc = scanner.nextInt();
        while (tcc-- > 0) {
            BigInteger a = new BigInteger(reverse(removeLeadingZeroes(scanner.next())));
            BigInteger b = new BigInteger(reverse(removeLeadingZeroes(scanner.next()))).add(a);
            String result = removeLeadingZeroes(reverse(b.toString()));
            System.out.println(result);
        }
    }

    private static String reverse(String s) {
        return new StringBuilder(s).reverse().toString();
    }

    private static String removeLeadingZeroes(String s) {
        int i = 0;
        while (i < s.length() && s.charAt(i) == '0') i++;
        return s.substring(i);
    }
}