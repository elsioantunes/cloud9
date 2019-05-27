public class Token{
    public static final int BLANK               = -2;
    public static final int EOF                 = -1;
    public static final int NUMERO_INTEIRO      =  0;
    public static final int NUMERO_PONTO_FIXO   =  1;
    public static final int OPERADOR_ARIT       =  2;
    public static final int ID                  =  3;


    
    private int    code;
    private String symbol;
    
    public void setCode(int code){
        this.code = code;
    }
    public int getCode(){
        return this.code;
    }
    
    public void setSymbol(String symbol){
       this.symbol = symbol;
    }
    public String getSymbol(){
       return this.symbol;
    }
}