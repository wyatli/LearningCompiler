#include <iostream>
#include "Scanner.h"
#include "Parser.h"
using namespace std;

int main() {
    testScanner("d:/sb.txt");
    //Scanner s("d:/sb.txt");
    testParser("d:/sb.txt");
}