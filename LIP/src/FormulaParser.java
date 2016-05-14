/**
 * Created by abc84 on 2016/5/14.
 */
import Exception.*;
public class FormulaParser extends Parser {

    public FormulaParser(Lexer lexer) {
        super(lexer, 1);
    }
    public void formula() throws MismatcherTokenException {
        expr();equaltion();expr();
    }

    private void equaltion() throws MismatcherTokenException {
        match(Lexer.EQUALS);
    }

    private void expr() throws MismatcherTokenException {
        Token last = LT(1);
        match(Lexer.NAME);
        if (LAT(1) == Lexer.NAME)throw new Error(last.rep()+" right can't be name, need an op");
        while (LAT(1) == Lexer.OPS) {
            match(Lexer.OPS);
            match(Lexer.NAME);
        }
    }
    public static void main(String[] args) throws MismatcherTokenException {
        Lexer l = new FormulaLexer("aaaa+  bb== c+b b");
        FormulaParser parser = new FormulaParser(l);//LL(2)
        parser.formula();
    }
}
