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


DFA* buidDFA(const NFA* nfa);//构造dfa
void match(DFA* dfa, const string&);//匹配
bool accept(DFA* dfa);//状态是否可接受
set<State *> epsilon_bychar(DFA* dfa, int c);//该状态（集合）通过字符c到达另一个epsilon状态集

struct DFA {
    set<State*> states;
    DFA* next[256];//跳转表

    DFA(set<State*> states):states(states){}
};


#endif //REENGINE_MATCH2_H
