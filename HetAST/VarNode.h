//
// Created by abc84 on 2016/5/16.
//

#ifndef HETAST_VARNODE_H
#define HETAST_VARNODE_H

#include "HeteroAST.h"
class VarNode : public HeteroAST {

public:
    VarNode(const Token &t) : HeteroAST(t) { }
    virtual void print();
};

void VarNode::print() {
    cout << *tp;
}


#endif //HETAST_VARNODE_H
