//
// Created by Administrator on 2016/7/25.
//

#include <cstdlib>
#include <map>
#include "lex.h"

ostream& operator<<(ostream&os, const Token& t) {

    return os << "<" << t.a.rep << ">" << " type: " << t.type <<endl;
}
char Lex::getChar() {
    if (!stream.eof()) {
        if (index == buffer.size() || index == 0) {
            index = 0;
            lineno++;
            getline(stream, buffer);
            while (buffer.size() == 0) {//不加的话会出现读行错误
                getline(stream, buffer);
            }
        }
    }
    return buffer[index++];
}


Token Lex::nextToken() {
    string buf;
    char cur = getChar();
    if (cur != EOF) {
        while(cur == ' ' || cur == '\n' || cur == '\b' || cur == '\t') {//跳过空白
            cur = getChar();
        }

        if (cur == '"') {//字符串
            cur = getChar();
            while (cur != '"') {
                buf.push_back(cur);
                cur = getChar();
            }
            Token t;
            t.type = STR;
            t.a.rep = buf;
            t.lineno = lineno;
            return t;
        }
        else if (isdigit(cur)) {//数字
            buf.push_back(cur);
            cur = getChar();
            while(isdigit(cur) || cur == '.') {
                buf.push_back(cur);
                cur = getChar();
            }
            back();
            Token t;
            t.type = NUM;
            t.a.val = atof(buf.c_str());
            t.lineno = lineno;
            return t;
        }
        else if (isalpha(cur)) {
            buf.push_back(cur);
            cur = getChar();
            while(isalpha(cur)) {
                buf.push_back(cur);
                cur = getChar();
            }
            Token t;
            back();
            if (buf == "true") {
                t.type = BOOL_;
                t.a.rep = "true";
                t.a.boolean = true;
                t.lineno = lineno;
                return t;
            }
            else if (buf == "false") {
                t.a.rep = "false";
                t.type = BOOL_;
                t.a.boolean = false;
                t.lineno = lineno;
                return t;
            }
            else if (buf == "null") {
                t.a.rep = "null";
                t.type = NUL;
                t.lineno = lineno;
                return t;
            }
        }
        switch (cur) {
            case '{': {
                Token t;
                t.a.rep = "{";
                t.type = LB;
                t.lineno = lineno;
                return t;
            }
            case '}': {
                Token t;
                t.a.rep = "}";
                t.lineno = lineno;
                t.type = RB;
                return t;
            }
            case '[': {
                Token t;
                t.a.rep = "[";
                t.lineno = lineno;
                t.type = LSB;
                return t;
            }
            case ']': {
                Token t;
                t.a.rep = "]";
                t.lineno = lineno;
                t.type = RSB;
                return t;
            }
            case ':': {
                Token t;
                t.a.rep = ":";
                t.type = COLON;
                t.lineno = lineno;
                return t;
            }
            case EOF: {
                Token t;
                t.a.rep = "EOF";
                t.lineno = lineno;
                t.type = EOF_;
                return t;
            }
            case '%': {
                Token t;
                t.a.rep = "EOF";
                t.lineno = lineno;
                t.type = EOF_;
                return t;
            }
            case ',': {
                Token t;
                t.a.rep = ",";
                t.lineno = lineno;
                t.type = COMMA;
                return t;
            }
            default:
                cout << "unknown char: " << cur << endl;
                break;
        }
    }
}

