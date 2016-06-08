//
// Created by abc84 on 2016/5/31.
//

#ifndef TINY_TREE_H
#define TINY_TREE_H

#include <memory>
#include <vector>
#include <set>
#include "Token.h"
#include "SymTab.h"

set<TOKEN_TYPES> expNode = {NUM, ID, EQ, LT, GT, LE, GE, PLUS, MINUS, TIMES, OVER};
set<TOKEN_TYPES> stmtNode = {IF, ASSIGN, READ, WRITE, REPEAT};
set<TOKEN_TYPES> opK = { EQ, LT, GT, LE, GE, PLUS, MINUS, TIMES, OVER};
typedef enum {
    INTEGER, BOOL, VOID
} ExpType;
typedef enum {
    expK, stmtK
} NodeKind;
using namespace std;

//class Analyser;
class Tree {
    friend void printTree(const Tree *);

    friend void tranverseTree(Tree *tree, SymTab *tab, void(*preProc)(SymTab *, Tree *),
                              void(*postProc)(SymTab *, Tree *));//以给定的先序处理,和后序处理遍历树

    friend void checkNode(SymTab *tab, Tree *node);

    friend void checkExpNode(SymTab *tab, Tree *node);

    friend void checkStmtNode(SymTab *tab, Tree *node);

    friend void deleteTree(Tree*);
private:
    void print() const {
        cout << type;
    }

    vector<Tree *> child;//子节点

    Tree *next;//相连的节点

    int val;
    string name;
    ExpType expType;
public:
    const TOKEN_TYPES type;

    NodeKind kind() const { return expNode.find(type) != expNode.end() ? expK : stmtK; }

    string getName() const { return name; }

    //virtual void print();

    Tree(TOKEN_TYPES type) : type(type), child(0, nullptr), next(nullptr) { }//必须初始化容器,和指针

    Tree(TOKEN_TYPES type, const string &n) : Tree(type) { this->name = name; };

    //id节点
    Tree(TOKEN_TYPES type, int val) : Tree(type) { this->val = val; }

    //num节点
    int lineno = 0;

    void addChild(Tree *t) { child.push_back(t); };

    void addNext(Tree *t) { next = t; }

    void setName(const string &s) { name = s; }

    void setExpK(ExpType type) {expType = type;}
};
//vector<Tree*> Tree::child;

static int indent = -2;

inline void printSpaces() {//打印空白
    for (int i = 0; i < indent; ++i) {
        cout << " ";
    }
}

inline void INDENT() {//缩进
    indent += 2;
}

inline void UNINDENT() {
    indent -= 2;
}

//set<TOKEN_TYPES> expNode = {NUM, ID, EQ,LT,GT, LE,GE,PLUS,MINUS,TIMES,OVER};
void printTree(const Tree *tree) {
    INDENT();
    while (tree != nullptr) {
        printSpaces();
        NodeKind kind = tree->kind();
        TOKEN_TYPES type = tree->type;
        if (kind == expK) {
            switch (type) {
                case NUM:
                    cout << "NUM: " << tree->val << endl;
                    break;
                case ID:
                    cout << "ID: " << tree->name << endl;
                    break;
                case PLUS:
                    cout << "Op: +" << endl;
                    break;
                case MINUS:
                    cout << "Op: -" << endl;
                    break;
                case TIMES:
                    cout << "Op: *" << endl;
                    break;
                case OVER:
                    cout << "Op: /" << endl;
                    break;
                case LT:
                    cout << "Op: <" << endl;
                    break;
                case GT:
                    cout << "Op: >" << endl;
                    break;
                case EQ:
                    cout << "Op: =" << endl;
                    break;
                case GE:
                    cout << "Op: >=" << endl;
                    break;
                case LE:
                    cout << "Op: <=" << endl;
                    break;
                default:
                    cerr << "Unkown token type: " << name[type] << endl;
            }
        }
            //set<TOKEN_TYPES> stmtNode = {IF, ASSIGN, READ, WRITE, REPEAT};
        else if (kind == stmtK) {
            switch (type) {
                case IF:
                    cout << "if" << endl;
                    break;
                case ASSIGN:
                    cout << "Assign to: " << tree->name << endl;
                    break;
                case REPEAT:
                    cout << "Repeat" << endl;
                    break;
                case READ:
                    cout << "Read: " << tree->name << endl;
                    break;
                case WRITE:
                    cout << "Write:" << endl;
                    break;
                default:
                    cerr << "Unkown token type: " << name[type] << endl;
            }
        }
        else cerr << "Unkown token type: " << name[type] << endl;
        for (Tree *tp : tree->child) {
            printTree(tp);
        }
        tree = tree->next;
    }
    UNINDENT();
}
void deleteTree(Tree* tree) {
    if (tree != nullptr) {
        auto temp = tree->child;
        auto nex = tree->next;
        delete tree;
        tree = nullptr;
        for (auto tp : temp) {
            deleteTree(tp);
        }
        deleteTree(nex);
    }
}




#endif //TINY_TREE_H
