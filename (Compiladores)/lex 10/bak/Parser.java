enum Tipo{
    STRING, INT, BOOL
}
class Var{
    String str, id;
    boolean inic;
    Tipo tipo;
    Var(Tipo tipo, String id){
        this.id = id;
        this.tipo = tipo;
        this.inic = false;
        this.str = "";
    }
    public String print(){
        return String.format("VAR: %s tipo "+tipo, id);
    }
}

class Parser {               // essencial
    public java.util.HashMap <String, Var> symbolTable;
    public TokenTypes CODE, code;
    public MeuLek ml;
    public String STR, str;
    public int escopo, LIN, COL;
    public Tipo tipo;
    public boolean pog1;

    Parser(String arq){
        symbolTable = new java.util.HashMap <String, Var>();
        ml = new MeuLek(arq);
        pog1 = false;
        escopo = 0;
        nextToken();
    }
    
   /***********************************************
   ************************************************/

    void nextToken(){
        ml.getToken();
        CODE = ml.token.code;
        STR = ml.token.str;
        LIN = ml.token.lin;
        COL = ml.token.col;
        TokensFile();
    }

    boolean is(TokenTypes code){
        return code == CODE;
    }

    boolean is(TokenTypes code1, TokenTypes code2){
        return is(code1) || is(code2);
    }

    boolean is(TokenTypes code1, TokenTypes code2, TokenTypes code3){
        return is(code1, code2) || is(code3);
    }

    void match(TokenTypes code){
        if(is(code)) nextToken();
        else erro (" esperava "+code+" mas veio "+CODE);
    }

    void confirm(TokenTypes code1, TokenTypes code2){
        if(is(code1)) match(code1);
        else if(is(code2)) match(code2);
    }

    void confirm(TokenTypes code){
        if(is(code)) match(code);
    }

    void match(TokenTypes code1, TokenTypes code2){
        if(is(code1)) match(code1);
        else if(is(code2)) match(code2);
        else erro (" esperava "+code1+" ou "+ code2 +" mas veio "+CODE);
    }

    void match(TokenTypes code1, TokenTypes code2, TokenTypes code3){
        if(is(code1)) match(code1);
        else if(is(code2)) match(code2);
        else if(is(code3)) match(code3);
        else erro (" esperava "+code1+" ou "+ code2 +" ou "+ code3 +" mas veio "+CODE);
    }

    void ignore(String str){
        waring("não esperava " +str+" neste momento.");
        nextToken();
    }

    void ignore(TokenTypes code){
        waring(code + "não era esperado neste momento.");
        nextToken();
    }

    void ignore(){
        nextToken();
    }

    boolean ifMatch(TokenTypes code1, TokenTypes code2, TokenTypes code3){
        boolean ret = is(code1) || is(code2) || is(code3);
        if(ret) nextToken();
        return ret;
    }

    boolean ifMatch(TokenTypes code){
        boolean ret = is(code);
        if(ret) nextToken();
        return ret;
    }

   /***********************************************
   ************************************************/
   
   void checkSymbol(){if(symbolTable.containsKey(STR)) erro("dupla declaração");}
   void checkSymbolExist(){if(!symbolTable.containsKey(STR)) erro("A variável '"+STR+"' não ecziste!");}
   
   void DECLAREVAR(){
       checkSymbol();
       Var v = new Var(tipo, STR);
       symbolTable.put(STR, v);
   }
   
   void SETVAR(String nome){
       Var v = symbolTable.get(nome);
       v.str = STR;
       v.inic = true;
   }


   Tipo GETVARTIPO(){
       checkSymbolExist();
       Var v = symbolTable.get(STR);
       return v.tipo;
   }
   
   Var GETVAR(String nome){
       if(!symbolTable.containsKey(nome)) erro("A variável "+nome+" não ecziste!");
       Var v = symbolTable.get(nome);
       return v;
   }


   /***********************************************
   ************************************************/
   
   int toInt(String str){
       return Math.round(Float.parseFloat(str));
   }
   
   // eu sei, eu sei... uma das minhas vergonhas nesse código.
   // se alguém do grupo se interessar em dar suporte a Float ou Double
   // fiquem à vontade. Não vou mexer com isso pra essa disciplina
   // (talvez noutro momento)

    
   /***********************************************
   ************************************************/

    
    boolean ifMatchComma(){return ifMatch(TokenTypes.DELIMIT_COMMA);}
    boolean ifMatchId(){return ifMatch(TokenTypes.T_ID);}
    boolean ifMatchPrint(){return ifMatch(TokenTypes.LITERAL_PRINT);}
    boolean ifMatchInput(){return ifMatch(TokenTypes.LITERAL_INPUT);}
    boolean ifMatchIfCMD(){return ifMatch(TokenTypes.LITERAL_IfCMD);}

    boolean isDeclaration(){return is(TokenTypes.LITERAL_INT, TokenTypes.LITERAL_STRING, TokenTypes.LITERAL_BOOL);}
    boolean isEndOfProg(){return is(TokenTypes.EOF,TokenTypes.LITERAL_ENDIF,TokenTypes.LITERAL_NEXT);}

    boolean isID(){return is(TokenTypes.T_ID);}
    boolean isNumber(){return is(TokenTypes.NUMBER, TokenTypes.NUMBER2, TokenTypes.T_ID);}
    boolean isString(){return is(TokenTypes.T_STRING, TokenTypes.T_CHAR);}
    boolean isBool(){return is(TokenTypes.LITERAL_true, TokenTypes.LITERAL_false);}

    boolean isDivOrTimes(){return is(TokenTypes.OP_DIV, TokenTypes.OP_TIMES);}
    boolean isPlusOrMinus(){return is(TokenTypes.OP_PLUS, TokenTypes.OP_MINUS);}
    boolean isOpRel(){
        return 
            is(TokenTypes.REL_AND, TokenTypes.REL_OR, TokenTypes.REL_NE) ||
            is(TokenTypes.REL_GE, TokenTypes.REL_LT, TokenTypes.REL_GT) ||
            is(TokenTypes.REL_EQT, TokenTypes.REL_LE);
    }

    String noQuotes(String str){return str.substring(1,STR.length()-1);}
    
    void abreParenteses(){match(TokenTypes.DELIMIT_LPAR);}
    void fechaParenteses(){match(TokenTypes.DELIMIT_RPAR);}

    // TODO: isso aqui vai ter que diferenciar TODOS operadores (não só *, +, && e || como agora)
    void matchDivOrTimes(){confirm(TokenTypes.OP_DIV, TokenTypes.OP_TIMES);}
    void matchPlusOrMinus(){confirm(TokenTypes.OP_PLUS, TokenTypes.OP_MINUS);}
    void matchOpRel(){
        if( is(TokenTypes.REL_AND, TokenTypes.REL_OR, TokenTypes.REL_NE) ||
            is(TokenTypes.REL_GE, TokenTypes.REL_LT, TokenTypes.REL_GT) ||
            is(TokenTypes.REL_EQT, TokenTypes.REL_LE)
        )
        nextToken();
        else erro("esperava um operador relacional, mas veio um "+CODE);
    }

    void matchDeclaration(){match(TokenTypes.LITERAL_INT, TokenTypes.LITERAL_STRING, TokenTypes.LITERAL_BOOL);}
    void matchAssign(){match(TokenTypes.OP_ASSIGN);}
    void matchId(){match(TokenTypes.T_ID);}
    void matchSemicolon(){match(TokenTypes.DELIMIT_SEMICOLON);System.err.println();}

   /***********************************************
   ************************************************/

    void noExpected(){
        if(is(TokenTypes.TOKEN_INVALIDO)) {ignore("token inválido");}
        else if(is(TokenTypes.T_STRING)) {ignore("string");}
        else if(is(TokenTypes.T_CHAR)) {ignore("char");}
        else if(is(TokenTypes.NUMBER2)) {ignore("número");}
        else if(is(TokenTypes.NUMBER)) {ignore("número");}
        else if(is(TokenTypes.DELIMIT_SEMICOLON)) {ignore("ponto e virgula");}
        else {nextToken(); erro("sei lá o que pode ser em " + LIN +", " + COL);}
    }

   /***********************************************
   ************************************************/

    void erro(String str){print("### ERRO: " + str); System.exit(256+24);}
    void waring(String str){print("### WARING: " + str);}
    void console(String str){print("\tCONSOLE: " + str);}
    void print(String str){System.out.println(LIN+","+COL+":\t"+str);}
    void TokensFile(){System.err.format("%3d,%3d  ::%-20s %s\n",LIN,COL,CODE,STR);}
}



