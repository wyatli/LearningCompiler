//
// Created by lee on 16-7-20.
//

#include "match.h"
#include <set>
#include <iostream>
/*
 * NFA直接匹配
 */
set<State*> marked;//记录已经访问过的

bool isMarked(State* state) {
    return marked.find(state) != marked.end();
}

void epsilon_closure(State* state,set<State*>& ss) {//深搜,计算epsilon闭包,添加到vector中
    marked.insert(state);//标记已访问
    ss.insert(state);//添加至vec中
    for (Edge* ep : state->edgs) {
        if (ep->ch == epsilon) { //若该边属于epsilon转换边
            State* next = ep->nextState;
            if (!isMarked(next) ) {//若没有访问过,就访问他
                epsilon_closure(next, ss);
            }
        }
    }

    marked.clear();
}

void match(const std::string patern, const std::string& toMatch) {
    NFA* nfa = buildNFA(patern);
    match(nfa, toMatch);
}

void transform(char c, set<State*>& oldStates,
               set<State*>& newStates) {//将当前状态集中，可以通过c转换的状态的epsilon闭包添加至新的状态集

    for (State* s : oldStates) {//向新状态集添加States
        for (Edge* e : s->edgs) {
            if (e->ch == c) {//该边为c转换
                State* next = e->nextState;
                epsilon_closure(next,newStates);//将下一个状态的ec（epsilon_closure）添加至新状态集（缓冲）
            }
        }
    }

    oldStates.clear();//情况原来状态集合

    for (State* state : newStates) {//写回当前状态，并把标记过的状态设为未标记
        oldStates.insert(state);
    }

    //marked.clear();
    newStates.clear();

}

void match(NFA* nfa, const std::string& s) {
    std::set<State*> oldStates;//当前状态集
    std::set<State*> newStates;//新状态集（缓冲作用）
    epsilon_closure(nfa->start, oldStates);//将起始状态的epsilon闭包添加进当前状态集
    //marked.clear();//必须加这一行，若是不加则不会将此时oldStates中的状态添加至后面的状态集中


    for(auto c : s) {
        transform(c, oldStates, newStates);//S = e_c(move(S,c));
    }
    if (find_if(oldStates.begin(), oldStates.end(),
                [](State* st){ return st->accepted;}) == oldStates.end()) {//若在最终集合中能找不到接受状态
        std::cout << "pattern mismatch" << std::endl;
    }
}


