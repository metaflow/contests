import java.util.*;

class Main {
    public static void main(String[] args) {
        new Main().run();
    }

    private void run() {
        Scanner scanner = new Scanner(System.in);
        int tcc = scanner.nextInt();
        for (int tc = 1; tc <= tcc; tc++) {
            if (tc != 1) System.out.println();
            int n = scanner.nextInt();
            int[] counts = new int[10000000];
            for (int i = 0; i < n; i++) {
                counts[readPhone(scanner)]++;
            }
            boolean found = false;
            for (int i = 0; i < counts.length; i++) {
                if (counts[i] < 2) continue;
                found = true;
                System.out.println(String.format("%03d-%04d %d", i / 10000, i % 10000, counts[i]));
            }
            if (!found) {
                System.out.println("No duplicates.");
            }
        }
    }

    private Integer readPhone(Scanner scanner) {
        String s = scanner.next();
        Integer phone = 0;
        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) == '-') continue;
            int v = 0;
            switch (s.charAt(i)) {
                case '1': v = 1; break;
                case '2':
                case 'A':
                case 'B':
                case 'C': v = 2; break;
                case '3':
                case 'D':
                case 'E':
                case 'F': v = 3; break;
                case '4':
                case 'G':
                case 'H':
                case 'I': v = 4; break;
                case '5':
                case 'J':
                case 'K':
                case 'L': v = 5; break;
                case '6':
                case 'M':
                case 'N':
                case 'O': v = 6; break;
                case '7':
                case 'P':
                case 'R':
                case 'S': v = 7; break;
                case '8':
                case 'T':
                case 'U':
                case 'V': v = 8; break;
                case '9':
                case 'W':
                case 'X':
                case 'Y': v = 9; break;
                case '0': v = 0; break;
            }
            phone = phone * 10 + v;
        }
        return phone;
    }
}

