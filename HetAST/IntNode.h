//
// Created by abc84 on 2016/5/16.
//

#ifndef HETAST_INTNODE_H
#define HETAST_INTNODE_H

#include "ExprNode.h"
class IntNode : public ExprNode {

public:
    IntNode(const Token &t) : ExprNode(t) { }
    virtual void print() override;
};

void IntNode::print() {
    cout << *tp;
}


#endif //HETAST_INTNODE_H
