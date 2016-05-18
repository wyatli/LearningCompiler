//
// Created by abc84 on 2016/5/16.
//

#ifndef HETAST_ASIGNNODE_H
#define HETAST_ASIGNNODE_H

#include "StatNode.h"
#include "VarNode.h"
#include "ExprNode.h"
class IndependentPrintVisitor;
class AsignNode : public StatNode{
    friend class IndependentPrintVisitor;
public:
    AsignNode(VarNode* id, const Token &t, ExprNode* value) :
            var(id), StatNode(t), val(value){ }
    virtual void print() override;
private:
    shared_ptr<VarNode> var;
    shared_ptr<ExprNode> val;
};

void AsignNode::print() {
    var -> print();
    cout << " = " ;
    val -> print();
}


#endif //HETAST_ASIGNNODE_H
