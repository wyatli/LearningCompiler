import com.sun.corba.se.impl.oa.toa.TOA;

/**
 * Created by abc84 on 2016/5/12.
 */
public class Parser {
    private int index = 0;
    private Token[] lookahead;//环形缓冲区
    private Lexer lexer;
    private int k; //LL(K)文法

    public Parser(Lexer lexer, int k) {
        this.lexer = lexer;
        this.k = k;
        lookahead = new Token[k];
        for (int i = 0; i < k; i++) {//初始化缓冲区
            consume();
        }
    }
    public int LA(int i) {//LL(1)
        return LT(i).type;
    }
    public Token LT(int i) {//LL(k)
        return lookahead[(index + i - 1) % k];//环式取值
    }
    public void consume() {
        lookahead[index] = lexer.nextToken();
        index = (index+1) % k;
    }
    public void match(int type) {
        if (type == LA(1)) consume();
        else {
            throw new Error("expecting type" + ListLexer.typeToName.get(type)
                            + "; found " + LT(1));
        }
    }
 }
