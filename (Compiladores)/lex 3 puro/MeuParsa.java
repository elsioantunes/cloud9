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
        if(code=="[NUM INTEIRO]"|| code=="[NUM REAL]"|| code=="[IDENTIFICADOR]"){
            System.out.println("NUM: "+code);
            nextToken();
        }
        else falha();
    }

    public void OP(){
        if(code=="[OP_EXPO]"|| code=="[OP_MINUS]"|| code=="[OP_PLUS]"|| code=="[OP_DIV]"|| code=="[OP_MULTIPLY]") {
            System.out.println("OP: "+code);
            nextToken();
            E();
        }
        else falha();
    }
    
    MeuParsa(String str){super(str);}
}