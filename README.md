# LearningCompiler
Compiler 
###LIP
>1. Lexer.java	//词法分析器
>2. ListLexer.java	<br>
>3. LookaheadParser.java<br>
>4. Parser.java	//解析器，LL(k)<br>
>5. Token.java<br>

####CS212<br>
>6. FormulaLexer.java //解析 'OOD + OOD = EVEN'把，其中的NAME词法解析出来 <br>
>7. FormulaParser.java//验证 FORMULA是否合法<br>
>8. FormulaSolver.java//解决该问题得到第一个解如（770 + 770 = 1510假设）<br>

####HeteroAST
>9. HeteroAST.java  -->> StatNode.java && ExprNode.java//抽象类，异规则语法树，后面两个为继承类，代表语句（statment）和表达式（expresion）<br>
>8. IndependentPrintVisitor.java //独立访问者模式，把访问和树的节点解耦<br>

####TINY（编译原理及实践的小型编译器）
>1. Scanner.h //扫描器，用DFA实现匹配，getNextToken
>2. Token.h //同上
>3. Parser.h//将scanner分解的词,根据BNF递归下降,构造语法树,用的是同形树,printTree作为输出测试
>4. SymTab.h//符号表,树节点的名称(key),以及所在的行数(lineno)和
>5. Analyser.h//用先序后序遍历树节点实现的简单的语义分析器,具有识别id是否赋值,以及type是否与类型相对应的基本检查如:if exp或者until exp ,exp必须为bool值,且当exp中含有id时,必须检查此id在之前赋过值(:=符号),检查了左右赋值必须同时为integer..
