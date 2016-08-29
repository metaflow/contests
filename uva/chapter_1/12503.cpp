#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    int case_count;
    int shifts[200];
    scanf("%d", &case_count);
    while (case_count--) {
        int instructions;
        scanf("%d\n", &instructions);
        for (int i = 0; i < instructions; i++) {
            string instruction;
            getline(cin, instruction);
            switch (instruction[0]) {
                case 'L': shifts[i] = -1; break;
                case 'R': shifts[i] = 1; break;
                case 'S':
                    int pos;
                    pos = stoi(instruction.substr(8, 3));
                    shifts[i] = shifts[pos - 1];
                    break;
            }
        }
        int result = 0;
        for (int i = 0; i < instructions; i++) result += shifts[i];
        printf("%d\n", result);
    }
}
