//
// Created by abc84 on 2016/5/24.
//
/*
 * lexical analysis
 */
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include "Token.h"
#ifndef TINY_SCANNER_H
#define TINY_SCANNER_H

#define MAX_RESERVES 8
enum StateType {
    START,INCOMMENT,INNUM,INID,INASSIGN,DONE
};
struct {//保留字，得到的ID根据这个表来查询是否为保留字
    string name;
    TOKEN_TYPES type;
}reserved_words[] = {{"if",IF},{"then",THEN},
                     {"else",ELSE},{"end",END},
                     {"repeat",REPEAT},{"until",UNTIL},
                     {"read",READ},{"write",WRITE}};
class Scanner {
private:
    int linepos = 0;
    ifstream file;
    static char buffer[256];//读取缓冲区
    StateType state = START;
    void ungetCh(){ linepos--; }//回退字符
    //Token next;//当前token类型
    //char cur;//当前字符
    char getCh() ;
    Token reservedlookup(const string& s)const ;//看当前ID是否为保留字
public:
    int lineno;
    Scanner(const string& source){
        file.open(source);
    }
    Token getNextToken();
};

Token Scanner::getNextToken() {
    char stringBuf[40];//存放单词的缓冲
    int  stringIndex = 0;//缓冲索引

    while (state != DONE) {
        char c = getCh();
        //bool save = true;
        switch (state) {
            case START:
                if (c == '{')state = INCOMMENT;
                else if(c == ':')state = INASSIGN;
                else if(isdigit(c)){stringBuf[stringIndex++] = c;state = INNUM;}
                else if(isalpha(c)){stringBuf[stringIndex++] = c; state = INID;}
                else if(c == ' ' || c == '\t' || c == '\n')state = START;
                else {
                        state = START;//重启自动机
                    switch (c) {
                        case EOF:
                        return Token(EOF_TYPE, "EOF");
                        case '+':
                            return Token(PLUS, "+");
                        case '-':
                            return Token(MINUS, "-");
                        case '*':
                            return Token(TIMES, "*");
                        case '/':
                            return Token(OVER, "/");
                        case '=':
                            return Token(EQ, "=");
                        case '(':
                            return Token(LPAREN, "(");
                        case ')':
                            return Token(RPAREN, ")");
                        case ';':
                            return Token(SEMI, ";");
                        case '<':{
                            if (getCh() == '=') {
                                return Token(LT, "<=");
                            }
                            ungetCh();
                            return Token(LT,"<");
                        }
                        case '>': {
                            if (getCh() == '=') {
                                return Token(GE, ">=");
                            }
                            ungetCh();
                            return Token(GT,"<");
                        }

                    default:
                        return Token(ERROR, "[Error]");
                    }
                }
                break;
            case INCOMMENT://注释状态
                if (c == '}') {
                    state = START;
                }
                break;
            case INNUM://数字状态
                if (!isdigit(c)) {//非数字时退出INNUM状态，生成TOKEN，并回退一个字符
                    ungetCh();//回退字符
                    state = START;
                    stringBuf[stringIndex] = '\0';//结尾字符
                    cout << strlen(stringBuf);
                    return Token(NUM, stringBuf);
                }
                stringBuf[stringIndex++] = c;
                break;
            case INID://id状态
                if (!isalpha(c)) {
                    ungetCh();
                    state = START;
                    stringBuf[stringIndex] = '\0';
                    return reservedlookup(stringBuf);
                   // return Token(ID, stringBuf);
                }
                stringBuf[stringIndex++] = c;
                break;
            case INASSIGN://赋值状态
                if (c == '=') {
                    state = START;
                    return Token(ASSIGN, ":=");
                }
                ungetCh();
                break;
            default:
                cerr<<"scanner in bug"<<endl;
                exit(1);
        }
    }
}

char Scanner::getCh() {
    if (!file.eof()) {
        if (linepos >= strlen(buffer)||linepos == 0) {//若当前linepos为0或linepos>buffer的size时，重新填充BUFFER
            file.getline(buffer,255);
            lineno ++;
            linepos = 0;
            return buffer[linepos++];
        }
        return buffer[linepos++];
    }
    return EOF;
}

char Scanner::buffer[] = "";

Token Scanner::reservedlookup(const string &s) const {
    for (int i = 0; i < MAX_RESERVES; ++i) {
        if (s == reserved_words[i].name) {
            return Token(reserved_words[i].type, s);
        }
    }
    return Token(ID, s);
}
void testScanner(const string& s) {//测试
    Scanner scan(s);
    Token t;
    while (t.getType() != EOF_TYPE) {
        t = scan.getNextToken();
        cout << t <<endl;
    }
    cout << t;
}


#endif //TINY_SCANNER_H
