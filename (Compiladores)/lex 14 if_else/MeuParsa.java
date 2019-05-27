class MeuParsa extends Parser{

    java.util.HashMap <String, Var> symbolTable;

    MeuParsa(String arq){
        super(arq);
        symbolTable = new java.util.HashMap <String, Var>();
        start();
    }

    void start(){
        pilha = new Pilha();
        escopo = new Comando();
        raiz = escopo;
        pilha.push(escopo);

        bloco(); 

        if(isEnd()) {
            System.out.println("// $ANTLR nao eh magia. Antes de ler o livro que o guru lhe deu você tem que escrever o seu!");
            System.out.println(escopo.toJava(0));
            
            //System.out.println("/* Symboltable:");
            //for(Var c:escopo.symbolTable.values()) System.out.println(c.show());
            //System.out.println("*/");
        }
    }
    
    void bloco(){
        while(true){
            if(isEnd()) break;
            else if(isDeclareInt()) CMD_Declare(0);
            else if(isDeclareFloat()) CMD_Declare(1);
            else if(isDeclareBool()) CMD_Declare(2);
            else if(isDeclareString()) CMD_Declare(3);
            else if(isID()) CMD_Atrib();
            else if(ifMatchPrint()) CMD_Print();
            else if(ifMatchInput()) CMD_Input();
            else if(ifMatchWhileCMD()) CMD_While();
            else if(ifMatchIfCMD()) CMD_If();
            else noExpected();
        }
    }

    void CMD_Declare(int tipo){
        matchDeclaration();
        String tmp = id;
        addvar(tipo, id);
        matchId();
        while(ifMatchComma()){
            tmp += ", "+id;
            addvar(tipo, id);
            matchId();
        }
        matchSemicolon();
        cmd = new Declare(tipo, tmp);
        escopo.push(cmd);
    }

    void CMD_Atrib(){
        String tmp = id;
        matchId();
        matchAssign();
        Var a = expr();
        setVar(tmp, a) ;
        cmd = new Atrib(tmp, a);
        matchSemicolon();
        escopo.push(cmd);
    }
    
    void CMD_Print(){
        Var a = expr();
        cmd = new Print(a);
        matchSemicolon();
        escopo.push(cmd);
    }
    
    void CMD_Input(){
        do {
            cmd = new Input(id, checkVarTipo(id));
            escopo.push(cmd);
            matchId();
        } while(ifMatchComma());
        matchSemicolon();
        raiz.setScan();
    }


    void CMD_While(){
        Var a = expr();
        escopo = new While(a);
        pilha.push(escopo);

            bloco();

        cmd = pilha.pop();
        escopo = pilha.getTopo();
        escopo.push(cmd);
        matchLoop();
    };

    void CMD_If(){
        Var a = expr();
        escopo = new If(a);
        pilha.push(escopo);
        bloco();
        if(ifMatchElse()){
            ((If)escopo).changeElseMode();
            bloco();
        }
        cmd = pilha.pop();
        escopo = pilha.getTopo();
        escopo.push(cmd);
        matchEndIf();
    };

  /***********************************************
   ***********************************************/

    int checkVarTipo(String tmp){
        if(!symbolTable.containsKey(tmp)){ 
            erros.put(new Erro(404,1,"a variável '"+tmp+"' precisa ser declarada previamente",LIN,COL));
            //erro ("a variável '"+tmp+"' precisa ser declarada previamente");
            return 666;
        }
        else return symbolTable.get(tmp).tipo;
    }

    void addvar(int tipo, String id){
        if(!symbolTable.containsKey(id))
            symbolTable.put(id, new Var(tipo, id));
        else
            erros.put(new Erro(10,0,"variável "+id+" já consta",LIN,COL));
            //waring("variavel "+id+" já consta");
    }
    
    void setVar(String tmp, Var a){
        if(!symbolTable.containsKey(tmp))
            erros.put(new Erro(404,1,"variável '"+tmp+"' não declarada",LIN,COL));
            //erro("variavel '"+tmp+"' não declarada");

        else{
            Var b = symbolTable.get(tmp);
            if(a.tipo != b.tipo)
                erros.put(new Erro(10,0,"tipo incompatível",LIN,COL));
                //waring("tipo incompatível");
            b.tipo = a.tipo;
            b.exp = a.exp;
            b.str = a.str;
            b.inic = true;
            symbolTable.put(tmp, b);
        }
    }

  /***********************************************
   ***********************************************/

    Var expr(){
        Var a = exp();
        String op;
        while(isOpRel()){
            op = id;
            nextToken();
            a = Opera(a, op, exp(), 1);
        }
        return a;
    }


    Var exp(){
        Var a = prod();
        String op;
        while(isPlusOrMinus()){
            op = id;
            nextToken();
            a = Opera(a, op, prod(), 0);
        }
        return a;
    }


    Var prod(){
        Var a = val();
        String op;
        while(isDivOrTimes()){
            op = id;
            nextToken();
            a = Opera(a, op, val(), 0);
        }
        return a;
    }

    
    Var val(){
        Var a = new Var(3, "@expr");
        if(isID()||isINT()||isDOUBLE()||isSTRING()){
            a.str = id;
            a.exp = id;
            a.id = id;
            if(isINT()) a.tipo = 0;
            if(isDOUBLE()) a.tipo = 1;
            if(isSTRING()) {a.tipo = 3; a.str = noQuotes(a.str);}
            if(isID()){
                if(!symbolTable.containsKey(id)){
                    erros.put(new Erro(10,0,"variável '"+id+"' non ecziste!",LIN,COL));
                    //waring("variavel '"+id+"' non ecziste!");
                }else{
                    a = symbolTable.get(id);
                    if(!a.inic) 
                        erros.put(new Erro(10,0,"variável '"+id+"' foi declarada mas não foi atribuída",LIN,COL));
                        //waring("variável '"+id+"' foi declarada mas não foi atribuída" );
                }
                a.exp = id;
            }
            nextToken();
        }else{
            a.exp = id;
            abreParenteses();
            Var b = expr();
            a.tipo = b.tipo;
            a.str = b.str;
            a.id = "("+b.exp+")";
            a.exp += b.exp;
            a.exp += id;
            fechaParenteses();
        }        
        return a;
    }

  /***********************************************
   ***********************************************/
    
    Var Opera(Var a, String op, Var b, int pog){
            //console("chegou a.str: "+a.str + " b.str: "+b.str);
        int tipo = 0;
        int x1 = 0;
        int y1 = 0;
        double x2 = 0;
        double y2 = 0;
        String x3 = a.str;
        String y3 = b.str;
        String res = "nulo";
        boolean x4 = false;
        
        Var r = new Var(0, "@opera");
        r.exp = a.id +" " + op + " " + b.id;  // só concatena toksns da expresão
        r.id = r.exp;
        
        // Agora, tentando avaliar a expressão
        // tem que tratar os tipos.
        // são tantos casos...
        if(a.tipo==3 || b.tipo==3)
            if(op=="*"||op=="/"||op=="-") 
                erros.put(new Erro(10,0,"Operação inválida",LIN,COL));
                //waring("Operação inválida");
        
        // que acontece se tentar multiplicar strings?
        if(a.tipo==1 || b.tipo == 1) tipo = 1;
        if(a.tipo==3 || b.tipo == 3) tipo = 3;
        if(a.tipo==2 && b.tipo != 2) erros.put(new Erro(10,0,"Operação ilegal",LIN,COL));
            //waring("Operação ilegal");
        if(a.tipo!=2 && b.tipo == 2) erros.put(new Erro(10,0,"Operação ilegal",LIN,COL));
            //waring("Operação ilegal");
        if(pog == 1) tipo = 2;

        // parseInt() e parseFloat() 
        // não aceitam qualquer parametro
        try{
            if(tipo==1){
                x2 = Double.parseDouble(a.str);
                y2 = Double.parseDouble(b.str);
            }
            if(tipo==0){
                x1 = Integer.parseInt(a.str); 
                y1 = Integer.parseInt(b.str);
            }

        }catch(Exception e){
            erros.put(new Erro(707,1,"Problema ao realizar a operação entre '"+a.str+"' e '"+b.str+"'",LIN,COL));
            //console("ERRO a.str: "+a.str + " b.str: "+b.str);
        }


        //  "+"  | "-"  | "*"  | "/"
        if(op.equals("+")){ x1 += y1; x2 += y2; x3 += y3;}
        if(op.equals("-")){ x1 -= y1; x2 -= y2;}
        if(op.equals("*")){ x1 *= y1; x2 *= y2;}
        if(op.equals("/")){ x1 /= y1; x2 /= y2;}
        
        //  "=="  | "!="  | ">="  | "<="  | "<"   | ">" 
        if(op.equals("==") && x3.equals(y3)) x4 = true;
        if(op.equals("!=") && !x3.equals(y3)) x4 = true;
        if(op.equals(">") && (x1>y1 || x2>y2 || x3.compareTo(y3)>0)) x4 = true;
        if(op.equals("<") && (x1<y1 || x2<y2 || x3.compareTo(y3)<0)) x4 = true;
        if(op.equals(">=") && (x1>=y1 || x2>=y2 || x3.compareTo(y3)>=0)) x4 = true;
        if(op.equals("<=") && (x1<=y1 || x2<=y2 || x3.compareTo(y3)<=0)) x4 = true;

        if(tipo == 0) res = "" + x1;
        if(tipo == 1) res = "" + x2;
        if(tipo == 2) res = "" + x4;
        if(tipo == 3) res = x3;
        
        r.str = res;
        r.tipo = tipo;
        return r;
    }
 }
