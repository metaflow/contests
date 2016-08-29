#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

int main() {
    int case_count;
    scanf("%d", &case_count);
    string one = "one";
    while (case_count--) {
        string word;
        cin >> word;
        int answer = 0;
        if (word.size() == 3) {
            int matches = 0;
            for (int i = 0; i < 3; i++) if (one[i] == word[i]) matches++;
            if (matches > 1) {
                answer = 1;
            } else {
                answer = 2;
            }
        } else {
            answer = 3;
        }
        printf("%d\n", answer);
    }
    return 0;
}
