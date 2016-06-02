//
// Created by abc84 on 2016/5/31.
//

#ifndef TINY_TREE_H
#define TINY_TREE_H

#include <memory>
#include <vector>
#include <set>
#include "Token.h"

static int indent = 0;
set <TOKEN_TYPES> expNode = {NUM, ID, EQ, LT, GT, LE, GE, PLUS, MINUS, TIMES, OVER};
set <TOKEN_TYPES> stmtNode = {IF, ASSIGN, READ, WRITE, REPEAT};
typedef enum {
    expK, stmt
} NodeKind;
using namespace std;

class Tree {
    friend void printTree(const Tree *);

private:
    vector<Tree *> child;
    //子节点
    Tree *next;
    //相连的节点
    int val;
    string name;
public:
    const TOKEN_TYPES type;

    NodeKind kind() const { return expNode.find(type) != expNode.end() ? expK : stmt; }

    void deleteTree();

    //virtual void print();

    Tree(TOKEN_TYPES type) : type(type) { }

    Tree(TOKEN_TYPES type, const string &name) : type(type) { this->name = name; };

    //id节点
    Tree(TOKEN_TYPES type, int val) : type(type) { val = val; }

    //num节点
    int lineno = 0;

    void addChild(Tree *t) { child.push_back(t); };

    void addNext(Tree *t) { next = t; }

    void setName(const string& s) {name = s;}
};

inline void printSpaces() {
    for (int i = 0; i < indent; ++i) {
        cout << " ";
    }
}

inline void INDENT() {
    indent += 2;
}

inline void UNINDENT() {
    indent -= 2;
}

//set<TOKEN_TYPES> expNode = {NUM, ID, EQ,LT,GT, LE,GE,PLUS,MINUS,TIMES,OVER};
void printTree(const Tree *tree) {
    INDENT();
    while(tree != nullptr) {
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
        else if (kind == stmt) {
            switch (type) {
                case IF:
                    cout << "if" <<endl;
                case ASSIGN:
                    cout << "Assign to" << tree->name;
                    break;
                case REPEAT:
                    cout << "Repeat" << endl;
                    break;
                case READ:
                    cout << "Read:" << tree->name;
                    break;
                case WRITE:
                    cout << "Write:";
                    break;
                default:
                    cerr << "Unkown token type: " << name[type] << endl;
            }
        }
        else cerr << "Unkown token type: " << name[type] << endl;
        for (Tree* tp : tree->child) {
            printTree(tp);
        }
        tree = tree->next;
    }
    UNINDENT();
}


#endif //TINY_TREE_H
