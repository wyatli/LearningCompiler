#ifndef Token_
#define Token_
#include <string>
#include <iostream>
#include <map>
#include <unordered_map>
#include <map>

enum TOKEN_TYPES {
    NONE,
    EOF_TYPE,ERROR,
    IF,THEN,ELSE,END,UNTIL,READ,WRITE,
    NUM,ID,
    ASSIGN,EQ,LT,GT,PLUS,MINUS,TIMES,OVER,LPAREN,RPAREN,SEMI,REPEAT,LE,GE
};
std::map<TOKEN_TYPES, std::string> name{ { IF, "IF" }, { EOF_TYPE, "EOF" }, { ERROR, "[ERO]" },
{ THEN, "THEN" }, { ELSE, "ELSE" }, { END, "END" }, { UNTIL, "UNTIL" },
{ READ, "READ" }, { WRITE, "WRITE" }, { NUM, "NUM" }, { ID, "ID" }, { ASSIGN, "ASSIGN" },
{ EQ, "EQ" }, { LT, "LT" }, { PLUS, "PLUS" }, { MINUS, "MINUS" }, { TIMES, "TIMES" }, { OVER, "OVER" },
{ LPAREN, "LPAREN" }, { RPAREN, "RPAREN" }, { SEMI, "SEMI" }, { REPEAT, "REP" }, { LE, "LE" }, { GE, "GE" }, { GT, "GT" } };
using namespace std;
class Token {
    friend ostream& operator<<(ostream& os, const Token& t);
public:
    TOKEN_TYPES type;
    
    //static map<TOKEN_TYPES , string> name;
    void printToken() {
        cout << name[type];
    }
	Token& operator=(const Token&);
    bool operator==(const Token& other) { return type == other.type;}
    Token(const Token& t);
    Token(TOKEN_TYPES type = NONE, const string& s = "");
    TOKEN_TYPES getType(){ return type; }
    string toString(){ return s; }
private:
    string s;
};

Token::Token(TOKEN_TYPES typ, const string& str) :type(typ), s(str) {
}
Token::Token(const Token& t): type(t.type), s(t.s){
}
ostream& operator<<(ostream &os, const Token& t) {
    return os << "< type:" << name[t.type] <<" :: "<< t.s << ">";
}
Token& Token::operator=(const Token& t) {
	this->type = t.type;
	this->s = t.s;
	return *this;
}

#endif // !Token_

