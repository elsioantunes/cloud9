public class Token{
    public int i;
    public String tipo,  str, estado;
    public boolean skip;
    Token(){str = ""; estado = "inicial";}
    public void montaStr(char c){str += c;}
}