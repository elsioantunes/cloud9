 class MeuParsa extends Parser{
    MeuParsa(String arq){super(arq);start();}
    
    void start(){
        pilha = new Pilha();
        escopo = new Comando();
        //raiz = escopo;
        pilha.push(escopo);

        bloco(); 

        if(isEnd()) {
            System.out.println("// $ANTLR nao eh magia. Antes de ler o livro que o guru lhe deu você tem que escrever o seu!");
            System.out.println(escopo.toJava(0));
            System.out.println("/* Symboltable:");
            for(Var c:escopo.symbolTable.values()) System.out.println(c.show());
            System.out.println("*/");
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
            //else if(isIfcmd()) CMD_If();
            else noExpected();
        }
    }
    
    void CMD_While(){
        Var a = expr();
        raiz = escopo;
        escopo = new While(raiz, a, LIN);
        pilha.push(escopo);

            bloco();

        cmd = pilha.pop();
        escopo = pilha.getTopo();
        escopo.push(cmd);
        matchLoop();
    };
    

    void CMD_Declare(int tipo){
        matchDeclaration();
        do {
            escopo.addvar(tipo, id, LIN);
            matchId();
        } while(ifMatchComma());
        matchSemicolon();
    }

    void CMD_Input(){
        do {
            cmd = new Input(escopo, id, LIN);
            escopo.push(cmd);
            matchId();
        } while(ifMatchComma());
        matchSemicolon();
    }

    
    void CMD_Atrib(){
        String a = id;
        matchId();
        matchAssign();
        Var b = expr();
        cmd = new Atrib(escopo, a, b, LIN);
        matchSemicolon();
        escopo.push(cmd);
    }

    void CMD_Print(){
        Var a = expr();
        cmd = new Print(a, LIN);
        matchSemicolon();
        escopo.push(cmd);
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
                if(!escopo.symbolTable.containsKey(id)){
                    waring("variavel '"+id+"' non ecziste!");
                }else{
                    a = escopo.symbolTable.get(id);
                    if(!a.inic) waring("variável '"+id+"' foi declarada mas não foi atribuída" );
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
                waring("Operação inválida");
        
        // que acontece se tentar multiplicar strings?
        if(a.tipo==1 || b.tipo == 1) tipo = 1;
        if(a.tipo==3 || b.tipo == 3) tipo = 3;
        if(a.tipo==2 && b.tipo != 2) waring("Operação ilegal");
        if(a.tipo!=2 && b.tipo == 2) waring("Operação ilegal");
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
            console("ERRO a.str: "+a.str + " b.str: "+b.str);
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




