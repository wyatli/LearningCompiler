/**
 * Created by abc84 on 2016/5/12.
 */
public abstract class Lexer {
    public static final int EOF = (char)-1;
    public static final int EOF_TYPE = 1;

    protected char currentChar;
    protected int index = 0;
    protected String s;

    public Lexer(String s) {
        this.s = s;
        currentChar = s.charAt(0);
    }

    public abstract Token nextToken();
    public abstract String getTokenName(int i);
}
