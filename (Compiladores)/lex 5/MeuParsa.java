class MeuParsa extends Parser {
    public int res;
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
        while(CODE ==  ml.LITERAL_STRING || CODE ==  ml.LITERAL_INT ||  CODE ==  ml.LITERAL_FLOAT){
            b = TEXT; // teste
            if(CODE ==  ml.LITERAL_STRING) match(ml.LITERAL_STRING);
            else if(CODE ==  ml.LITERAL_INT) match(ml.LITERAL_INT);
            else if(CODE ==  ml.LITERAL_FLOAT) match(ml.LITERAL_FLOAT);
            else debug("tá declarando o que aí manolo?");
            a = TEXT; // teste
            match(ml.T_ID);
            debug("declarou " + a + " como " + b); // teste
            if(b == "INT") declara(a);
            while(CODE ==  ml.DELIMIT_COMMA){
                match(ml.DELIMIT_COMMA);
                a = TEXT; // teste
                match(ml.T_ID);
                debug("declarou " + a + " como " + b); // teste
                if(b == "INT") declara(a);
            }
            match(ml.DELIMIT_SEMICOLON);
        }
    } 

    public void corpo(){
        while(CODE != ml.EOF){
            if(CODE ==  ml.LITERAL_PRINT) print(); 
            else if(CODE ==  ml.LITERAL_READ) read(); 
            else if(CODE ==  ml.T_ID) atrib();
            else if(CODE ==  ml.NUMBER || CODE ==  ml.NUMBER2){
                debug(" WARING: esse numero na linha " + token.lin +", no " +token.col+"º caractere está no lugar errado");
                if(CODE ==  ml.NUMBER) match(ml.NUMBER);
                if(CODE ==  ml.NUMBER2) match(ml.NUMBER2);
            } 
            match(ml.DELIMIT_SEMICOLON);
            while(CODE ==  ml.DELIMIT_SEMICOLON){
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
        if(CODE == ml.T_CHAR) match(ml.T_CHAR);
        else if(CODE == ml.T_STRING) match(ml.T_STRING);
        else if(CODE == ml.NUMBER) match(ml.NUMBER);
        else if(CODE == ml.NUMBER2) match(ml.NUMBER2);
        else debug("vc não pode atribuir isso", 666);

        debug("atribuiu " + b + " à " + a); // teste
        try{
            atribui(a, b);    
        }catch(Exception ex){
            
        }
        
    }

    public void print(){
        match(ml.LITERAL_PRINT);
        a = TEXT; // teste
        //match(ml.T_ID);
        expr();
        debug("imprimiu " + res); // teste
    }
    
    public void read(){
        match(ml.LITERAL_READ);
        String a = TEXT;
        match(ml.T_ID);
        debug("leu " + a);
        while(CODE ==  ml.DELIMIT_COMMA){
            match(ml.DELIMIT_COMMA);
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




    public void expr(){
        termo();
        res = VALOR;
        exprl();
    }

    public void termo(){
        if(CODE == ml.NUMBER) {             // numero
            VALOR = toInt(TEXT);
            match(ml.NUMBER);
        }
        else if(CODE == ml.T_ID) {          // variável
            VALOR = mv.get(TEXT).intValue();
            match(ml.T_ID);
        }
        else debug("Só dá pra dar print em expressão valida");
    }
    
    public void exprl(){
        while(CODE == ml.OP_PLUS || CODE == ml.OP_MINUS){
            OP = TEXT;
            if(CODE == ml.OP_PLUS) match(ml.OP_PLUS);
            if(CODE == ml.OP_MINUS) match(ml.OP_MINUS);
            termo();
            
            if(OP.equals("+")){
                res += VALOR;
            }else{
                res -= VALOR;
            }
        }
    }
    
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
    
    public void match(int code){
        if(code == CODE)
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

    public void atribui(String a, String b){
        mv.put(a, toInt(b));
    }
    
    public void declara(String a){
        mv.put(a, 0);
    }
    
    public int toInt(String str){
        return Integer.parseInt(str);
    }

    public void debug(String str){System.out.println(str);}
    public void debug(int val){debug(""+val);}
    
    public void debug(String str, int lol){
        debug("Erro na linha "+ ml.token.lin+", coluna " + ml.token.col);
        debug("\n"+str);
        System.exit(256+24);
    }
}
