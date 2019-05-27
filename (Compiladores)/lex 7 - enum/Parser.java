// A classe MeuParsa extende Parser, que contém as ferramentas essenciais aqui.
// MeuParsa é que depende da linguagem. Parser é a parte que não mudaria para uma linguagem diferente.
class MeuParsa extends Parser {
    MeuParsa(String arq){
        super(arq);
        verbose = true;
        print("MeuParsa aqui");
        getToken(); parse();
        if(is(TokenTypes.EOF)) print("chegou ao fim do arquivo com sucesso!");
    }
    
    /*
        PARSE -> DECLARE_INT | DECLARE_FLOAT | DECLARE_STRING |
                 PRINT | INPUT | ATRIB |
                 TOKEN_INVÁLIDO | STRING | NUMERO | CHAR | SEMICOLON... 
    */
    
    // método principal
    // ao chegar aqui, já temos o primeiro token code, pedido no construtor.
    public void parse(){
        while(CODE != TokenTypes.EOF){
            if(is(TokenTypes.LITERAL_INT)) declare();
            else if(is(TokenTypes.LITERAL_FLOAT)) declare();
            else if(is(TokenTypes.LITERAL_STRING)) declare();

            else if(is(TokenTypes.LITERAL_PRINT)) print();
            else if(is(TokenTypes.LITERAL_INPUT)) input();
            else if(is(TokenTypes.T_ID)) atrib();

            //else if(is(TokenTypes.LITERAL_IF)) ifthenelse();
            //else if(is(TokenTypes.LITERAL_WHILE)) dowhile();
            
	/*
	LITERAL_FLOAT, LITERAL_INT, LITERAL_STRING, LITERAL_PRINT, LITERAL_INPUT,
	
	não implementado
	LITERAL_IF, LITERAL_THEN, LITERAL_ELSE, LITERAL_ENDIF, 
	LITERAL_FOR, LITERAL_TO, LITERAL_STEP, LITERAL_NEXT, LITERAL_WHILE, LITERAL_UNTIL, 
	LITERAL_REM, LITERAL_GOTO, LITERAL_GOSUB, LITERAL_RETURN, LITERAL_SUB, LITERAL_ENDSUB, 
	*/

            // possiveis erros previsíveis 
            else if(is(TokenTypes.TOKEN_INVALIDO)) {noMatch("token inválido");}
            else if(is(TokenTypes.T_STRING)) {noMatch("string");}
            else if(is(TokenTypes.T_CHAR)) {noMatch("char");}
            else if(is(TokenTypes.NUMBER2)) {noMatch("número");}
            else if(is(TokenTypes.NUMBER)) {noMatch("número");}
            else if(is(TokenTypes.DELIMIT_SEMICOLON)) {noMatch("ponto e virgula");}
            else {getToken(); print("sei lá o que pode ser em " + LIN +", " + COL);}
        }
    }
    
    
    /*
        DECLARE -> ("STRING"|"FLOAT"|"STRING") ID (COMMA ID)* SEMICOLON
    */
    public void declare(){
        getToken();
        match(TokenTypes.T_ID);
        while(is(TokenTypes.DELIMIT_COMMA)){
            getToken();
            match(TokenTypes.T_ID);
        }
        match(TokenTypes.DELIMIT_SEMICOLON);
    }
    
    
    /*
        ATRIB -> ID ASSIGN (STRING|NUMERO|CHAR|ERRO) SEMICOLON
    */
    public void atrib(){
        getToken();
        match(TokenTypes.OP_ASSIGN);
        if(is(TokenTypes.T_STRING)) getToken();
        else if(is(TokenTypes.NUMBER)) getToken();
        else if(is(TokenTypes.NUMBER2)) getToken();
        else if(is(TokenTypes.T_CHAR)) getToken();
        else noMatch();
        match(TokenTypes.DELIMIT_SEMICOLON);
    }
    

    /*
        PRINT -> "PRINT" ID SEMICOLON
    */
    public void print(){
        getToken();
        int res = expr();
        //match(TokenTypes.T_ID);
        match(TokenTypes.DELIMIT_SEMICOLON);
        print ("imprimiu "+res);
        
        
    }
    

    /*
        INPUT -> ID (COMMA ID)* SEMICOLON
    */
    public void input(){
        getToken();
        match(TokenTypes.T_ID);
        while(is(TokenTypes.DELIMIT_COMMA)){
            getToken();
            match(TokenTypes.T_ID);
        }
        match(TokenTypes.DELIMIT_SEMICOLON);
    }
    







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
    


    public int toInt(String str){return Integer.parseInt(str);}


}

// Classe principal que faz análise sintática de qualquer linguagem.
class Parser{
    boolean verbose;
    public java.util.HashMap <String, Integer> mv;
    public TokenTypes CODE;
    public MeuLek ml;
    public Token token;
    public String TEXT;
    public int LIN, COL;
    
    Parser(String arq){
        print("Parser aqui");
        mv = new java.util.HashMap <String, Integer> ();
        ml = new MeuLek(arq);
    }
    
    public boolean check(TokenTypes code){
        boolean ret = is(code);
        if(ret) match(code);
        return ret;
    }
    
    public boolean check(TokenTypes code1,TokenTypes code2){
        boolean ret = is(code1)^is(code2);
        if(ret){
            check(code1);
            check(code2);
        }
        return ret;
    }
    
    public void noMatch(String str){
        print(
            ""+ LIN + ", "+COL+
            " - não esperava " +str+" neste momento"
            );
        getToken();
    }
        
    public void noMatch(){
        print(
            ""+ LIN + ", "+COL+
            " - " + CODE + " não era esperado neste momento."
            );
    }
        
    public void match(TokenTypes code){
        if(is(code)) getToken();
        else {
            print(
                "Não deu match!" + LIN + ", "+COL+
                "\nesperava " + code + " mas veio " + CODE
                );
            System.exit(256+24);
        }
    }
        
    // apenas confirma se o code do token é aquele esperado
    public boolean is(TokenTypes code){
        return code == CODE;
    }
    
    // getToken. Recebe o token do analisador léxico 
    // e seta as variáveis CODE, TEXT, LIN e COL.
    public boolean getToken(){
        ml.getToken();
        CODE = ml.token.code;
        TEXT = ml.token.str;
        LIN = ml.token.lin;
        COL = ml.token.col;
        if (verbose) print(":::"+CODE);
        if (verbose && is(TokenTypes.DELIMIT_SEMICOLON)) print("");
        return ml.token.code != TokenTypes.EOF;
    }
    
    // debug
    public void print(String str){
        System.out.println(str);
    }

    // versão do debug que encerra o programa
    public void print(String str, int lol){
        print(str);
        System.exit(256+24);
    }
}