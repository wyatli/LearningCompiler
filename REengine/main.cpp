#include <iostream>
#include "NFA.h"
#include <string>
#include "match2.h"
#include "match.h"
using namespace std;

int main() {
    //epsilon = 257;

    NFA* nfa = buildNFA("ab|c.");
    match(nfa, "ff");

    DFA* dfa = buidDFA(nfa);

    return 0;
}