//
// Created by abc84 on 2016/5/16.
//

#ifndef HETAST_ADDNODE_H
#define HETAST_ADDNODE_H

#include "ExprNode.h"
class AddNode: public ExprNode{

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
