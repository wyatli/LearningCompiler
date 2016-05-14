import javax.rmi.CORBA.Util;
import java.util.*;
import Exception.*;
/**
 * Created by abc84 on 2016/5/14.
 */
public class FormulaSolver {
    private FormulaLexer lexer ;
    private String toSolve;
    private ArrayList<Token> NameTokens;
    public FormulaSolver(String toSolve) throws MismatcherTokenException {
        this.toSolve = toSolve;
        lexer = new FormulaLexer(toSolve);
        checkValidInput(toSolve);
        NameTokens = new ArrayList<>();
        fillInName(NameTokens);
    }

    public Set<Character> noneDup() {//把单词拆成字母，放进一个set不重复
        Set<Character> noneDup = new HashSet<>();
        for (Token t:NameTokens) {
            int len = t.rep().length();
            for (int i = 0; i < len; i++) {
                noneDup.add(t.rep().charAt(i));
            }
        }
        return noneDup;
    }
    private List<String> translateds() {//所有已翻译的字符串
        List<String> trans = new ArrayList<>();
        List<List<Integer>> lists = new ArrayList<>();
        Set<Character> chars = noneDup();
        permutations(lists, Arrays.asList(0,1,2,3,4,5,6,7,8,9),
                new ArrayList<>(), chars.size());
        for (List<Integer> ints : lists) {//在所有排列里
            Map<Character, Integer> map = new HashMap<>();//映射表如（a,b,c）->(1,2,3)
            int i = 0;
            for (Character c : chars) {
                map.put(c, ints.get(i));
                i++;
            }
            //System.out.println(map);
           String s = transWithMap(map);
           // System.out.println(s);
            if (s.length() != 0)
                trans.add(s);
        }
        return trans;
    }

    private String transWithMap(Map<Character, Integer> map) {//用得到的map 进行转换
        String s = "";
        boolean valid = true;
        for(int j = 0; j < toSolve.length(); j++) {//将该字符串处理为映射表翻译的形式//如a+b==c - >0+1==2
            //char c = toSolve.charAt(i);
            // System.out.println(map.get(toSolve.charAt(j)));
            if (map.get(toSolve.charAt(j))!= null) {
                if (map.get(toSolve.charAt(j))==0 && j+1 < toSolve.length() &&
                        map.get(toSolve.charAt(j+1)) != null)
                {valid = false;break;}//若当前映射为0，下一个映射！=null则形式为0x（e.g 02）
                // ,valid标志设成false，不生成该字符串
                s += map.get(toSolve.charAt(j));
            }
            else
                s += toSolve.substring(j,j+1);
        }
        if (!valid) return "";
        return s;
    }

    private static void permutations(List<List<Integer>> target,List<Integer> elems,List<Integer> store, int k) {
        //k个elems元素的排列

        if (store.size() == k) {
            target.add(store);
            return;
        }
        for (int i = 0; i < elems.size(); i++) {
            List<Integer> newDatas = new ArrayList<Integer>(elems);
            List<Integer> newTarget = new ArrayList<Integer>(store);
            newTarget.add(newDatas.get(i));
            newDatas.remove(i);
            permutations(target,newDatas, newTarget, k);
        }

    }
    private void checkValidInput(String s) throws MismatcherTokenException {//check if the input is valid using parser
        //FormulaParser parser = new FormulaParser(lexer);
        FormulaParser parser = new FormulaParser(new FormulaLexer(toSolve));
        parser.formula();
    }
    private void fillInName(ArrayList<Token> nameTokens) {
        Token token = lexer.nextToken();
        while (token.type != Lexer.EOF_TYPE) {
            //System.out.println(token);
            if (token.type == Lexer.NAME) {
                NameTokens.add(token);
            }
            token = lexer.nextToken();
        }
        System.out.println(NameTokens);
    }
//    public String candidate() {
//        for (String can : translateds()) {
//
//        }
//    }
    public static void main(String[] args) throws MismatcherTokenException {
        FormulaSolver solver = new FormulaSolver("ac+b*f==c");
        System.out.println(solver.noneDup());
        List<List<Integer>> l = new ArrayList<>();
        List<Integer> elems = Arrays.asList(0,1,2,3, 4,5,6,7,8,9);
        permutations(l,elems,new ArrayList<>(),3);
        //System.out.println(l);
        System.out.println(solver.translateds());
    }
}
