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
        while(is(TokenTypes.LITERAL_STRING) || is(TokenTypes.LITERAL_INT) ||  is(TokenTypes.LITERAL_FLOAT)){
            b = TEXT; // teste
            if(check(TokenTypes.LITERAL_STRING) || check(TokenTypes.LITERAL_INT) || check(TokenTypes.LITERAL_FLOAT)){
                a = TEXT; // teste
                match(TokenTypes.T_ID);
                debug("declarou " + a + " como " + b); // teste
                if(b == "INT") declara(a);
                while(check(TokenTypes.DELIMIT_COMMA)){
                    a = TEXT; // teste
                    match(TokenTypes.T_ID);
                    debug("declarou " + a + " como " + b); // teste
                    if(b == "INT") declara(a);
                }
                match(TokenTypes.DELIMIT_SEMICOLON);
            }
        }
    } 

    public void corpo(){
        while(CODE != TokenTypes.EOF){
            if(is(TokenTypes.LITERAL_PRINT)) print(); 
            else if(is(TokenTypes.LITERAL_READ)) read(); 
            else if(is(TokenTypes.T_ID)) atrib();
            else if(is(TokenTypes.NUMBER) || is(TokenTypes.NUMBER2)){
                debug(" WARING: esse numero na linha " + token.lin +", no " +token.col+"º caractere está no lugar errado");
                check(TokenTypes.NUMBER);
                check(TokenTypes.NUMBER2);
            } 
            match(TokenTypes.DELIMIT_SEMICOLON);
            while(is(TokenTypes.DELIMIT_SEMICOLON)){
                debug(" WARING: Dois pontos fora de contexto na linha " + token.lin+ " posso ignorar isso.");
                match(TokenTypes.DELIMIT_SEMICOLON);
            }         
        }
    }
    
    
    public void atrib(){
        a = TEXT; // teste
        match(TokenTypes.T_ID);
        match(TokenTypes.OP_ASSIGN);
        b = TEXT; // teste
        if(check(TokenTypes.T_CHAR)||check(TokenTypes.T_STRING)||check(TokenTypes.NUMBER)||check(TokenTypes.NUMBER2)){
            debug("atribuiu " + b + " à " + a); // teste
            try{atribui(a, b);}catch(Exception ex){}
        } 
        else debug("vc não pode atribuir isso", 666);
    }

    public void print(){
        match(TokenTypes.LITERAL_PRINT);
        debug("imprimiu " + expr());

    }
    
    public void read(){
        match(TokenTypes.LITERAL_READ);
        String a = TEXT;
        match(TokenTypes.T_ID);
        debug("leu " + a);
        while(check(TokenTypes.DELIMIT_COMMA)){
            a = TEXT;
            match(TokenTypes.T_ID);
            debug("leu " + a);
        }
    }
    

    public void eof(){
        if(CODE != TokenTypes.EOF) 
            debug("Término inesperado", 666);
        else
            match(TokenTypes.EOF);
        debug("deu tudo certo");
    };




    /*
        expr     -> product    (( + | - ) product)
        product -> value      (( * | / ) value)
        value   -> number  |  ( expr )
    
    */


    public int expr(){
        int soma = product();
        while(is(TokenTypes.OP_PLUS) || is(TokenTypes.OP_MINUS)){
            boolean op = is(TokenTypes.OP_PLUS);
            check(TokenTypes.OP_PLUS, TokenTypes.OP_MINUS);
            int produto = product();
            soma += op?produto:-produto;
        }
        return soma;
    }

    public int product(){
        int produto = value();
        while(is(TokenTypes.OP_TIMES) || is(TokenTypes.OP_DIV)){
            boolean op = is(TokenTypes.OP_TIMES);
            check(TokenTypes.OP_DIV, TokenTypes.OP_TIMES);
            int valor = value();
            if(op) produto *= valor;
            else produto /= valor;
        }
        return produto;
    }
    
    public int value(){
        int valor;
        if(is(TokenTypes.NUMBER)){
            valor = toInt(TEXT);
            match(TokenTypes.NUMBER);

        }else{
            match(TokenTypes.DELIMIT_LPAR);
            valor = expr();
            match(TokenTypes.DELIMIT_RPAR);
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
                "\nesperava " + TokenTypes.nomes[code]+ " e veio " + TokenTypes.nomes[CODE]
                ,666
            );
    }

    public void getToken(){
        TokenTypes.getToken();
        token = TokenTypes.token;
        CODE = token.code; 
        TEXT = token.texto; 
    }

    public void debug(String str){System.out.println(str);}
    public void debug(int val){debug(""+val);}
    
    public void debug(String str, int lol){
        debug("Erro na linha "+ TokenTypes.token.lin+", coluna " + TokenTypes.token.col);
        debug("\n"+str);
        System.exit(256+24);
    }
}
