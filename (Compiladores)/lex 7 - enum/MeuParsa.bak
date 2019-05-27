////import static Expression.*;
class MeuParsa extends Parser {
    public String a, b; // para testes

    MeuParsa(String file){
        super(file); 
        prog(); 
    }

    public void prog(){
        declara();
        corpo();
        eof();
    }

    public void declara(){
        while(is(ml.LITERAL_STRING) || is(ml.LITERAL_INT) ||  is(ml.LITERAL_FLOAT)){
            b = TEXT; // teste
            if(check(ml.LITERAL_STRING) || check(ml.LITERAL_INT) || check(ml.LITERAL_FLOAT)){
                a = TEXT; // teste
                match(ml.T_ID);
                debug("declarou " + a + " como " + b); // teste
                if(b == "INT") declara(a);
                while(check(ml.DELIMIT_COMMA)){
                    a = TEXT; // teste
                    match(ml.T_ID);
                    debug("declarou " + a + " como " + b); // teste
                    if(b == "INT") declara(a);
                }
                match(ml.DELIMIT_SEMICOLON);
            }
        }
    } 

    public void corpo(){
        while(CODE != ml.EOF){
            if(is(ml.LITERAL_PRINT)) print(); 
            else if(is(ml.LITERAL_READ)) read(); 
            else if(is(ml.T_ID)) atrib();
            else if(is(ml.NUMBER) || is(ml.NUMBER2)){
                debug(" WARING: esse numero na linha " + token.lin +", no " +token.col+"º caractere está no lugar errado");
                check(ml.NUMBER);
                check(ml.NUMBER2);
            } 
            match(ml.DELIMIT_SEMICOLON);
            while(is(ml.DELIMIT_SEMICOLON)){
                debug(" WARING: Dois pontos fora de contexto na linha " + token.lin+ " posso ignorar isso.");
                match(ml.DELIMIT_SEMICOLON);
            }         
        }
    }
    
    
    public void atrib(){
        a = TEXT; // teste
        match(ml.T_ID);
        match(ml.OP_ASSIGN);
        b = TEXT; // teste
        if(check(ml.T_CHAR)||check(ml.T_STRING)||check(ml.NUMBER)||check(ml.NUMBER2)){
            debug("atribuiu " + b + " à " + a); // teste
            try{atribui(a, b);}catch(Exception ex){}
        } 
        else debug("vc não pode atribuir isso", 666);
    }

    public void print(){
        match(ml.LITERAL_PRINT);
        debug("imprimiu " + expr());

    }
    
    public void read(){
        match(ml.LITERAL_READ);
        String a = TEXT;
        match(ml.T_ID);
        debug("leu " + a);
        while(check(ml.DELIMIT_COMMA)){
            a = TEXT;
            match(ml.T_ID);
            debug("leu " + a);
        }
    }
    

    public void eof(){
        if(CODE != ml.EOF) 
            debug("Término inesperado", 666);
        else
            match(ml.EOF);
        debug("deu tudo certo");
    };




    /*
        expr     -> product    (( + | - ) product)
        product -> value      (( * | / ) value)
        value   -> number  |  ( expr )
    
    */


    public int expr(){
        int soma = product();
        while(is(ml.OP_PLUS) || is(ml.OP_MINUS)){
            boolean op = is(ml.OP_PLUS);
            check(ml.OP_PLUS, ml.OP_MINUS);
            int produto = product();
            soma += op?produto:-produto;
        }
        return soma;
    }

    public int product(){
        int produto = value();
        while(is(ml.OP_TIMES) || is(ml.OP_DIV)){
            boolean op = is(ml.OP_TIMES);
            check(ml.OP_DIV, ml.OP_TIMES);
            int valor = value();
            if(op) produto *= valor;
            else produto /= valor;
        }
        return produto;
    }
    
    public int value(){
        int valor;
        if(is(ml.NUMBER)){
            valor = toInt(TEXT);
            match(ml.NUMBER);

        }else{
            match(ml.DELIMIT_LPAR);
            valor = expr();
            match(ml.DELIMIT_RPAR);
        }
        return valor;
    }
    
    
    
    
    
    public void atribui(String a, String b){mv.put(a, toInt(b));}
    public void declara(String a){mv.put(a, 0);}
    public int toInt(String str){return Integer.parseInt(str);}
    public int varValue(String str){return mv.get(str).intValue();}

}

class Parser{
    public java.util.HashMap <String, Integer> mv;    
    public String TEXT;
    public String OP;
    public String NOME_VAR;
    public int VALOR;
    public int CODE;
    public MeuLek ml;
    public Token token;
    
    Parser(String file){
        mv = new java.util.HashMap <String, Integer> ();    
        ml = new MeuLek(file);
        getToken();
    }
    
    public boolean check(int code){
        boolean ret = is(code);
        if(ret) match(code);
        return ret;
    }
    
    public boolean check(int code1,int code2){
        boolean ret = is(code1)^is(code2);
        if(ret){
            check(code1);
            check(code2);
        }
        return ret;
    }
    
    public boolean is(int code){
        return code == CODE;
    }
    
    public void match(int code){
        if(is(code))
            getToken();
        else
            debug(
                "não deu match!" +
                "\nesperava " + ml.nomes[code]+ " e veio " + ml.nomes[CODE]
                ,666
            );
    }

    public void getToken(){
        ml.getToken();
        token = ml.token;
        CODE = token.code; 
        TEXT = token.texto; 
    }

    public void debug(String str){System.out.println(str);}
    public void debug(int val){debug(""+val);}
    
    public void debug(String str, int lol){
        debug("Erro na linha "+ ml.token.lin+", coluna " + ml.token.col);
        debug("\n"+str);
        System.exit(256+24);
    }
}
