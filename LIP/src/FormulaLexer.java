import java.util.HashMap;

/**
 * Created by abc84 on 2016/5/14.
 */
public class FormulaLexer extends Lexer {


    public FormulaLexer(String s) {
        super(s);
    }

    @Override
    public Token nextToken() {
        while (currentChar != EOF) {
            //System.out.println(currentChar);
            switch (currentChar) {
                case ' ':case '\n':case '\t':case '\r':ignore();continue;
                //case ',':comsume();return new Token(COMMA, ",");
                case '=':
                    comsume();
                    if (currentChar == '=') {
                        comsume();
                        return new Token(EQUALS, "==");
                    }
                    return new Token(Equal,"=");
                case '+':comsume();return new Token(OPS,"+");
                case '-':comsume();return new Token(OPS,"-");
                case '*':comsume();return new Token(OPS,"*");
                case '/':comsume();return new Token(OPS,"/");

                default:
                    if (isLetter()) {//字母的话继续一直到成为一个名字
                        return Name();
                    }
                    else if (isDigit()) {
                        return digits();
                    }
                    else throw new Error("invalid char:" + currentChar);
            }
        }
        return new Token(EOF_TYPE, "<EOF>");
    }

    private Token digits() {
        StringBuffer buffer = new StringBuffer();
        while (isDigit()) {//直到不为字母
            buffer.append(currentChar);
            comsume();//跳到下一个
        }
        return new Token(NUM, buffer.toString());
    }

    private Token Name() {//"[a-z|A-Z]+"
        StringBuffer buffer = new StringBuffer();
        while (isLetter()) {//直到不为字母
            buffer.append(currentChar);
            comsume();//跳到下一个
        }
        return new Token(NAME, buffer.toString());
    }

    @Override
    public String getTokenName(int i) {
        return FormulaLexer.typeToName.get(i);
    }
    public static void main(String[] args) {
        FormulaLexer lexer = new FormulaLexer("aaa-+5432 == 7");
        Token t = lexer.nextToken();
        while (t.type != EOF_TYPE) {
            System.out.println(t);
            t = lexer.nextToken();
        }
        System.out.println(t);
    }
}
