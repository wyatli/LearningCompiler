#include <iostream>
#include "NFA.h"
#include <string>
#include "match.h"
using namespace std;

int main() {
    //epsilon = 257;
    cout << "Hello, World!" << endl;

    NFA* nfa = buildNFA("a+b.c.");
    match(nfa, "aaaaaaaabc");
    return 0;
}