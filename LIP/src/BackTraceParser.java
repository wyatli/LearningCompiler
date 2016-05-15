import java.util.HashMap;
import Exception.*;
/**
 * Created by abc84 on 2016/5/15.
 */
/*
带记忆功能的回溯解析器
 */
public class BackTraceParser extends LookaheadParser {

    public static final int FAILED = -1;//解析失败
    private HashMap<Integer, Integer> list_mem = new HashMap<>();//记忆之前解析过的startindex对应的
                                                                // endindex，若failed返回-1

    public BackTraceParser(Lexer lexer) {
        super(lexer, 1);
    }

    @Override
    public void list() throws MismatcherTokenException, RecognitionException, PreviousParseFailedException {
        boolean failed = false;
        int startIndex = index();//开始解析时的位置
        if (isSpeculating() && alreadyParsed()) return;//若当前已经解析过了且成功了，就将index置为mem里对应的endindex
        try{
            _list();
        }catch (Exception e){
            e.printStackTrace();
            failed = true;
        }finally {//无论是否解析成功都要记录startIndex对应的状态
           if (isSpeculating()) memorize(list_mem, startIndex, failed);
        }
        //System.out.println(list_mem);
    }

    @Override
    public void consume() {
        index ++;
        if (index == lookahead.size() && !isSpeculating() ) {
            index = 0;
            lookahead.clear();
            list_mem.clear();//多处这一条
        }
        sync(1);
    }

    private void memorize(HashMap<Integer, Integer> list_mem, int startIndex, boolean failed) {
        int endIndex = failed ? FAILED : index();
        list_mem.put(startIndex, endIndex);
        //System.out.println(list_mem);
    }
//    @Override//不能override因为这回调用_list(),而不是list()，就不能记忆恢复了
//    public void asign() throws MismatcherTokenException, RecognitionException, PreviousParseFailedException {//[a,b] = [c,d]
//        _list();match(Lexer.Equal);_list();
//
//    }

    private void _list() throws RecognitionException, MismatcherTokenException, PreviousParseFailedException {
        System.out.println("parsing list at index " + index());
        match(Lexer.LBRACKT);elements();match(Lexer.RBRACKT);//'['elements']'
    }

//    @Override//道理同上
//    public void element() throws RecognitionException, MismatcherTokenException, PreviousParseFailedException {//[a=b]|[a]||[c,[a,a=b]]
//        if (LT(1).type == ListLexer.NAME && LT(2).type == ListLexer.Equal) {//'a=b'
//            match(ListLexer.NAME);
//            match(ListLexer.Equal);
//            match(ListLexer.NAME);
//        }
//        else if (LT(1).type == ListLexer.LBRACKT) _list();//'['
//        else if (LT(1).type == ListLexer.NAME)match(ListLexer.NAME);//'a'
//        else {
//            throw new RecognitionException("expecting name or list; found" + LT(1)+" at " + index());
//        }
//    }//NAME | NAME = NAME | list

    private boolean alreadyParsed() throws PreviousParseFailedException {
        Integer endIndex = list_mem.get(index());
        if (endIndex == null) return false;
        //int val = endIndex;

        if (endIndex == FAILED ) throw new PreviousParseFailedException("at index " + index());
        else {//already parsed
            System.out.println("parse list before at " + index()
                    + ";" + "skip ahead to token index " +
                    endIndex + " : " + lookahead.get(endIndex).rep());
            index = endIndex;//refresh cur index
            return true;
        }
    }
    public static void  main(String[] args) throws RecognitionException, NoViableAltException, MismatcherTokenException, PreviousParseFailedException {
        ListLexer lexer = new ListLexer("[a,b]=[d]");
        BackTraceParser parser = new BackTraceParser(lexer);
        parser.stat();
    }
}
