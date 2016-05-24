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
