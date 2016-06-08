//
// Created by abc84 on 2016/5/31.
//

#ifndef TINY_PARSER_H
#define TINY_PARSER_H

#include <sstream>
#include <string>
#include "Token.h"
#include "Scanner.h"
#include <vector>
#include <memory>
#include "Tree.h"

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

/*
 * 树节点
 */
//typedef struct treeNode {
//    //treeNode(){}
//    static shared_ptr<treeNode> getExpNode(Expkind ek) {
//        treeNode* node = (treeNode *) malloc(sizeof(treeNode));
//        node->node_type = ExpK;
//        node->kind.ek = ek;
//        node->lineno = 0;
//        node->attr.name = "";
//        node->attr.op = NONE;
//        node->attr.val = -1;
//        return shared_ptr<treeNode>(node);
//    }
//    static shared_ptr<treeNode> getStatNode(StatKind sk) {
//        treeNode* node = (treeNode *) malloc(sizeof(treeNode));
//        node->node_type = StatK;
//        node->kind.sk = sk;
//        node->lineno = 0;
//        node->attr.name = "";
//        node->attr.op = NONE;
//        node->attr.val = -1;
//        return shared_ptr<treeNode>(node);
//    }
//    NodeKind node_type;//节点类型
//    int lineno;
//    union {//节点类型的类型
//        StatKind sk;
//        Expkind ek;
//    } kind;
//    union {//属性值
//        string name;
//        int val;
//        TOKEN_TYPES op;
//    } attr;
//
//} TreeNode;

/*
 * 解析
 */
class Parser {
    friend void testParser(const string &s);

private:
    Token current;
    //当前token
    Scanner scanner;

    void match(TOKEN_TYPES types);

    Tree *stat_seq();

    Tree *stat();

    Tree *if_stat();

    Tree *asign_stat();

    Tree *repeat_stat();

    Tree *read_stat();

    Tree *write_stat();

    Tree *exp();

    Tree *simple_exp();

    Tree *term();

    Tree *factor();

public:
    Parser(const string &s) : scanner(s) { current = scanner.getNextToken(); }

    Tree *getAST();//生成语法树
};

Tree *Parser::stat_seq() {
    Tree *t = stat();
    Tree *temp = t;
    while (current.type != EOF_TYPE && current.type != END
           && current.type != ELSE && current.type != UNTIL && current.type != ERROR) {
        match(SEMI);
        Tree *p = stat();
        if (p != nullptr) {
            if (t == nullptr) {
                t = temp = p;
            }
            else {
                temp->addNext(p);
                temp = p;
            }
        }
    }
    //match(EOF_TYPE);
    return t;
}

void Parser::match(TOKEN_TYPES type) {
    if (type == current.type) {
        current = scanner.getNextToken();
    }
    else {
        cout << " expected type " << name[type] << " found " << name[current.type]
        << ":  " << current.toString() <<
        " at line :" << scanner.lineno << endl;
    }
}

Tree *Parser::stat() {

    switch (current.type) {
        case IF:
            return if_stat();
        case ID:
            return asign_stat();
        case REPEAT:
            return repeat_stat();
        case READ:
            return read_stat();
        case WRITE:
            return write_stat();
        default:
            cout << "unexpected token: " << name[current.type] << " at lineno" << scanner.lineno << endl;
            current = scanner.getNextToken();
            return nullptr;
    }
}

Tree *Parser::if_stat() {//if exp then stat_seq else stat_seq end

    Tree *node = new Tree(IF);
    node->lineno = scanner.lineno;
    match(IF);
    node->addChild(exp());
    match(THEN);
    node->addChild(stat_seq());
    if (current.type == ELSE) {//[else stat_seq]
        match(ELSE);
        node->addChild(stat_seq());
    }
    match(END);
    cout << current.toString() << endl;
    return node;
}

Tree *Parser::asign_stat() {

    Tree *node = new Tree(ASSIGN, current.toString());
    node->lineno = scanner.lineno;
    node->setName(current.toString());
    match(ID);
    match(ASSIGN);
    node->addChild(exp());
    return node;
}

Tree *Parser::repeat_stat() {//repeat stat_seq until exp
    match(REPEAT);
    Tree *left = stat_seq();
    match(UNTIL);
    Tree *right = exp();
    Tree *node = new Tree(REPEAT);
    node->lineno = scanner.lineno;
    node->addChild(left);
    node->addChild(right);
    return node;
}

Tree *Parser::read_stat() {//read id 读入
    match(READ);
    Tree *node = new Tree(READ);
    node->lineno = scanner.lineno;
    node->setName(current.toString());
    match(ID);
    return node;
}

Tree *Parser::write_stat() {//write exp 输出
    match(WRITE);
    Tree *node = new Tree(WRITE);
    node->lineno = scanner.lineno;
    node->addChild(exp());
    return node;
}

Tree *Parser::exp() {//exp ->　simple_exp compop simple_exp
    //return std::shared_ptr<TreeNode>();
    Tree *left = simple_exp();
    Tree *node = left;
    while (current.type == LT || current == LE || // < <= == > >=
           current.type == EQ ||
           current.type == GT || current.type == GE) {
        node = new Tree(current.type);
        node->lineno = scanner.lineno;
        match(current.type);
        node->addChild(left);
        Tree *right = simple_exp();
        node->addChild(right);
    }
    return node;
}

Tree *Parser::simple_exp() {//term {addop term}
    Tree *left = term();
    Tree *node = left;
    while (current.type == PLUS || current.type == MINUS) {
        node = new Tree(current.type);
        node->lineno = scanner.lineno;
        match(current.type);
        node->addChild(left);
        Tree *right = term();
        node->addChild(right);
        left = node;
    }
    return node;
}

Tree *Parser::term() {// factor {mulop factor}

    Tree *left = factor();
    Tree *node = left;
    //TOKEN_TYPES type = current.type;
    while (current.type == OVER || current.type == TIMES) {
        node = new Tree(current.type);
        node->lineno = scanner.lineno;
        match(current.type);
        node->addChild(left);
        Tree *right = factor();
        node->addChild(right);
        left = node;
    }
    return node;
}

Tree *Parser::factor() {//(exp) || NUM || ID

    TOKEN_TYPES type = current.type;
    Token temp(current);
    switch (type) {
        case NUM: {
            match(NUM);
            int num;
            stringstream(temp.toString()) >> num;
            Tree* node = new Tree(NUM, num);
            node->lineno = scanner.lineno;
            return node;
        }

        case ID: {
            match(ID);
            Tree *t = new Tree(ID, temp.toString());
            t->setName(temp.toString());
            t->lineno = scanner.lineno;
            return t;
        }
        case LPAREN: {
            match(LPAREN);
            Tree *t = exp();
            match(RPAREN);
            return t;
        }
        default:
            cout << "unexpected token: " << name[current.type] << "at lineno" << scanner.lineno << endl;
            current = scanner.getNextToken();
            return nullptr;
    }
    //current = scanner.getNextToken();
}

void testParser(const string &s) {
    Parser p(s);
    Tree *t = p.getAST();
    t;
    cout << endl;
    printTree(t);
}


Tree *Parser::getAST() {
    Tree *t = stat_seq();
    if (current.type != EOF_TYPE) {
        cout << "too few code" << endl;
    }
    return t;
}


#endif //TINY_PARSER_H
