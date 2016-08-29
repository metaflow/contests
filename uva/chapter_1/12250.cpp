#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

int main() {
    int case_count = 0;
    string s;
    while(cin >> s) {
        if (s == "#") return 0;
        string a;
        if (s == "HELLO") {
            a = "ENGLISH";
        } else if (s == "HOLA") {
            a = "SPANISH";
        } else if (s == "HALLO") {
            a = "GERMAN";
        } else if (s == "BONJOUR") {
            a = "FRENCH";
        } else if (s == "CIAO") {
            a = "ITALIAN";
        } else if (s == "ZDRAVSTVUJTE") {
            a = "RUSSIAN";
        } else {
            a = "UNKNOWN";        
        }        
        printf("Case %d: %s\n", ++case_count, a.c_str());
    }
    return 0;
}
