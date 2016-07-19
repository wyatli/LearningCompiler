//
// Created by Administrator on 2016/7/19.
//

#include "NFA.h"
#include <stack>
#include <iostream>
int epsilon;
int State::counter = 0;

void destroyState(State *sp) {//销毁节点
    for (auto &edp : sp->edgs) {//删除点上的边
        //sp->removeEdge(edp);
        delete edp;
    }
    vector<Edge*> empty;
    sp->edgs.swap(empty);
    delete sp;
}

NFA * buildAlter(NFA &nfa1, NFA &nfa2) {
    State *s1 = new State(false);//new State After new Start
    State *s2 = new State(true);//new accepted State
    NFA *newNFA = new NFA(s1, s2);//造新的NFDa

    //添加两条epsilon边并连接到原来的nfa的start下个节点
    s1->addEdge(Edge::getEpsilon(nfa1.nextFromStart()));
    s1->addEdge(Edge::getEpsilon(nfa2.nextFromStart()));
    //将原来的nfa的end节点从ac true状态到false
    nfa1.end->accepted = false;
    nfa2.end->accepted = false;
    //完成连接新的end节点
    nfa1.end->addEdge(Edge::getEpsilon(newNFA->end));
    nfa2.end->addEdge(Edge::getEpsilon(newNFA->end));

    //删除旧的nfa
    delete &nfa1;
    delete &nfa2;

    return newNFA;
}

NFA *buildSimple(char c) {
    State *next = new State(false);
    State *end = new State(true);
    next->addEdge(new Edge(c, end));
    NFA *nfa = new NFA(next, end);
    return nfa;
}

NFA *buildOpt(NFA &nfa) {
    nfa.next->addEdge(Edge::getEpsilon(nfa.end));//不能在start上面加,因为start会被删除
    return &nfa;
}

NFA *buildConcat(NFA &nfa1, NFA &nfa2) {
    //destroyState(nfa2.start);
    State *s = new State(true);//new accepted State
    s -> addEdge(Edge::getEpsilon(nfa2.next));
    destroyState(nfa1.end);
    nfa1.end = s;//更新end
    delete &nfa2;
    return &nfa1;
}

NFA *buildNFA(const string &s) {
    stack<NFA *> nfas;
    for (auto c : s) {
        switch (c) {
            case '|': {
                NFA *n1;
                n1 = nfas.top();
                nfas.pop();
                NFA *n2;
                n2 = nfas.top();
                nfas.pop();
                nfas.push(buildAlter(*n1, *n2));
                break;
            }
            case '.': {
                NFA *nfa1 = nfas.top();
                nfas.pop();
                NFA *nfa2 = nfas.top();
                nfas.pop();
                nfas.push(buildConcat(*nfa1, *nfa2));
            }

            case '?': {
                NFA *nfa = nfas.top();
                nfas.pop();
                nfas.push(buildOpt(*nfa));
                break;
            }
            default://字符状态
                std::cout << c<< std::endl;
                nfas.push(buildSimple(c));
                break;
        }
    }

    return nfas.top();
}