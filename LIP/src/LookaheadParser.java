import com.sun.org.apache.xpath.internal.operations.Lt;

/**
 * Created by abc84 on 2016/5/12.
 */
/*
递归下降匹配LL（2）文法
 */
public class LookaheadParser extends Parser {
    //private Token lookahead;
    public LookaheadParser(Lexer lexer, int k) {
        super(lexer, k);
    }

    public void list() {
         match(ListLexer.LBRACKT);elements();match(ListLexer.RBRACKT);
    }
    public void elements() {
        element();
        while (LT(1).type == ListLexer.COMMA) {
            match(ListLexer.COMMA);element();
        }
    }

    public void element() {//[a=b]|[a]||[c,[a,a=b]]
        if (LT(1).type == ListLexer.NAME && LT(2).type == ListLexer.Equal) {//'a=b'
            match(ListLexer.NAME);
            match(ListLexer.Equal);
            match(ListLexer.NAME);
        }
        else if (LT(1).type == ListLexer.LBRACKT) list();//'['
        else if (LT(1).type == ListLexer.NAME)match(ListLexer.NAME);//'a'
        else {
            throw new Error("expecting name or list; found" + LT(1));
        }
    }

    public static void main(String[] args) {
        Lexer l = new ListLexer("[a,b=c,[d,a]]");
        LookaheadParser parser = new LookaheadParser(l, 2);//LL(2)
        parser.list();
    }
}
