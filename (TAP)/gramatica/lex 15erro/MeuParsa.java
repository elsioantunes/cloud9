    /* Gramática da linguagem
        <Start>             -> <Bloco>
        <Bloco>             -> (<CMD_Atrib>|<Print>|<Input>|<While>|<If>|<For>|<noExpected>)* <Eof>
        <CMD_Declare>       -> (<CMD_DeclareString>|<CMD_DeclareInt>|<CMD_DeclareBool><CMD_DeclareFloat>)*
        <CMD_DeclareString> -> "STRING" <ID> (<virg><ID>)* <semicolon>
        <CMD_DeclareInt>    -> "INT"    <ID> (<virg><ID>)* <semicolon>
        <CMD_DeclareBool>   -> "BOOL"   <ID> (<virg><ID>)* <semicolon>
        <CMD_DeclareFloat>  -> "DOUBLE"   <ID> (<virg><ID>)* <semicolon>
        <CMD_Atrib>         -> <ID> <ASSIGN> <ExpL> <SEMICOLON>
        <CMD_Print>         -> "PRINT" <ExpL> <SEMICOLON>
        <CMD_Input>         -> "INPUT"  <ID> (<VIRG><ID>)* <semicolon>
        <CMD_While>         -> "WHILE" <ExpL> <Bloco> "LOOP"
        <CMD_If>            -> "IF" <ExpL> <Bloco> ("ELSE" <Bloco>)? "ENDIF"
        <CMD_For>           -> "FOR" <ID> <ASSIGN> <ExpL> "TO" <ExpL> ("STEP" <ExpL>)? <Bloco> "NEXT"

        <ExpL>          ->  <ExpR>  ( "||"  | "&&" ) <ExpR> )?
        <ExpR>          ->  <Exp>  ( "!="  | ">="  | ">="  | "<"   | ">" ) <Exp> )?
        <Exp>           ->  <Prod> ( ( "+" | "-" ) <Prod> )*
        <Prod>          ->  <Val>  ( ( "*" | "/" ) <Val>  )*
        <Val>      ->  ( <ID> | <STRING> | <NUMBER>  | <BOOL> ) | "(" <ExpL> ")"
        
    */
    class MeuParsa extends Parser{

        MeuParsa(String arq){
            super(arq);
            start();
        }
    
        void start(){
            pilha = new Pilha();
            escopo = new Comando();
            raiz = escopo;
            pilha.push(escopo);
    
            bloco(); 
    
            if(isEnd()) {
                if(erros.size()>0 && erros.get(0).hasErrors(erros)) //Tem Erros
                {
                    String str1="class MeuProg{// code by robot\n";
                    str1 += "   public static void main(String args[]){\n";
            
                    for(Erro e:erros)
                    {
                        str1+=e.show();
                    }
                    str1+="}}";
                    System.out.println(str1);
                }
                else
                {
                    System.out.println("// $ANTLR é o %$&*#. Antes de ler o livro que o guru lhe deu você tem que escrever o seu!");
                    System.out.println(escopo.toJava(0));
                }
            }
        }
        
        void bloco(){
            symboltable.acquire();
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
                else if(ifMatchForCMD()) CMD_For();
                else noExpected();
            }
            symboltable.release();
        }
        
        void CMD_Print(){
            Var a = expl();
            cmd = new Print(a);
            matchSemicolon();
            escopo.push(cmd);
        }
        
        void CMD_Input(){
            do {
                cmd = new Input(id, symboltable.checkVarTipo(id,LIN,COL));
                escopo.push(cmd);
                matchId();
            } while(ifMatchComma());
            matchSemicolon();
            raiz.setScan();
        }
    
        void CMD_Atrib(){
            String tmp = id;
            matchId();
            matchAssign();
            Var a = expl();
            symboltable.setVar(tmp, a,LIN,COL) ;
            cmd = new Atrib(tmp, a);
            matchSemicolon();
            escopo.push(cmd);
        }
        
        void CMD_While(){
            Var a = expl();
            escopo = new While(a);
            pilha.push(escopo);
            bloco();
            cmd = pilha.pop();
            escopo = pilha.getTopo();
            escopo.push(cmd);
            matchLoop();
        };

        void CMD_Declare(int tipo){
            matchDeclaration();
            String tmp = id;
            symboltable.createVar(tipo, id);
            matchId();
            while(ifMatchComma()){
                tmp += ", "+id;
                symboltable.createVar(tipo, id);
                matchId();
            }
            matchSemicolon();
            cmd = new Declare(tipo, tmp);
            escopo.push(cmd);
        }
    
    
        void CMD_If(){
            Var a = expl();
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
    
        void CMD_For(){
            String tmp = id;
            matchId();
            matchAssign();
            Var a = expl();
            matchTo();
            Var b = expl();
            Var c = null;
            if(ifMatchStep())
                c = expl();
            symboltable.setVar(tmp, a, LIN, COL) ;
            escopo = new For(tmp, a, b, c);
            pilha.push(escopo);
                bloco();
            cmd = pilha.pop();
            escopo = pilha.getTopo();
            escopo.push(cmd);
            matchNext();
        };
    
    
      /***********************************************
       ***********************************************/
    
        Var expl(){
            Var a = expr();
            String op;
            while(isOpLogic()){
                op = id;
                nextToken();
                a = Opera(a, op, expr(), 1);
            }
            return a;
        }
    
    
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
            if(isID()||isINT()||isDOUBLE()||isSTRING()||isBOOL()){
                a.str = id;
                a.exp = id;
                a.id = id;
                if(isINT()) a.tipo = 0;
                if(isDOUBLE()) a.tipo = 1;
                if(isBOOL()) a.tipo = 2;
                if(isSTRING()) {a.tipo = 3; a.str = noQuotes(a.str);}
                if(isID()) a = symboltable.getVar(id,LIN,COL);
                nextToken();
            }else{
                a.exp = id;
                abreParenteses();
                Var b = expl();
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
            r.exp = a.exp +" " + op + " " + b.exp;  // só concatena toksns da expresão

            // Agora, tentando avaliar a expressão
            // tem que tratar os tipos.
            // são tantos casos...
            if(a.tipo==3 || b.tipo==3)
                if(op=="*"||op=="/"||op=="-") 
                    erros.add(new Erro(10,0,"Operação inválida",LIN,COL));
                    //waring("Operação inválida");
            
            // que acontece se tentar multiplicar strings?
            if(a.tipo==1 || b.tipo == 1) tipo = 1;
            if(a.tipo==2 && b.tipo == 2) tipo = 2;
            if(a.tipo==3 || b.tipo == 3) tipo = 3;
            if(a.tipo==2 && b.tipo != 2) erros.add(new Erro(10,0,"Operação ilegal",LIN,COL));//waring("Operação ilegal");
            if(a.tipo!=2 && b.tipo == 2) erros.add(new Erro(10,0,"Operação ilegal",LIN,COL));//waring("Operação ilegal");
            if(pog == 1) tipo = 2;
    
            // parseInt() e parseFloat() 
            // não aceitam qualquer parametro
            if(tipo==1){
                x2 = Double.parseDouble(a.str);
                y2 = Double.parseDouble(b.str);
            }
            if(tipo==0){
                x1 = Integer.parseInt(a.str); 
                y1 = Integer.parseInt(b.str);
            }
    

            //  "+"  | "-"  | "*"  | "/"
            if(op.equals("+")){ x1 += y1; x2 += y2; x3 += y3;}
            if(op.equals("-")){ x1 -= y1; x2 -= y2;}
            if(op.equals("*")){ x1 *= y1; x2 *= y2;}
            if(op.equals("/")){ x1 /= y1; x2 /= y2;}
            
            //  "&&"  | "||"  | "=="  | "!="  | ">="  | "<="  | "<"   | ">" 
            if(op.equals("&&") && x3.equals("true") && y3.equals("true")) x4 = true;
            if(op.equals("||") && (x3.equals("true") || y3.equals("true"))) x4 = true;
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
