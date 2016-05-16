//
// Created by abc84 on 2016/5/16.
//

#ifndef HETAST_STATNODE_H
#define HETAST_STATNODE_H

#include "HeteroAST.h"
class StatNode : public HeteroAST{

public:
    StatNode(const Token &t) : HeteroAST(t) { }
    virtual void print() = 0;
};


#endif //HETAST_STATNODE_H
