import java.util.HashMap;

/**
 * Created by abc84 on 2016/5/12.
 */
public abstract class Lexer {
    protected String s;
    public static final int EOF = (char)-1;
    public static final int EOF_TYPE = 1;
    protected char currentChar;
    protected int index = 0;
    public static final int RBRACKT = 2;
    public static final int LBRACKT = 3;
    public static final int NAME = 4;
    public static final int COMMA = 5;
    public static final int Equal = 6;
    public static final int EQUALS = 7;//==
    public static final int OPS = 8;//operator
    public static final int NUM = 9;

    static HashMap<Integer, String> typeToName = new HashMap<>();

    static {
        typeToName.put(0, "n/a");
        typeToName.put(1, "<EOF>");
        typeToName.put(2, "RBRACKT");
        typeToName.put(3, "LBRACKT");
        typeToName.put(4, "NAME");
        typeToName.put(5, "COMMA");
        typeToName.put(6, "EQUAL");
        typeToName.put(7, "EQUALS");
        typeToName.put(8, "OPS");
        typeToName.put(9, "NUM");
    }
    public Lexer(String s) {
        this.s = s;
        currentChar = s.charAt(0);
    }
    public void comsume() {
        index++;
        if (index >= s.length())currentChar = EOF;
        else currentChar = s.charAt(index);
    }
    public void ignore() {
        while (currentChar == '\n' || currentChar == '\t'
                || currentChar == '\r' || currentChar == ' '){
            comsume();
        }
    }
    public boolean isDigit() {
        return currentChar >= '0' && currentChar <= '9';
    }
    public boolean isLetter() {
        return currentChar >= 'a' && currentChar <= 'z'
                || currentChar >= 'A' && currentChar <= 'Z' ;
    }
    public abstract Token nextToken();
    public abstract String getTokenName(int i);
}
