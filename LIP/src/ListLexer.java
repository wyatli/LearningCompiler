import java.util.HashMap;

/**
 * Created by abc84 on 2016/5/12.
 */
public class ListLexer extends Lexer {
    public static int RBRACKT = 2;
    public static int LBRACKT = 3;
    public static int NAME = 4;
    public static int COMMA = 5;
    public static int Equal = 6;

    static HashMap<Integer, String> typeToName;
    static {
        typeToName = new HashMap<>();
        typeToName.put(0, "n/a");
        typeToName.put(1, "<EOF>");
        typeToName.put(2, "RBRACKT");
        typeToName.put(3, "LBRACKT");
        typeToName.put(4, "NAME");
        typeToName.put(5, "COMMA");
        typeToName.put(6, "=");
    }
    public ListLexer(String s) {
        super(s);
    }

    @Override
    public Token nextToken() {
        while (currentChar != EOF) {
            //System.out.println(currentChar);
            switch (currentChar) {
                case ' ':case '\n':case '\t':case '\r':ignore();continue;
                case '[':comsume();return new Token(LBRACKT, "[");
                case ']':comsume();return new Token(RBRACKT, "]");
                case ',':comsume();return new Token(COMMA, ",");
                case '=':comsume();return new Token(Equal, "=");
                default:
                    if (isLetter()) {//字母的话继续一直到成为一个名字
                        return Name();
                    }
                    else throw new Error("invalid char:" + currentChar);
            }
        }
        return new Token(EOF_TYPE, "<EOF>");
    }
    public void match(char x) {
        if (x == currentChar){
            comsume();
            return;
        }
        throw new Error("expecting " + x + " found " +currentChar);
    }
    private Token Name() {//"[a-z|A-Z]+"
        StringBuffer buffer = new StringBuffer();
        while (isLetter()) {//直到不为字母
            buffer.append(currentChar);
            comsume();//跳到下一个
        }
        return new Token(NAME, buffer.toString());
    }

    private void comsume() {
        index++;
        if (index >= s.length())currentChar = EOF;
        else currentChar = s.charAt(index);
    }

    private void ignore() {
        while (currentChar == '\n' || currentChar == '\t'
                || currentChar == '\r' || currentChar == ' '){
            comsume();
        }
    }

    @Override
    public String getTokenName(int i) {
        return typeToName.get(i);
    }

    public boolean isLetter() {

        return currentChar >= 'a' && currentChar <= 'z'
                || currentChar >= 'A' && currentChar <= 'Z' ;
    }

    public static void main(String[] args) {
        ListLexer lexer = new ListLexer("[acccc,bccc ]");
        Token t = lexer.nextToken();
        while (t.type != EOF_TYPE) {
            System.out.println(t);
            t = lexer.nextToken();
        }
        System.out.println(t);
    }
}
