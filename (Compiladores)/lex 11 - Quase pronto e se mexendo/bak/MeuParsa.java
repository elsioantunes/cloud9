 class MeuParsa extends Parser{

    MeuParsa(String arq){
        super(arq);
        Start();
        if(isEnd()) console("Acho que ficou bom o resultado com sucesso.\n*/");
    }
    
    /*
        <Start>         -> <Declare><Prog>
        <Declare>       -> (<DeclareString>|<DeclareInt>|<DeclareBool>)*
        <DeclareString> -> "STRING" <ID> (<virg><ID>)* <semicolon>
        <DeclareInt>    -> "INT"    <ID> (<virg><ID>)* <semicolon>
        <DeclareBool>   -> "BOOL"   <ID> (<virg><ID>)* <semicolon>
        <Corpo>         -> (<Atrib>|<Input>|<Print>|<While>|<Until>|<If>|<For>|<noExpected><Eof>|)*
        <Atrib>         -> <ID> <ASSIGN> <ExpR>
        <Print>         -> "PRINT" <ExpR> <SEMICOLON>
        <Input>         -> "INPUT"  <ID> (<VIRG><ID>)* <semicolon>
        <ForCMD>        -> "FOR" <ID> <ASSIGN> <Exp> "TO" <Exp> ("STEP" <Exp>)?

        <ExpR>          ->  <Exp>  ( "!="  | ">="  | ">="  | "<"   | ">" ) <Exp> )?
        <Exp>           ->  <Prod> ( ( "+" | "-" ) <Prod> )*
        <Prod>          ->  <Val>  ( ( "*" | "/" ) <Val>  )*
        <Val>      ->  ( <ID> | <STRING> | <NUMBER>  | <BOOL> ) | "(" <Expr> ")"
        
    */
    
    void Start(){
        //OpenFileOut();
        Corpo();
        
        //System.out.println("SymbolTable:");
        //for(Var v: symbolTable.values())
          //System.out.println("\t"+v.show());
        
        System.out.println("// $ANTLR de cu é rola! Antes de ler o livro que o guru lhe deu você tem que escrever o seu!\n");
        System.out.println(prog.writeCode(0));
    }
    
    void Corpo(){
        while(true){
            if(isDeclaration()) Declare();
            else if(isID()) Atrib();
            else if(ifMatchPrint()) Print();
            else if(ifMatchInput()) Input();
            else if(ifMatchWhileCMD()) WhileCMD();
            else if(ifMatchUntilCMD()) UntilCMD();
            else if(ifMatchIfCMD()) IfCMD();
            else if(ifMatchForcmd()) Forcmd();
            else if(isEnd()) break;
            else noExpected();
        }
    }
    
    void Declare(){
        switch (CODE){
            case LITERAL_INT: tipo = Tipo.INT; break;
            case LITERAL_STRING: tipo = Tipo.STRING; break;
            case LITERAL_BOOL: tipo = Tipo.BOOL; break;
            case LITERAL_FLOAT: tipo = Tipo.FLOAT; break;
        }
        matchDeclaration();
        logExpOn();
        do {
            DECLAREVAR(STR);
            matchId();
        } while(ifMatchComma());
        logExpOff();
        matchSemicolon();
        MONTAdecl(tipo, exp);
    }

    void Atrib(){
        Var a = GETVAR(STR);
        matchId();
        matchAssign();
        SETVAR(a, ExpR());
        matchSemicolon();
        MONTAatrib(a.id, exp);
    }
    
    void Input(){
        Var a;
        logExpOn();
        do{
            a = GETVAR(STR);
            matchId();
            MONTAinput(a.tipo, a.id);
        }while(ifMatchComma());
        logExpOff();
        matchSemicolon();
        
    }
    
    void Print(){
        Var a = ExpR();
        matchSemicolon();
        MONTAprint(exp);
    }
    
    void Forcmd(){ // TODO
        matchId();
        matchAssign();
        Var a = ExpR();
        matchTo();
        Var b = ExpR();
        if(ifMatchStep()){
            Var c = ExpR();
        }
        Corpo();
        matchNext();

    }

    void IfCMD(){
        Var a = ExpR();
        matchThen();
        MONTAif(exp);
        Corpo();
        MONTAendif();
        if(ifMatchElse()){
            MONTAelse();
            Corpo();
            MONTAendif();
        }
        matchEndIf();
    }

    void UntilCMD(){
        Var tmp = ExpR();
        Corpo();
        matchLoop();

    }

    void WhileCMD(){
        Var tmp = ExpR();
        MONTAwhile(exp);
        Corpo();
        ANINHA();
        matchLoop();
    }


   /***********************************************
   ************************************************/
    Var ExpR(){
        logExpOn();
        Var a = ExpR_(); 
        logExpOff();
        return a;
    }
 
   // <ExpR   ->  <Exp> (( "!="  | "<="  | ">="  | "<"   | ">" ) <Exp>)? 
    Var ExpR_(){
        Var a = Exp();
        if(isOpRel()){
            int op = opRel();
            Var b = Exp();
            a = Opera(a, op, b);
        }
        return a;
    }
    
    //<Exp>     ->  <Prod> ( ( "+" | "-" ) <Prod> )*
    Var Exp(){
        Var a = Prod();
        while(isPlusOrMinus()){
            int op = plusOrMinus();
            Var b = Prod();
            a = Opera(a, op, b);
        }
        return a;
    }
    
    //<Prod>     ->  <Val>  ( ( "*" | "/" ) <Val>  )*
    Var Prod(){
        Var a = Val();
        while(isDivOrTimes()){
            int op = divOrTimes();
            Var b = Val();
            a = Opera(a, op, b);
        }
        return a;
    }
    
    //<Val>      ->  ( <ID> | <STRING> | <NUMBER>  | <BOOL> ) | "(" <Expr> ")"
    Var Val(){
        Var v = new Var(Tipo.INT, "exp");
        if(isID()){
            v = GETVAR(STR);
            match();
        }else if(isINT()){
            v.str = STR;
            match();
        }else if(isFLOAT()){
            v.tipo = Tipo.FLOAT;
            v.str = STR;
            match();
        }else if(isSTRING()){
            v.tipo = Tipo.STRING;
            v.str = noQuotes(STR);
            match();
        }else{
            abreParenteses();
            v = ExpR_();
            fechaParenteses();
        }
        return v;
    }

 }




