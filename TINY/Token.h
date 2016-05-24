#ifndef Token_
#define Token_
#include <string>
#include <iostream>
#include <map>
#include <unordered_map>


enum TOKEN_TYPES {
    NONE,
    EOF_TYPE,ERROR,
    IF,THEN,ELSE,END,UNTIL,READ,WRITE,
    NUM,ID,
    ASSIGN,EQ,LT,PLUS,MINUS,TIMES,OVER,LPAREN,RPAREN,SEMI,REPEAT
};

using namespace std;
class Token {
    friend ostream& operator<<(ostream& os, const Token& t);
public:
    Token(const Token& t);
    Token(TOKEN_TYPES type = NONE, const string& s = "");
    TOKEN_TYPES getType(){ return type; }
    string toString(){ return s; }
private:
    TOKEN_TYPES type;
    string s;
};

Token::Token(TOKEN_TYPES typ, const string& str) :type(typ), s(str) {
}
Token::Token(const Token& t): type(t.type), s(t.s){
}



ostream& operator<<(ostream &os, const Token& t) {
    return os << "< type:" << t.type <<" -- "<< t.s << ">";
}


#endif // !Token_

