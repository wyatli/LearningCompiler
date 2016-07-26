//
// Created by Administrator on 2016/7/25.
//

#ifndef JSONPARSER_LEX_H
#define JSONPARSER_LEX_H

#include <iostream>
#include <string>
#include <fstream>
typedef enum {
    LB, RB, NUM, STR, BOOL_, COLON, LSB, RSB,NUL,EOF_, COMMA
} TYPE;
using namespace std;
typedef struct {
    string rep;
    double val;
    bool boolean;
} attr;
struct Token {//词素
    friend ostream& operator<<(ostream& os, const Token&);
    TYPE type;
    int lineno;
    attr a;

};

class Lex {
private:
    int index;
    string buffer;
    int lineno;
    ifstream stream;

    char getChar();//获取下一个字符

    void back() {--index;}//回退一个字符

public:
    Lex(const string &s) : index(0), lineno(0), stream() { stream.open(s); }

    Token nextToken();//下一个词素,供语法分析使用

};

#endif //JSONPARSER_LEX_H
