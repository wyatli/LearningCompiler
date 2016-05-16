#include <iostream>
#include "Token.h"
#include "AsignNode.h"
#include "IntNode.h"
#include "AddNode.h"

using namespace std;

int main() {
    Token plus(PLUS, "+");
    Token l(INT, "1");
    Token r(INT, "2");
    Token var(VAR, "x");
    VarNode* v = new VarNode(var);
    IntNode* left = new IntNode(l);
    IntNode* right = new IntNode(r);
    AddNode* ad = new AddNode(left, plus, right);
    AsignNode as(v, Token(EQUAL, "="), ad);
    as.print();
    //ad.print();
    return 0;
}