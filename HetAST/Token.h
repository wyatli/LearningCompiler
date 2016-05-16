#ifndef Token_
#define Token_
#include <string>
#include <iostream>
enum TOKEN_TYPES {
    INT,EQUAL,PRINT,PLUS,VAR
};
using namespace std;
class Token {
    friend ostream& operator<<(ostream& os, const Token& t);
public:
    Token(const Token& t);
    Token(TOKEN_TYPES type, const string& s);
    int getType(){ return type; }
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

