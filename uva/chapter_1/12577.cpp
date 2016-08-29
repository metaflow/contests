#include <stdio.h>

int main() {
    char s[30];
    int case_counter = 0;
    while (fgets(s, 30, stdin)) {
        if (s[0] == '*') break;
        case_counter++;
        printf("Case %d: Hajj-e-%s\n",
            case_counter,
            (s[0] == 'U') ? "Asghar" : "Akbar");
    }
    return 0;
}
