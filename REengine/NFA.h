//
// Created by Administrator on 2016/7/19.
//

#ifndef REENGINE_NFA_H
#define REENGINE_NFA_H

#include <vector>
#include <algorithm>
#include <string>
#include <stack>
extern int epsilon;

struct NFA;
void destroyState(State *sp);

NFA *buildSimple(char c);//a

NFA *buildAlter(NFA &nfa1, NFA &nfa2); //a|b

NFA *buildOpt(NFA &nfa);//a?

NFA *buildConcat(NFA &nfa1, NFA &nfa2);//ab

NFA *buildRepStar(NFA &nfa);//a*

NFA *buildRepPlus(NFA &nfa);//a+

NFA *buildNFA(const std::string &);


using namespace std;//0x6927d0

struct Edge;
struct State {
    static int counter;
    vector<Edge *> edgs;
    //节点的边
    int id;//标号
    bool accepted;

    bool operator==(const State& other) const { return this->id == other.id;}
    State(bool ac):id(counter++),edgs(),accepted(ac){

    }
    void addEdge(Edge* e) {
        edgs.push_back(e);
    }
    void removeEdge(Edge* e) {
        auto it = find(edgs.begin(), edgs.end(), e);
        edgs.erase(it);
    }
};

struct Edge {
    int ch;
    //转换所需的字符
    State *nextState;//边所指向的下一个节点
public:
    Edge(int c, State* next): ch(c), nextState(next){}
    static Edge* getEpsilon(State* next) {
        return new Edge(epsilon, next);
    }
};


struct NFA {
    State *start;
    State *end;
    State *next;
    //状态起始节点
    NFA(State* next, State *end) : start(new State(false)), end(end){
        start->addEdge(new Edge(epsilon, next));//start-(epsilon)->next
        this->next = next;
    }
    ~NFA() {//只删除收尾节点,中间的保留留作后用,若要彻底删除之,则单独调用deleteNFA()
        destroyState(start);
        destroyState(end);
    }
    State* nextFromStart() const{
        return next;
    }
};
#endif //REENGINE_NFA_H
