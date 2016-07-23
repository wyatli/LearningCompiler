//
// Created by Administrator on 2016/7/22.
//

#ifndef REENGINE_MATCH2_H
#define REENGINE_MATCH2_H

#include <map>
#include <vector>
#include <set>
#include "NFA.h"

using namespace std;
struct DFA {
    set<State*> states;
    DFA* next[256];//跳转表

    DFA(set<State*> states):states(states){}
};

DFA* buidDFA(const NFA* nfa);


set<State *> epsilon_bychar(DFA* dfa, int c);
#endif //REENGINE_MATCH2_H
