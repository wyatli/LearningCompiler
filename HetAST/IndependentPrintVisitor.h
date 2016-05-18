//
// Created by abc84 on 2016/5/18.
//

#ifndef HETAST_INDEPENDENTPRINTVISITOR_H
#define HETAST_INDEPENDENTPRINTVISITOR_H
/*
 * visitor模式，以独立的类遍历树
 */
#include <cstdlib>
#include "HeteroAST.h"
//#include "AddNode.h"
#include "AsignNode.h"
#include "IntNode.h"
#include "VarNode.h"
class  AddNode;
class IndependentPrintVisitor {
public:
    void print(const HeteroAST& node);//根节点，调度算法调度节点
    void print(const AddNode& node);
    void print(const AsignNode& node);
    void print(const IntNode& node);
    void print(const VarNode& node);
};

void IndependentPrintVisitor::print(const HeteroAST &node) {
    TOKEN_TYPES type = node.getType();
    switch (type) {
        case INT:   print(dynamic_cast<const IntNode&>(node));break;//这后面若没有break；会有bad_cast
        case EQUAL: print(dynamic_cast<const AsignNode&>(node));break;
        case PLUS:  print(dynamic_cast<const AddNode&>(node));break;
        case VAR:   print(dynamic_cast<const VarNode&>(node));break;
        default:
            cerr << "no Node match" << endl;
            exit(0);
    }
}
void IndependentPrintVisitor::print(const IntNode &node) {
    node.printToken();
}
void IndependentPrintVisitor::print(const AddNode &node) {
    print(*node.left);cout << " + ";print(*node.right);
}

void IndependentPrintVisitor::print(const AsignNode &node) {
    print(*(node.var));cout << " = ";print(*(node.val));
}

void IndependentPrintVisitor::print(const VarNode &node) {
    node.printToken();
}


#endif //HETAST_INDEPENDENTPRINTVISITOR_H
