class Parser {               // essencial
    public java.util.HashMap <String, String> mv;
    public java.util.HashMap <String, Boolean> ma;
    public java.util.HashMap <String, Boolean> ms;
    public TokenTypes CODE;
    public MeuLek ml;
    public String TEXT;
    public int LIN, COL;

    Parser(String arq){
        mv = new java.util.HashMap <String, String>();
        ma = new java.util.HashMap <String, Boolean>();
        ms = new java.util.HashMap <String, Boolean>();
        ml = new MeuLek(arq);
        nextToken();
    }

    public void matchId(){match(TokenTypes.T_ID);}
    public void matchSemicolon(){match(TokenTypes.DELIMIT_SEMICOLON);System.err.println();}
    public void matchAssign(){match(TokenTypes.OP_ASSIGN);}
    public void abreParenteses(){match(TokenTypes.DELIMIT_LPAR);}
    public void fechaParenteses(){match(TokenTypes.DELIMIT_RPAR);}

    public boolean matchNumber(){return confirm(TokenTypes.NUMBER, TokenTypes.NUMBER2);}
    public boolean matchDivOrTimes(){return confirm(TokenTypes.OP_DIV, TokenTypes.OP_TIMES);}
    public boolean matchPlusOrMinus(){return confirm(TokenTypes.OP_PLUS, TokenTypes.OP_MINUS);}

    public boolean isInicialized(String var){return ma.get(var);}
    public boolean isVarAString(String var){return ms.get(var);}    
    public boolean isDeclared(String var){return ma.containsKey(var);}

    public boolean isVarOfString(){return isID()&&!isVarStringProblem();}
    public boolean isString(){return is(TokenTypes.T_STRING, TokenTypes.T_CHAR);}
    public boolean isVarNumProblem(){return !isDeclared(TEXT) || !isInicialized(TEXT) || isVarAString(TEXT);}
    public boolean isVarStringProblem(){return !isDeclared(TEXT) || !isInicialized(TEXT) || !isVarAString(TEXT);}
    public boolean isVirg(){return is(TokenTypes.DELIMIT_COMMA);}
    public boolean isNumber(){return is(TokenTypes.NUMBER, TokenTypes.NUMBER2, TokenTypes.T_ID);}
    public boolean isDivOrTimes(){return is(TokenTypes.OP_DIV, TokenTypes.OP_TIMES);}
    public boolean isPlusOrMinus(){return is(TokenTypes.OP_PLUS, TokenTypes.OP_MINUS);}
    public boolean isID(){return is(TokenTypes.T_ID);}
    public boolean isCommandPrint(){return is(TokenTypes.LITERAL_PRINT);}
    public boolean isCommandInput(){return is(TokenTypes.LITERAL_INPUT);}
    public boolean isDeclareFloat(){return is(TokenTypes.LITERAL_FLOAT);}
    public boolean isDeclareString(){return is(TokenTypes.LITERAL_STRING);}
    public boolean isDeclareInt(){return is(TokenTypes.LITERAL_INT);}
    public boolean is(TokenTypes code1, TokenTypes code2, TokenTypes code3){return is(code1,code2) || is(code3);}
    public boolean is(TokenTypes code1, TokenTypes code2){return is(code1) || is(code2);}
    public boolean is(TokenTypes code){return code == CODE;}
    public boolean isEOF(){return is(TokenTypes.EOF);}

    public void noExpected(){
        if(is(TokenTypes.TOKEN_INVALIDO)) {noMatch("token inválido");}
        else if(is(TokenTypes.T_STRING)) {noMatch("string");}
        else if(is(TokenTypes.T_CHAR)) {noMatch("char");}
        else if(is(TokenTypes.NUMBER2)) {noMatch("número");}
        else if(is(TokenTypes.NUMBER)) {noMatch("número");}
        else if(is(TokenTypes.DELIMIT_SEMICOLON)) {noMatch("ponto e virgula");}
        else {nextToken(); erro("sei lá o que pode ser em " + LIN +", " + COL);}
    }

   /***********************************************
   ************************************************/
    public void noMatch(String str){
        waring("não esperava " +str+" neste momento.");
        nextToken();
    }
        
    public void noMatch(){
        waring(CODE + " não era esperado neste momento.");
        nextToken();
    }
        
    public void confirm(TokenTypes code){
        if(is(code)) match(code);
    }

    public boolean confirm(TokenTypes code1, TokenTypes code2){
        boolean ret = is(code1);
        if(is(code1)^is(code2)){
            confirm(code1);
            confirm(code2);
        }else{
            print(" esperava ou "+code1+" ou "+code2);
            nextToken();
        }
        return ret;
    }
    
   /***********************************************
   ************************************************/
    public void match(TokenTypes code){
        if(is(code)) nextToken();
        else{
            print(" esperava "+code+" mas veio "+CODE);
            System.exit(256+24);
        }
    }

    public boolean nextToken(){
        ml.getToken();
        CODE = ml.token.code;
        TEXT = ml.token.str;
        LIN = ml.token.lin;
        COL = ml.token.col;
        TokensFile();
        return ml.token.code != TokenTypes.EOF;
    }

   /***********************************************
   ************************************************/

    public void erro(String str){print("### ERRO: " + str);System.exit(256+24);}
    public void waring(String str){print("### WARING: " + str);}
    public void console(String str){print("\tCONSOLE: " + str);}
    public void print(String str){System.out.println(LIN+","+COL+":\t"+str);}
    public void TokensFile(){System.err.format("%3d,%3d  ::%-20s %s\n",LIN,COL,CODE,TEXT);}
}




