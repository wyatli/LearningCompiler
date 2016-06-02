//
// Created by abc84 on 2016/5/16.
//
//#pragma once
#ifndef HETAST_ADDNODE_H
#define HETAST_ADDNODE_H

//#include "IndependentPrintVisitor.h"
#include "ExprNode.h"
//#include "IndependentPrintVisitor.h"
//class IndependentPrintVisitor;
class AddNode: public ExprNode{
    //friend void  IndependentPrintVisitor::print(const AddNode &node);
    friend class IndependentPrintVisitor;
public:
    AddNode(ExprNode* l,const Token &t,ExprNode* r) :
            ExprNode(t),left(l),right(r) { }
    virtual void print() override ;

private:
    shared_ptr<ExprNode> left;
    shared_ptr<ExprNode> right;
};

void AddNode::print() {
    left -> print();
    cout << " + " ;
    right -> print();
}



#endif //HETAST_ADDNODE_H
