class MeuParsa extends Parser {
    MeuParsa(String file){super(file); prog(); fim();}

    public void prog(){
        declara();
        atribui();
        escreve();
        
        Object[] vals = MV.values().toArray();
        for(Object o:vals) System.out.println(o);
        System.out.println("\n");
        
        debug("O resultado é "+res);
    }

    public void escreve(){
        match(ml.LITERAL_PRINT);
        expr();
        match(ml.DELIMIT_SEMICOLON);
    }

    public void expr(){
        termo();
        res = VALOR;
        exprl();
    }

    public void termo(){
        if(CODE == ml.NUMBER) {
            VALOR = Integer.parseInt(TEXT);
            match(ml.NUMBER);
        }
        else if(CODE == ml.T_ID) {
            VALOR = MV.get(TEXT).intValue();
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

    public void declara(){
        match(ml.LITERAL_DECLARE);
        MV.put(TEXT, 0);
        match(ml.T_ID);
        while(CODE == ml.DELIMIT_COMMA){
            match(ml.DELIMIT_COMMA);
            MV.put(TEXT, 0);
            match(ml.T_ID);
        }
        match(ml.DELIMIT_SEMICOLON);
    }    

    public void atribui(){
        while(CODE == ml.T_ID){
            idVar = TEXT;
            match(ml.T_ID);
            match(ml.OP_ASSIGN);
            if(CODE == ml.NUMBER) {
                MV.put(idVar, Integer.parseInt(TEXT));
                match(ml.NUMBER);
            }
            else if(CODE == ml.NUMBER2) match(ml.NUMBER2);
            else if(CODE == ml.T_STRING) match(ml.T_STRING);
            match(ml.DELIMIT_SEMICOLON);
        }
    }    

    public static void main(String args[]){
        MeuParsa mp = new MeuParsa("in");
    }
}

class Parser{
    public java.util.HashMap <String, Integer> MV;    
    public String TEXT;
    public String OP;
    public String idVar;
    public int VALOR;
    public int CODE;
    public MeuLek ml;
    public Token token;
    public int res;
    
    Parser(String file){
        MV = new java.util.HashMap <String, Integer> ();    
        ml = new MeuLek(file);
        getToken();
        res = 0;
    }
    
    public void match(int code){
        if(code == CODE)
            getToken();
        else
            debug(
                "Erro na linha "+ ml.token.lin+", coluna " + ml.token.col + 
                "\nesperava " + ml.nomes[code]+ " e veio " + ml.nomes[CODE], 
                666
            );
    }

    public void getToken(){
        ml.getToken();
        token = ml.token;
        CODE = token.code; 
        TEXT = token.texto; 
    }

    public void fim(){
        if(CODE != ml.EOF) debug("Término inesperado");
    };

    public void debug(String str){System.out.println(str);}
    public void debug(int val){System.out.println(val);}
    public void debug(String str, int lol){debug(str);System.exit(256+24);}
}

//System.out.println("tudo pronto");

    /*
        while(ml.getToken()){
            Token t = ml.token;
            System.out.println(t.texto + "\t\t\t" + ml.nomes[t.code] + " " + t.lin + ", " +t.col);
            
        }
    */
