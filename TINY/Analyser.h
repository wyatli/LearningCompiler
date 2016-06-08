//
// Created by abc84 on 2016/6/8.
//

#ifndef TINY_ANALYSER_H
#define TINY_ANALYSER_H

#include "SymTab.h"
#include "Tree.h"
#include "Parser.h"
/*...
 * 简单的语义分析(semantic analysis)
 */
void type_error(Tree *t, const string &msg) {
    cout << "Type error at line: " << t->lineno << "  " << msg;
    cout << endl;
}

void tranverseTree(Tree *tree, SymTab *tab, void(* preProc)(SymTab *, Tree *),
                   void(* postProc)(SymTab *, Tree *)) {//遍历树
    if (tree != nullptr) {
        preProc(tab, tree);//先序遍历
        for (auto tp : tree->child) {
            tranverseTree(tp, tab, preProc, postProc);
        }
        postProc(tab, tree);//后续遍历
        tranverseTree(tree->next, tab, preProc, postProc);//遍历下一个兄弟节点
    }
}

void nullProc(SymTab *tab, Tree *node) {//do nothing
}

void insertNode(SymTab *tab, Tree *node) {//用树节点上的信息向sybt里添加节点
    if (tab != nullptr && node != nullptr) {
        switch (node->type) {
            case READ: {
                const string name = node->getName();
                tab->insert(name, node->lineno);
                break;
            }
            case ASSIGN: {
                const string name = node->getName();
                tab->insert(name, node->lineno);
                break;
            }
            default:
                break;
        }
    }
}
void checkExpNode(SymTab *tab, Tree *node) {//检查表达式节点
    if (opK.find(node->type) != opK.end()) {//是操作符类型
        if (node->child[0]->expType != INTEGER &&
            node->child[1]->expType != INTEGER) {
            type_error(node, "op has operand that is not integer");
        }
        if (node->type == EQ || node->type == GE ||
            node->type == LE ||node->type == GT ||node->type == LT ) {
            node->setExpK(BOOL);
        }
        else {//+ - * /
            node->setExpK(INTEGER);
        }
    }
    else if (node->type == ID) {//查询符号表
        if (!tab->lookup(node->name).second){type_error(node, string("can't resolve varible: ")+node->name);}
        else {node->setExpK(INTEGER);}
    }
    else if (node->type == NUM) {
        node->setExpK(INTEGER);
    }
}
void checkStmtNode(SymTab *tab, Tree *node) {//检查语句节点
    if (stmtNode.find(node->type) != stmtNode.end()) {//是语句节点
        switch (node->type){
            case IF:
                if (node->child[0]->expType != BOOL)
                    type_error(node, "if need BOOL condition test found Integer");
                break;
            case REPEAT:
                if (node->child[1]->expType != BOOL)
                    type_error(node, "until need BOOL condition test found Integer");
                break;
            case ASSIGN:
                if (node->child[0]->expType != INTEGER)
                    type_error(node, "Assignment need Integer in the right");
                if (node->type == ID&&tab->lookup(node->child[0]->name).first == -1) {
                    type_error(node, string("can't resolve varible: ")+node->name);
                }
                break;
            case WRITE:
                if (node->child[0]->expType != INTEGER)
                    type_error(node, "write need Integer in the right");
                if (node->type == ID&&tab->lookup(node->child[0]->name).first == -1) {
                    type_error(node, string("can't resolve varible: ")+node->name);
                }
                break;
            default:
                break;
        }
    }
}
void checkNode(SymTab *tab, Tree *node) {//自底而上检查节点
    if (tab != nullptr && node != nullptr) {
        checkExpNode(tab,node);
        checkStmtNode(tab,node);
    }
}

class Analyser {
private:
    //SymTab st;
    shared_ptr<SymTab> buildSymTab();//初始化symtb
    Tree *tree;
    shared_ptr<SymTab> symtb;
public:
    Analyser(Tree *t) : tree(t) {
        if (t == nullptr)
            cout << "Tree can't be empty";
        symtb = buildSymTab();
    }


    void typeCheck();

    virtual ~Analyser() { deleteTree(tree); }
};

shared_ptr<SymTab> Analyser::buildSymTab() {
    SymTab *tab = new SymTab;
    tranverseTree(tree, tab,insertNode, nullProc);
    cout << endl;
    tab->printTab();
    return shared_ptr<SymTab>(tab);
}

void Analyser::typeCheck() {
    tranverseTree(tree, symtb.get(), nullProc, checkNode);
}
void testAnalyser() {
    Parser parser("d:/sb.txt");
    Analyser analyser(parser.getAST());
    analyser.typeCheck();
}


#endif //TINY_ANALYSER_H
