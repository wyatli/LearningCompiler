#include <iostream>
#include "Token.h"
#include "AsignNode.h"
#include "IntNode.h"
#include "AddNode.h"
#include "IndependentPrintVisitor.h"
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
    AddNode* ad2 = new AddNode(ad, plus, right);
    AddNode* ad3 = new AddNode(ad2, plus, left);
    //ad3->print();
    AsignNode as(v, Token(EQUAL, "="), ad3);
    as.print();
    cout<<endl<<"---------------"<<endl;
    IndependentPrintVisitor visitor;
    visitor.print(as);
    //ad.print();
    return 0;
}