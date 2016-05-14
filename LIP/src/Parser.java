import com.sun.corba.se.impl.oa.toa.TOA;

import java.util.ArrayList;
import java.util.List;
import Exception.*;
/**
 * Created by abc84 on 2016/5/12.
 */
/*
语义分析，回溯法，任意长度向前看
 */
public class Parser {
    private int index = 0;
    private List<Token> lookahead;//环形缓冲区
    private List<Integer> markers;//存放当前的index以便后面回溯（mark and release）
    private Lexer lexer;
    private int k; //LL(K)文法

    public Parser(Lexer lexer, int k) {
        this.lexer = lexer;
        this.k = k;
        lookahead = new ArrayList<>();
        markers = new ArrayList<>();
//        for (int i = 0; i < k; i++) {//初始化缓冲区
//            consume();
//        }
    }
    public int pos() {
        return index;
    }
    public int LAT(int i) {//LL(1)
        return LT(i).type;
    }
    public Token LT(int i) {//LL(k)\\
        sync(i);//确保前面有i个Token
        return lookahead.get(index + i - 1);
        //return lookahead[(index + i - 1) % k];//环式取值
    }
    public void mark() {//标记存入，以便后面收回
        markers.add(index);
    }
    public void release() {//从marker栈中取出,并销毁
        index = markers.get(markers.size() - 1);
        markers.remove(markers.size() - 1);
    }
    private void sync(int i) {
        if (index + i - 1 > (lookahead.size() - 1)) {
            int n = index + i - 1 - (lookahead.size() - 1);
            fill(n);//向缓冲区填入n个Tooken
        }
    }

    private void fill(int n) {//向缓冲区填入n个Tooken
        for(int i = 0; i < n; i++) {
            lookahead.add(lexer.nextToken());
        }
    }

    public void consume() {
        index++;
//        lookahead[index] = lexer.nextToken();
//        index = (index+1) % k;
        if (index == lookahead.size() && !isSpeculating()) {//若到了末尾且没有在推断中，就重新填入词法单元
            index = 0;
            lookahead.clear();
        }
        sync(1);//确保后面有一个,以便下次match
    }
    public void match(int type) throws MismatcherTokenException {
        if (type == LAT(1)) consume();
        else {
            throw new MismatcherTokenException("expecting type" + Lexer.typeToName.get(type)
                            + "; found " + LT(1));
        }
    }

    private boolean isSpeculating() {
        return !markers.isEmpty();//若标记还在表明还在推断
    }
}
