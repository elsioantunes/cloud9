public class Lexico{
    private String Buf;
    public int i;
    public Token t;
    Lexico(String str){Buf=str+'\0'; i=0;};
    public char nextChar(){if(i<Buf.length())return Buf.charAt(i++);else return '\0';};
    public void Recognize(String nome){t.estado="final"; t.tipo = nome;}
    public void Recognize(String nome, int lol){i--; t.skip=true; Recognize(nome);}
    public boolean Digit(char c) {return (c >= '0' && c <= '9');}
    public boolean Alphan(char c) {return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';}
    public void reset(){i=0;}
}




