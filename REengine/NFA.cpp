//
// Created by Administrator on 2016/7/19.
//参见龙书第三章

#include "NFA.h"
#include <stack>
#include <iostream>
int epsilon = 257;
int State::counter = 0;

void destroyState(State *sp) {//销毁节点
    for (auto &edp : sp->edgs) {//删除点上的边
        //sp->removeEdge(edp);
        delete edp;
    }
    vector<Edge*> empty;
    sp->edgs.swap(empty);
    //delete sp;
}

NFA * buildAlter(NFA &nfa1, NFA &nfa2) {
    State *s1 = new State(false);//new State After new Start
    State *s2 = new State(true);//new accepted State
    NFA *newNFA = new NFA(s1, s2);//造新的NFDa

    //添加两条epsilon边并连接到原来的nfa的start下个节点
    s1->addEdge(Edge::getEpsilon(nfa1.next));
    s1->addEdge(Edge::getEpsilon(nfa2.next));

    //将原来的nfa的end节点从ac true状态到false
    nfa1.end->accepted = false;
    nfa2.end->accepted = false;

    //完成连接新的end节点
    nfa1.end->addEdge(Edge::getEpsilon(newNFA->end));
    nfa2.end->addEdge(Edge::getEpsilon(newNFA->end));

    //destroyState(nfa1.start);
    //destroyState(nfa2.start);
    delete nfa1.start;
    delete nfa2.start;

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
//    //destroyState(nfa2.start);
//    State *s = new State(true);//new accepted State
//    s -> addEdge(Edge::getEpsilon(nfa2.next));
//    destroyState(nfa1.end);
//    nfa1.end = s;//更新end
//    delete &nfa2;
//    return &nfa1;

    nfa1.end->addEdge(new Edge(epsilon,nfa2.next));
    nfa1.end->accepted = false;
    delete nfa2.start;
    delete &nfa2;
    nfa1.end = nfa2.end;
    return &nfa1;
}

NFA *buildRepStar(NFA &nfa) {//a*

    //将现在的end节点与next节点epsilon相连
    nfa.end->addEdge(new Edge(epsilon, nfa.next));

    //添加新的next节点
    State* newNext = new State(false);
    newNext->addEdge(new Edge(epsilon, nfa.next));
    nfa.next = newNext;
    nfa.start->edgs.clear();//清除原来的边
    nfa.start->addEdge(new Edge(epsilon, nfa.next));

    //添加新的end节点
    nfa.end->accepted = false;
    State* newEnd = new State(true);
    nfa.end->addEdge(new Edge(epsilon, newEnd));
    nfa.end = newEnd;

    //将新的next节点与新的end节点相连（epsilon）
    nfa.next->addEdge(new Edge(epsilon, nfa.end));

    return &nfa;
}

NFA *buildRepPlus(NFA &nfa) {//与*区别在于与end是否相连
    //将现在的end节点与next节点epsilon相连
    nfa.end->addEdge(new Edge(epsilon, nfa.next));

    //添加新的next节点
    State* newNext = new State(false);
    newNext->addEdge(new Edge(epsilon, nfa.next));
    nfa.next = newNext;
    nfa.start->edgs.clear();//清除原来的边
    nfa.start->addEdge(new Edge(epsilon, nfa.next));

    //添加新的end节点
    nfa.end->accepted = false;
    State* newEnd = new State(true);
    nfa.end->addEdge(new Edge(epsilon, newEnd));
    nfa.end = newEnd;

    return &nfa;
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
               // cout << c << endl;
                NFA *nfa1 = nfas.top();//后一个
                nfas.pop();
                NFA *nfa2 = nfas.top();//前一个
                nfas.pop();
                nfas.push(buildConcat(*nfa2, *nfa1));//必须注意链接的顺序，要不然在match时会出错
                break;
            }

            case '?': {
                NFA *nfa = nfas.top();
                nfas.pop();
                nfas.push(buildOpt(*nfa));
                break;
            }
            case '*': {
                NFA *nfa = nfas.top();
                nfas.pop();
                nfas.push(buildRepStar(*nfa));
                break;
            }
            case '+': {
                NFA *nfa = nfas.top();
                nfas.pop();
                nfas.push(buildRepPlus(*nfa));
                break;
            }
            default://字符状态
                //std::cout << c<< std::endl;
                nfas.push(buildSimple(c));
                break;
        }
    }

    return nfas.top();
}