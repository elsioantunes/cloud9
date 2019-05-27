class MeuParsa extends Parser{
    MeuParsa(String arq){
        super(arq);
        programa();
        if(isEOF()) console("chegou ao fim do arquivo com sucesso");
    }
    
    
    public void programa(){
        while(true){
            if(isDeclareInt()) declare();
            else if(isDeclareFloat()) declare();
            else if(isDeclareString()) declare();
            else if(isCommandPrint()) Print();
            else if(isCommandInput()) input();
            else if(isID()) atrib();
            //else if(isCommandIF()) if(); // TODO
            //else if(isCommandWhile()) While(); // TODO
            else if(isEOF()) break;
            else noExpected();
        }
    }


    public void declare(){
        boolean t = isDeclareString();
        declare(t);
        while(isVirg()) declare(t);
        matchSemicolon();
    }
    public void declare(boolean tipo){
        nextToken();
        if(isDeclared(TEXT))
            waring("variável '"+TEXT+"' já declarada");
        else setVar(tipo, TEXT, "0", false);
        matchId();
    }
    public void setVar(Boolean tipo, String key, String val, boolean inic){
        mv.put(key, val);ma.put(key, inic);ms.put(key, tipo);
    }


    public void atrib(){ // trata a variável
        String var = TEXT;
        if(!isDeclared(var)) erro("variável '"+var+"' não foi declarada");
        nextToken(); //id
        matchAssign();
        atrib(var, isVarAString(var));
        matchSemicolon();
    }
    public void atrib(String var, boolean tipo){ // trata os argumentos
        if(tipo){ // var é string
            if(isString()) setVar(true, var, TEXT,  true);
            else if(isID()){
                if(isVarStringProblem()) waring("var não declarada, não inicializada ou não é string");
                else setVar(true, var, mv.get(TEXT),  true);
            } 
            else if(isNumber()) waring("variável tipo string não aceita número");
            nextToken();

        }else{ // var é numeric
            if(isString()){
                waring("variável numérica não aceita string");
                nextToken();
            }else{
                String value = ""+expr();
                if(is(TokenTypes.DELIMIT_SEMICOLON))
                    setVar(false, var, value, true);
            }
        }
    }

    


    public void Print(){
        nextToken();
        if(isString()){
            console("res = " + TEXT);
            nextToken();
        }
        else if(isVarOfString()){
            console("var "+TEXT+" = " + mv.get(TEXT));
            nextToken();
        }
        else console("res = " + expr()); //sem nextToken
        matchSemicolon();
    }


    public void input(){
        input(0);
        while(isVirg()) input(1);
        matchSemicolon();
    }
    public void input(int LoL){
        nextToken();
        if(!isDeclared(TEXT)) 
            erro("variável '"+TEXT+"' não foi declarada");
        matchId();
    }


    
    
    public int expr(){
        int s = product();
        while(isPlusOrMinus()){
            boolean op = matchPlusOrMinus();
            int p = product();
            if(op) s += p;
            else s -= p;
        }
        return s;
    }

    public int product(){
        int p = value();
        while(isDivOrTimes()){
            boolean op = matchDivOrTimes();
            int v = value();
            if(op) p /= v;
            else p *= v;
        } 
        return p;
    }
    
    public int value(){
        int v;
        if(isNumber()) v = getVal();
        else{
            abreParenteses();
            v = expr();
            fechaParenteses();
        }
        return v;
    }
    
    public int getVal(){
        String ret = TEXT;
        if(isID()){
            if(isVarNumProblem())
                erro("a variável '"+TEXT+"' não foi declarada, não foi inicializada ou é uma String");
            nextToken();
            return (int) Float.parseFloat(mv.get(ret));
        }
        matchNumber();
        return (int) Float.parseFloat(ret);
    }
}




