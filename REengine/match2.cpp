//
// Created by Administrator on 2016/7/22.
//
#include <iostream>
#include "match2.h"
#include "match.h"

//struct setcomp {
//    bool operator()(const set<State *> &states1, const set<State *> &states2) {
//        if (states1.size() < states2.size()) {
//            return true;
//        }
//        if (states2.size() < states1.size()) {
//            return false;
//        }
//        for (auto it = states1.begin(); it != states1.end(); ++it) {
//            for (auto it2 = states2.begin(); it != states2.end(); ++it2) {
//                if (*it < *it2) {
//                    return true;
//                }
//            }
//        }
//        return false;
//    }
//};
DFA *buidDFA(const NFA *nfa) {
    set<State *> begin;
    epsilon_closure(nfa->start, begin);
    DFA *start = new DFA(begin);

    stack<DFA *> stack;
    stack.push(start);

    map<set<State *>, DFA *> map;//存放已经访问过的DFA,若访问过则直接从里面取DFA,若没有则插入

    while (!stack.empty()) {
        DFA *dfa = stack.top();
        stack.pop();
//        auto p = pair<set<State *>, DFA *>(dfa->states, dfa);
//        map.insert(p);
        map[dfa->states] = dfa;

        //cout << "sb" << endl;
        for (int c = 0; c <= 255; c++) {//不能用char(-128-127)也不能用unsigned char(0-255)，到255时+1就溢出，溢出条件为真无限循环

            set<State *> next_vec = epsilon_bychar(dfa, c);
            if (map.find(next_vec) == map.end() && next_vec.size() != 0) {//若是新的DFA
                //cout << "x"<<c <<endl;
                DFA *next = new DFA(next_vec);
                stack.push(next);
                dfa->next[c] = next;
            }
            else if (next_vec.size() != 0){
                // cout << c <<endl;
                dfa->next[c] = map[next_vec];
            }
        }
    }
    return start;
}



set<State *> epsilon_bychar(DFA *dfa, int c) {//epsilon(move(T,c))龙书第三章子集构造公式之一
    set<State *> states;

    for (auto &sp : dfa->states) {
        for (auto &ep : sp->edgs) {
            if (ep && ep->ch == c) {
                epsilon_closure(ep->nextState, states);//参数必须时ep->nextState.若是sp则有错
            }
        }
    }
    return states;
}

void match(DFA* dfa,const std::string& s) {
    if (accept(dfa)) return;//必须加这句，因为比如模式为a？,字符串为"",s[0]就会出错
    DFA* next = dfa->next[s[0]];
    int i = 1;
    while (next != nullptr && i < s.size()) {
        next = next->next[s[i]];
        i++;
    }

    if (!accept(next)) {
        cout << "pattern mismatch" << endl;
    }
}

bool accept(DFA* dfa) {
    for(State* s : dfa->states) {
        if (s->accepted) {
            return true;
        }
    }
    return false;
}