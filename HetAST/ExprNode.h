//
// Created by abc84 on 2016/5/16.
//

#ifndef HETAST_EXPRNODE_H
#define HETAST_EXPRNODE_H

#include "HeteroAST.h"

class ExprNode : public HeteroAST{

public:
    ExprNode(const Token &t) : HeteroAST(t) { }
    virtual void print() = 0;
};


#endif //HETAST_EXPRNODE_H
