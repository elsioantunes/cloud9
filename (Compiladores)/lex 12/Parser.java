enum Tipo{
    INT, FLOAT, STRING, BOOL
}

class Pilha{
    Programa[] buf;
    int topo;
    Pilha(){
        topo = 0;
        buf = new Programa[12];
    }
    void push(Programa Cmd){
        buf[topo++] = Cmd;
    }
    boolean vazia(){
        return topo == 0;
    }
    Programa pop(){
        return buf[--topo];
    }
    Programa getTopo(){
        return buf[topo-1];
    }
}

class ExpBuf{
    String[] buf;
    int i;
    ExpBuf(){
        i = 0;
        buf = new String[300];
    }
    void push(String str){
        buf[i++] = str;
    }
    String show(){
        String s = "";
        for(int j=0;j<i;j++)
            s+=(j>0?" ":"")+buf[j];
        return s;
    }
}

class Var{
    String str, id;
    boolean inic;
    Tipo tipo;
    Var(Tipo tipo, String id){
        this.id = id;
        this.tipo = tipo;
        this.inic = false;
        this.str = "0";
    }
    String show(){
        return String.format("VAR: %s,\t tipo: "+tipo+",\t valor:%s", id, str);
    }
}


class Parser {               // essencial
    public java.util.HashMap <String, Var> symbolTable;
    public TokenTypes CODE, code;
    public MeuLek ml;
    public String STR, str, exp;
    public int escopo, LIN, COL;
    public Tipo tipo;
    public boolean debug, logExpFlag;
    public ExpBuf buf;
    public Programa prog, topo, cmd;
    public Pilha p;

    Parser(String arq){
        p = new Pilha();
        prog = new Programa();
        symbolTable = new java.util.HashMap <String, Var>();
        ml = new MeuLek(arq);
        escopo = 0;
        debug = false;
        logExpFlag = false;
        nextToken();
    }
    
   /***********************************************
   ************************************************/

    void nextToken(){
        if(logExpFlag) buf.push(STR);
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

    void match(){
        nextToken();
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

    void match(TokenTypes code1, TokenTypes code2, TokenTypes code3, TokenTypes code4){
        if(is(code1)) match(code1);
        else if(is(code2)) match(code2);
        else if(is(code3)) match(code3);
        else if(is(code4)) match(code4);
        else erro (" esperava "+code1+" ou "+ code2 +" ou "+ code3 +" ou "+ code4 +" mas veio "+CODE);
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
    
    void MONTAwhile(String exp, int wu){p.push(new CmdWhile(exp, wu));};
    void MONTAif(String exp){p.push(new CmdIf(exp));};
    void MONTAelse(){p.push(new CmdElse());};

    void pushCmd(){
        if(p.vazia()) prog.push(cmd);
        else p.getTopo().push(cmd);
    }

    void ANINHA(){
        cmd = p.pop();
        pushCmd();    
    }
   
    void MONTAdecl(Tipo tipo, String exp){
        cmd = new CmdDecl(tipo, exp);
        pushCmd();    
   };
   
    void MONTAatrib(String var, String exp){
        cmd = new CmdAtrib(var, exp);
        pushCmd();    
    };
    
    void MONTAinput(Tipo tip, String var){
        cmd = new CmdInput(tip, var);
        pushCmd();    
    };
   
    void MONTAprint(String exp, Var a){
        cmd = new CmdPrint(exp, a);
        pushCmd();    
    };
   
   

   /***********************************************
   ************************************************/
   
   void checkSymbol(String id){if(symbolTable.containsKey(id)) erro("dupla declaração");}
   void checkSymbolExist(String id){if(!symbolTable.containsKey(id)) erro("A variável '"+id+"' não ecziste!");}
   
   void DECLAREVAR(String id){
       checkSymbol(id);
       Var v = new Var(tipo, id);
       symbolTable.put(id, v);
   }
   
   Var CREATEVAR(String id, Tipo tipo, String str){
       Var d = new Var(tipo, id);
       d.str = str;
       symbolTable.put("OperaRes", d);
       return d;
   }
   
   void SETVAR(Var a, Var b){
       if(debug) console("setvar a: " +a.id+", "+a.str+", "+a.tipo);
       if(debug) console("setvar b: " +b.id+", "+b.str+", "+b.tipo);

       if(a.tipo!=b.tipo) erro("tipo incompativel");
       Var v = symbolTable.get(a.id);
       v.str = b.str;
       v.inic = true;
   }

   Var GETVAR(String id){
       checkSymbolExist(id);
       return symbolTable.get(id);
   }
   
   /***********************************************
   ************************************************/
   
    void logExpOn(){
        if(!logExpFlag){
            buf = new ExpBuf();
            logExpFlag = true;
        }
    }
    
    void logExpOff(){
        logExpFlag = false;
        exp = buf.show();
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
    boolean ifMatchStep(){return ifMatch(TokenTypes.LITERAL_STEP);}
    boolean ifMatchPrint(){return ifMatch(TokenTypes.LITERAL_PRINT);}
    boolean ifMatchInput(){return ifMatch(TokenTypes.LITERAL_INPUT);}
    boolean ifMatchUntilCMD(){return ifMatch(TokenTypes.LITERAL_UNTIL);}
    boolean ifMatchWhileCMD(){return ifMatch(TokenTypes.LITERAL_WHILE);}
    boolean ifMatchIfCMD(){return ifMatch(TokenTypes.LITERAL_IF);}
    boolean ifMatchForcmd(){return ifMatch(TokenTypes.LITERAL_FOR);}
    boolean isDeclaration(){return is(TokenTypes.LITERAL_INT, TokenTypes.LITERAL_FLOAT) || is(TokenTypes.LITERAL_STRING, TokenTypes.LITERAL_BOOL);}
    boolean isEnd(){return is(TokenTypes.EOF,TokenTypes.LITERAL_ENDIF) || is(TokenTypes.LITERAL_NEXT,TokenTypes.LITERAL_ELSE,TokenTypes.LITERAL_LOOP);}
    boolean ifMatchElse(){return ifMatch(TokenTypes.LITERAL_ELSE);}
    boolean isID(){return is(TokenTypes.T_ID);}
    boolean isNumber(){return is(TokenTypes.NUMBER, TokenTypes.NUMBER2, TokenTypes.T_ID);}
    boolean isINT(){return is(TokenTypes.NUMBER);}
    boolean isFLOAT(){return is(TokenTypes.NUMBER2);}
    boolean isSTRING(){return is(TokenTypes.T_STRING, TokenTypes.T_CHAR);}
    boolean isBOOL(){return is(TokenTypes.LITERAL_true, TokenTypes.LITERAL_false);}
    boolean isLPAR(){return is(TokenTypes.DELIMIT_LPAR);}
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
    int plusOrMinus(){if(is(TokenTypes.OP_PLUS)){match(); return 0;}match(); return 1;}
    int divOrTimes(){if(is(TokenTypes.OP_TIMES)){match(); return 2;}match(); return 3;}
    int opRel(){
        if(is(TokenTypes.REL_NE)) {match(); return 4;}
        else if(is(TokenTypes.REL_GE)) {match(); return 5;}
        else if(is(TokenTypes.REL_LT)) {match(); return 6;}
        else if(is(TokenTypes.REL_GT)) {match(); return 7;}
        else if(is(TokenTypes.REL_EQT)) {match(); return 8;}
        else if(is(TokenTypes.REL_LE)) {match(); return 9;}
        else erro("esperava um operador relacional, mas veio um "+CODE);
        return 9;
    }
    void matchLoop(){match(TokenTypes.LITERAL_LOOP);}
    void matchEndIf(){match(TokenTypes.LITERAL_ENDIF);}
    void matchThen(){match(TokenTypes.LITERAL_THEN);}
    void matchDeclaration(){match(TokenTypes.LITERAL_INT, TokenTypes.LITERAL_FLOAT, TokenTypes.LITERAL_STRING, TokenTypes.LITERAL_BOOL);}
    void matchAssign(){match(TokenTypes.OP_ASSIGN);}
    void matchTo(){match(TokenTypes.LITERAL_TO);}
    void matchNext(){match(TokenTypes.LITERAL_NEXT);}
    void matchId(){match(TokenTypes.T_ID);}
    void matchSemicolon(){System.err.println(); match(TokenTypes.DELIMIT_SEMICOLON);}

   /***********************************************
   ************************************************/
    Var Opera(Var a, int op, Var b){
        //console("Opera a: " +a.id+", \t "+a.str+", \t"+a.tipo);
        //console("Opera b: " +b.id+", \t"+b.str+",\t "+b.tipo);
        //console("Opera op: " +op);
        int x1=0, y1=0;
        float x2=0, y2=0;
        String x3, y3;
        Tipo t = Tipo.INT;
        boolean x4;

        if(a.tipo == Tipo.STRING && op > 0 && op < 4) erro("operador inválido");
        if(a.tipo == Tipo.FLOAT || b.tipo == Tipo.FLOAT) t = Tipo.FLOAT;
        if(a.tipo == Tipo.STRING || b.tipo == Tipo.STRING) t = Tipo.STRING;

        if(t == Tipo.INT){
            x1 = Integer.parseInt(a.str);
            y1 = Integer.parseInt(b.str);
        }
        else if(t == Tipo.FLOAT){
            x2 = Float.parseFloat(a.str);
            y2 = Float.parseFloat(b.str);
        }

        x3 = a.str;
        y3 = b.str;
        x4 = false;

        switch(op){
            //  "+"  | "-"  | "*"  | "/"
            case 0: x1+=y1; x2+=y2; x3+=y3; break;
            case 1: x1-=y1; x2-=y2; break;
            case 2: x1*=y1; x2*=y2; break;
            case 3: x1/=y1; x2/=y2; break;
            
            //  "!="  | ">="  | "<="  | "<"   | ">" 
            case 4: if(x1!=y1 && x2!=y2 && !x3.equals(y3)) x4 = true; else x4 = false; break;
            case 5: if(x1>=y1 && x2>=y2) x4 = true; else x4 = false; break;
            case 6: if(x1<y1 && x2<y2) x4 = true; else x4 = false; break;
            case 7: if(x1>y1 && x2>y2) x4 = true; else x4 = false; break;
            case 8: if(x1==y1 && x2==y2 && x3.equals(y3)) x4 = true; else x4 = false; break;
            case 9: if(x1<=y1 && x2<=y2) x4 = true; else x4 = false; break;
        }
        
        if(op > 3){t = Tipo.BOOL; str = ""+x4;}
        if(t == Tipo.INT) str = ""+x1;
        if(t == Tipo.FLOAT) str = ""+x2;
        if(t == Tipo.STRING) str = x3;

        Var d = CREATEVAR("@tmp", t, str);
        
        //console("Opera res: " +d.id+", \t"+d.str+",\t "+d.tipo+",\t "+CODE);
        return d;
    }

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

    void erro(String str){print("### ERRO: " + str + "\n\nConsulte TokensFile.txt para relatório de captura"); System.exit(256+24);}
    void waring(String str){print("### WARING: " + str);}
    void console(String str){print("\tCONSOLE: " + str);}
    void print(String str){System.out.println(LIN+","+COL+":\t"+str);}
    void TokensFile(){System.err.format("%3d,%3d  ::%-20s %s\n",LIN,COL,CODE,STR);}
}



