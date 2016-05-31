//
// Created by abc84 on 2016/5/31.
//

#ifndef TINY_PARSER_H
#define TINY_PARSER_H

#include <string>
#include "Token.h"
#include "Scanner.h"
#include <vector>
#include <memory>
using namespace std;
//文法处理，递归下降
/*
 * program -> stat_seq
 * stat_seq -> stat{;stat}
 * stat -> if_stat|asign_stat|repeat_stat|read_stat|write_stat
 * if_stat -> if exp then stat_seq [else stat_seq] end
 * asign_stat -> identifier:=exp
 * repeat_stat -> repeat stat_seq until exp
 * read_stat -> read identifier
 * write_stat -> write exp
 * exp -> simple_exp compop simple_exp
 * comop -> <|>|<=|>=|=
 * simple_exp -> term {addop term}
 * addop -> +|-
 * term -> factor {mulop factor}
 * mulop -> *|/
 * factor -> (exp)|num
 */

typedef enum {StatK, ExpK} NodeKind;
typedef enum {IF_STM,ASI_STM,REP_STM,READ_STM,WRI_STM} StatKind;
typedef enum {Num, Id, Op} Expkind;
/*
 * 树节点
 */
typedef struct treeNode {
    //treeNode(){}
    static shared_ptr<treeNode> getExpNode(Expkind ek) {
        treeNode* node = (treeNode *) malloc(sizeof(treeNode));
        node->node_type = ExpK;
        node->kind.ek = ek;
        node->lineno = 0;
        node->attr.name = "";
        node->attr.op = NONE;
        node->attr.val = -1;
        return shared_ptr<treeNode>(node);
    }
    static shared_ptr<treeNode> getStatNode(StatKind sk) {
        treeNode* node = (treeNode *) malloc(sizeof(treeNode));
        node->node_type = StatK;
        node->kind.sk = sk;
        node->lineno = 0;
        node->attr.name = "";
        node->attr.op = NONE;
        node->attr.val = -1;
        return shared_ptr<treeNode>(node);
    }
    NodeKind node_type;//节点类型
    int lineno;
    union {//节点类型的类型
        StatKind sk;
        Expkind ek;
    } kind;
    union {//属性值
        string name;
        int val;
        TOKEN_TYPES op;
    } attr;
    vector<shared_ptr<treeNode>> child;//子节点
    shared_ptr<treeNode> next;//相连的节点
} TreeNode;

/*
 * 解析
 */
class Parser {
    friend void testParser(const string& s);
private:
    Token current;//当前token
    Scanner scanner;
    /*
     * 递归下降文法
     * /*
     * program -> stat_seq
     * stat_seq -> stat{;stat}
     * stat -> if_stat|asign_stat|repeat_stat|read_stat|write_stat
     * if_stat -> if exp then stat_seq [else stat_seq] end
     * asign_stat -> identifier:=exp
     * repeat_stat -> repeat stat_seq until exp
     * read_stat -> read identifier
     * write_stat -> write exp
     * exp -> simple_exp compop simple_exp
     * comop -> <|>|<=|>=|=
     * simple_exp -> term {addop term}
     * addop -> +|-
     * term -> factor {mulop factor}
     * mulop -> *|/
     * factor -> (exp)|num
     */
    shared_ptr<TreeNode> stat_seq();
    shared_ptr<TreeNode> stat();
    shared_ptr<TreeNode> if_stat();
//    shared_ptr<TreeNode> asign_stat();
//    shared_ptr<TreeNode> repeat_stat();
//    shared_ptr<TreeNode> read_stat();
//    shared_ptr<TreeNode> write_stat();
    shared_ptr<TreeNode> exp();
//    shared_ptr<TreeNode> simple_exp();
//    shared_ptr<TreeNode> term();
//    shared_ptr<TreeNode> factor();
public:
    Parser(const string& s):scanner(s){}
    //shared_ptr<TreeNode> getAST();//生成语法树
    void match(TOKEN_TYPES types);
};

void testParser(const string& s) {
    Parser p(s);
    p.stat_seq();
}

shared_ptr<TreeNode> Parser::stat_seq() {
    shared_ptr<TreeNode> t = stat();
    shared_ptr<TreeNode> temp = t;
    while (current.type != EOF_TYPE && current.type != END
            && current.type != ELSE && current.type != UNTIL) {
        match(SEMI);
        shared_ptr<TreeNode> p = stat();
        if (p != nullptr) {
            if (t == nullptr) {
                t = temp = p;
            }
            else {
                temp->next = p;
                temp = p;
            }
        }
    }
    return t;
}

void Parser::match(TOKEN_TYPES type) {
    if (type == current.type) current = scanner.getNextToken();
    else {
        cerr << " expected type " << Token::name[type] <<" found " << Token::name[current.type] <<
                                                         "at line :" << scanner.lineno;
    }
}

shared_ptr<TreeNode> Parser::stat() {
    switch (current.type) {
        case IF:
            return if_stat();
//        case REPEAT:
//            return repeat_stat();
//        case ASSIGN:
//            return asign_stat();
//        case READ:
//            return read_stat();
//        case WRITE:
//            return write_stat();
        default:
            cerr << "unexpected token: " << Token::name[current.type] << "at lineno" << scanner.lineno;
            current = scanner.getNextToken();
            return nullptr;
    }
}

shared_ptr<TreeNode> Parser::if_stat() {//if exp then stat_seq else stat_seq end
    shared_ptr<TreeNode> node = TreeNode::getStatNode(IF_STM);
    match(IF);
    (node->child).push_back(exp());
    match(THEN);
    (node->child).push_back(stat_seq());
    if(current.type == ELSE) {//[else stat_seq]
        match(ELSE);
        (node->child).push_back(stat_seq());
    }
    match(END);
    return node;
}

shared_ptr<TreeNode> Parser::exp() {
    return std::shared_ptr<TreeNode>();
}


#endif //TINY_PARSER_H
