import Exception.*;
import sun.dc.pr.PRError;
import sun.misc.LRUCache;

/**
 * Created by abc84 on 2016/5/12.
 */
/*
递归下降匹配LL（2）文法|回溯法加辅助推演
 */
public class LookaheadParser extends Parser {
    //private Token lookahead;
    public LookaheadParser(Lexer lexer, int k) {
        super(lexer, k);
    }

    public void asign() throws MismatcherTokenException, RecognitionException, PreviousParseFailedException {//[a,b] = [c,d] = [f]
        list();
        while (LT(1).type == Lexer.Equal) {
            match(Lexer.Equal);list();
        }
    }

    public void list() throws MismatcherTokenException, RecognitionException, PreviousParseFailedException {
        match(ListLexer.LBRACKT);elements();match(ListLexer.RBRACKT);

    }//'['elements']'

    public void elements() throws MismatcherTokenException, RecognitionException, PreviousParseFailedException {
        element();
        while (LT(1).type == ListLexer.COMMA) {
            match(ListLexer.COMMA);element();
        }
    }

    public void stat() throws RecognitionException, // stat: list EOF | list '='list EOF
            NoViableAltException, MismatcherTokenException, PreviousParseFailedException {// list EOF | list '=' list 回溯法
        if (speculate_stat_alt1()) {
            list();match(Lexer.EOF_TYPE);
        }
        else if (speculate_stat_alt2()) {
            asign();match(Lexer.EOF_TYPE);
        }
        else //肯定出错了两个都不匹配
            throw new NoViableAltException("expecting stat found: "+LT(1)+" at " + index());
    }

    public boolean speculate_stat_alt1() throws PreviousParseFailedException {
        boolean success = true;
        mark();
        try{
            list();
            match(Lexer.EOF_TYPE);
        }catch (RecognitionException | MismatcherTokenException e){
            //return false;这里不能return否则就不能release
            success = false;
        }
        release();
        return success;
    }//list EOF

    public boolean speculate_stat_alt2() throws PreviousParseFailedException{
        boolean success = true;
        mark();
        try{
            asign();match(Lexer.EOF_TYPE);
        }catch (RecognitionException | MismatcherTokenException e){
            e.printStackTrace();
            success = false;
//            e.printStackTrace();
//            return false;
        }
        release();
        return success;
    }//list '=' list EOF

    public void element() throws RecognitionException, MismatcherTokenException, PreviousParseFailedException {//[a=b]|[a]||[c,[a,a=b]]
        if (LT(1).type == ListLexer.NAME && LT(2).type == ListLexer.Equal) {//'a=b'
            match(ListLexer.NAME);
            match(ListLexer.Equal);
            match(ListLexer.NAME);
        }
        else if (LT(1).type == ListLexer.LBRACKT) list();//'['
        else if (LT(1).type == ListLexer.NAME)match(ListLexer.NAME);//'a'
        else {
            throw new RecognitionException("expecting name or list; found" + LT(1)+" at " + index());
        }
    }//NAME | NAME = NAME | list

    public static void main(String[] args) throws NoViableAltException, RecognitionException, MismatcherTokenException, PreviousParseFailedException {
        ListLexer l = new ListLexer("[a,b]=[c,d]=[f]");
        LookaheadParser parser = new LookaheadParser(l, 2);//LL(2)
        //parser.match(Lexer.Equal);
        parser.stat();
    }
}
