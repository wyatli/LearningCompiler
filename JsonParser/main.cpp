#include <iostream>
#include <fstream>

using namespace std;

#include "parser.h"

int main() {
/*
	    Lex lex("E:/jsn.txt");
	    Token t = lex.nextToken();
	    while (t.type != EOF_) {
	        cout << t;
	        t = lex.nextToken();
	    }
		for (;;);*/
	Parser p("E:/jsn.txt");
	Json_Object* obj = p.json();
	cout << "sb" << endl;
}