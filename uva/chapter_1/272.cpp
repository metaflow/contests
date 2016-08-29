#include <stdio.h>

int main() {
    char c;
    bool first_quote = true;
    while ((c = getchar()) != EOF) {
        if (c == '"') {
            printf("%s", (first_quote ? "``" : "''"));
            first_quote = !first_quote;
        } else {
            putchar(c);
        }
    }
    return 0;
}
