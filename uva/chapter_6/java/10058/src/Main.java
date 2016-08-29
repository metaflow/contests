import java.util.Scanner;
import java.util.regex.Pattern;

class Main {
    String verb = "(hate|love|know|like)s?";
    String noun = "(tom|jerry|goofy|mickey|jimmy|dog|cat|mouse)";
    String actor = "(a |the )?"+noun;
    String active_list = "(" + actor + " and )*" + actor;
    String action = active_list + " " + verb + " " + active_list;
    Pattern statement = Pattern.compile("(" + action + " ?, ?)*" + action);

    public static void main(String[] args) {
        new Main().run();
    }

    private void run() {
        Scanner s = new Scanner(System.in);
        while (s.hasNextLine()) {
            String r = s.nextLine();
            r = r.trim().replaceAll(" +", " ");
            if (statement.matcher(r).matches()) {
                System.out.println("YES I WILL");
            } else {
                System.out.println("NO I WON'T");
            }
        }
    }
}

// time : 20:00