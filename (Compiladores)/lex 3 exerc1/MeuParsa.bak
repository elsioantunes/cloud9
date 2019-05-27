public class MeuParsa extends Parser{

    public Boolean isOK(){
        System.out.println("##############################");
        list();
        System.out.println("------------------------------");

        if(!lastToken()) E();
        return true;
    }
    
    public void E(){
        NUM();
        OP();
    }
    
    public void NUM(){
        noComment();
        if(code.equals("[NUM INTEIRO]") || code.equals("[NUM REAL]") || code.equals("[IDENTIFICADOR]")){
            System.out.println("NUM: "+code);
            nextToken();
        }
        else falha();
    }

    public void OP(){
        noComment();
        if(code.equals("[OP_EXPO]") || code.equals("[OP_MINUS]") || code.equals("[OP_PLUS]") || code.equals("[OP_MULTIPLY]") || code.equals("[OP_DIV]")) {
            System.out.println("OP: "+code);
            nextToken();
            E();
        }
        else falha();
    }
    
    MeuParsa(String str){super(str);}
}