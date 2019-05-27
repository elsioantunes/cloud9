class Parser {
    public MeuLek ml;
    public int LIN, COL;
    public TokenTypes CODE;
    public String val, VAL, EXP, id;
    public Comando cmd, escopo, raiz;
    public Pilha pilha;
    public SymbolTable symboltable;

    Parser(String arq){
        ml = new MeuLek(arq);
        symboltable = new SymbolTable();
        nextToken();
    }
    
   /***********************************************
   ************************************************/

    String noQuotes(String str){return str.substring(1, str.length()-1);}
    
   /***********************************************
   ************************************************/
    boolean ifMatchInput(){return ifMatch(TokenTypes.LITERAL_INPUT);}
    boolean ifMatchStep(){return ifMatch(TokenTypes.LITERAL_STEP);}
    boolean ifMatchPrint(){return ifMatch(TokenTypes.LITERAL_PRINT);}
    boolean ifMatchComma(){return ifMatch(TokenTypes.DELIMIT_COMMA);}
    boolean ifMatchElse(){return ifMatch(TokenTypes.LITERAL_ELSE);}
    boolean ifMatchId(){return ifMatch(TokenTypes.T_ID);}
    boolean ifMatchWhileCMD(){return ifMatch(TokenTypes.LITERAL_WHILE);}
    boolean ifMatchIfCMD(){return ifMatch(TokenTypes.LITERAL_IF);}
    boolean ifMatchForCMD(){return ifMatch(TokenTypes.LITERAL_FOR);}
    boolean ifMatch(TokenTypes code){
        boolean ret = is(code);
        if(ret) nextToken();
        return ret;
    }
    boolean isDivOrTimes(){return is(TokenTypes.OP_DIV, TokenTypes.OP_TIMES);}
    boolean isPlusOrMinus(){return is(TokenTypes.OP_PLUS, TokenTypes.OP_MINUS);}
    boolean isDeclareInt(){return is(TokenTypes.LITERAL_INT);}
    boolean isDeclareFloat(){return is(TokenTypes.LITERAL_DOUBLE);}
    boolean isDeclareBool(){return is(TokenTypes.LITERAL_BOOL);}
    boolean isDeclareString(){return is(TokenTypes.LITERAL_STRING);}
    boolean isEnd(){return is(TokenTypes.EOF,TokenTypes.LITERAL_ENDIF) || is(TokenTypes.LITERAL_ELSE,TokenTypes.LITERAL_LOOP,TokenTypes.LITERAL_NEXT);}
    boolean isID(){return is(TokenTypes.T_ID);}
    boolean isINT(){return is(TokenTypes.NUMBER);}
    boolean isDOUBLE(){return is(TokenTypes.NUMBER2);}
    boolean isBOOL(){return is(TokenTypes.LITERAL_true, TokenTypes.LITERAL_false);}
    boolean isSTRING(){return is(TokenTypes.T_STRING, TokenTypes.T_CHAR);}
    boolean isOpLogic(){return is(TokenTypes.REL_AND, TokenTypes.REL_OR);}
    boolean isOpRel(){
        return 
            is(TokenTypes.REL_AND, TokenTypes.REL_OR, TokenTypes.REL_NE) ||
            is(TokenTypes.REL_GE, TokenTypes.REL_LT, TokenTypes.REL_GT) ||
            is(TokenTypes.REL_EQT, TokenTypes.REL_LE);
    }
    int plusOrMinus(){if(is(TokenTypes.OP_PLUS)){match(); return 0;}match(); return 1;}
    int divOrTimes(){if(is(TokenTypes.OP_TIMES)){match(); return 2;}match(); return 3;}
    int opRel(){
        if(is(TokenTypes.REL_NE)) {match(); return 4;}
        else if(is(TokenTypes.REL_GE)) {match(); return 5;}
        else if(is(TokenTypes.REL_LT)) {match(); return 6;}
        else if(is(TokenTypes.REL_GT)) {match(); return 7;}
        else if(is(TokenTypes.REL_EQT)) {match(); return 8;}
        else {match(); return 9;} // is TokenTypes.REL_LE
    }
    void abreParenteses(){match(TokenTypes.DELIMIT_LPAR);}
    void fechaParenteses(){match(TokenTypes.DELIMIT_RPAR);}
    void matchAssign(){match(TokenTypes.OP_ASSIGN);}
    void matchTo(){match(TokenTypes.LITERAL_TO);}
    void matchId(){match(TokenTypes.T_ID);}
    void matchDeclaration(){nextToken();}
    void matchSemicolon(){match(TokenTypes.DELIMIT_SEMICOLON);}
    void matchLoop(){match(TokenTypes.LITERAL_LOOP);}
    void matchNext(){match(TokenTypes.LITERAL_NEXT);}
    void matchEndIf(){match(TokenTypes.LITERAL_ENDIF);}

   /***********************************************
   ************************************************/
    void noExpected(){
        if(is(TokenTypes.TOKEN_INVALIDO)) {ignore("token inválido");}
        else if(is(TokenTypes.T_STRING)) {ignore("string");}
        else if(is(TokenTypes.T_CHAR)) {ignore("char");}
        else if(is(TokenTypes.NUMBER2)) {ignore("número");}
        else if(is(TokenTypes.NUMBER)) {ignore("número");}
        else if(is(TokenTypes.DELIMIT_SEMICOLON)) {ignore("ponto e virgula");}
        else {nextToken(); erro(" sei lá o que pode ser "+CODE+" neste contexto.");}
    }
    void ignore(String str){
        waring("não esperava " +str+" neste momento.");
        nextToken();
    }

   /***********************************************
   ************************************************/

    void match(){nextToken();}
    void match(TokenTypes code){
        if(is(code)) nextToken();
        else erro (" esperava "+code+" mas veio "+CODE);
    }
    boolean is(TokenTypes code){return code == CODE;}
    boolean is(TokenTypes code1, TokenTypes code2){return is(code1) || is(code2);}
    boolean is(TokenTypes code1, TokenTypes code2, TokenTypes code3){return is(code1) || is(code2) || is(code3);}
    void nextToken(){
        ml.getToken();
        LIN = ml.token.lin;
        COL = ml.token.col;
        VAL = ml.token.str;
        id = ml.token.str;
        CODE = ml.token.code;
        //print(""+CODE);
    }

   /***********************************************
   ************************************************/
    void erro(String str){print("### ERRO: " + str + "\n\nConsulte TokensFile.txt para relatório de captura"); System.exit(256+24);}
    void waring(String str){print("### WARING: " + str);}
    void console(String str){print("\tCONSOLE: " + str);}
    void print(String str){System.err.println(LIN+","+COL+":\t"+str+"\n");}
}





