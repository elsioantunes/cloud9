 class MeuParsa extends Parser{
    MeuParsa(String arq){
        super(arq);
        Start();
        if(isEndOfProg()) console("chegou ao fim do arquivo com sucesso");
    }
    
    /*
        <Start>         -> <Declare><Prog>
        <Declare>       -> (<DeclareString>|<DeclareInt>|<DeclareBool>)*
        <DeclareString> -> "STRING" <ID> (<virg><ID>)* <semicolon>
        <DeclareInt>    -> "INT"    <ID> (<virg><ID>)* <semicolon>
        <DeclareBool>   -> "BOOL"   <ID> (<virg><ID>)* <semicolon>
        <Prog>          -> (<Atrib>|<Print>|<NoExpeted>)* <EOF>
        <Atrib>         -> <ID> " = " <EXPR>
        <Print>         -> "PRINT" <EXPR> <SEMICOLON>
        <Input>         -> "INPUT"  <ID> (<VIRG><ID>)* <semicolon>

        <ExpREL>        ->  <Expr> ( ( "||" | "&&"  | "!="  | ">="  | ">="  | "<"   | ">" ) <Expr> )*
        <Expr>          ->  <Prod> ( ( "+" | "-" ) <Prod> )*
        <Prod>          ->  <Val>  ( ( "*" | "/" ) <Val>  )*
        <Val>           ->  "(" <Expr> ")" | ( <ID> | <STRING> | <NUMBER>  | <BOOL> ) 
    */
    
    // <Start> -> <Declare><Prog>
    void Start(){
        Declare();
        Prog();
    }
    
    // <Declare>  -> (<DeclareString>|<DeclareInt>|<DeclareBool>)*
    void Declare(){
        while(isDeclaration())
            Declare(CODE);
    }
    
    // <DeclareString> -> "STRING" <ID> (<virg><ID>)* <semicolon>
    // <DeclareInt>    -> "INT"    <ID> (<virg><ID>)* <semicolon>
    // <DeclareBool>   -> "BOOL"   <ID> (<virg><ID>)* <semicolon>
    void Declare(TokenTypes code){
        switch (code){
            case LITERAL_INT: tipo = 0; break;
            case LITERAL_STRING: tipo = 1; break;
            case LITERAL_BOOL: tipo = 2; break;
        }
        matchDeclaration();
        SETVAR(tipo, STR);
        matchId();
        while(ifMatchComma()){
            SETVAR(tipo, STR);
            matchId();
        }
        matchSemicolon();
    }

    // <Prog> -> (<Atrib>|<Print>|<Input>|<IfCMD>|<NoExpeteds>)* <EndOfProg>
    void Prog(){
        while(true){
            if(isID()) Atrib();
            else if(ifMatchPrint()) Print();
            else if(ifMatchInput()) Input();
            else if(ifMatchIfCMD()) IfCMD();
            else if(isEndOfProg()) break;
            else noExpected();
        }
    }
    
    // <IfCMD>  ->  "IF" <ExpREL> "THEN" <Prog> (<ElseProg>)?
    void IfCMD(){ // TODO
        ExpREL();
        Prog();
        ElseProg();
    }
    
    // <ElseProg> -> "ELSE" <Prog> 
    void ElseProg(){ // TODO
        Prog();
    };

    // <Atrib>  -> <ID> " = " <EXPR>
    void Atrib(){
        String var = STR;
        Var v = GETVAR(var);
        tipo = v.tipo;
        matchId();
        matchAssign();
        Atrib(var);
        matchSemicolon();
    }
    void Atrib(String var){
        ExpREL();
        SETVAR(var, str);
        console(":atrib: Atribuído ["+str+"] a ["+var+"]");
    }

    // <Print>   -> "PRINT" <EXPR> <SEMICOLON>
    void Print(){
        pog1 = true;
        tipo = 0;
        ExpREL();
        pog1 = false;
        console(":printing: "+str);
        matchSemicolon();
    }
    
    // <Input>   -> "INPUT" <ID> ( <VIRG> <ID> )* <SEMICOLON>
    void Input(){
        Var in = GETVAR(STR); 
        matchId();
        while(ifMatchComma()){
            in = GETVAR(STR); 
            matchId();
        }
        matchSemicolon();
    }
    
    
    
    

    // <ExpREL>  ->  <Expr> ( ( "||" | "&&"  | "!="  | "=="  | ">="  | "<="  | "<"   | ">" ) <Expr> )*
    void ExpREL(){ // TODO: completar isto;
        Expr();
        boolean m2, m1 = str.equals("true"); // não se preocupe, string não chega aqui assim
        
        console(""+str);
        
        int p2, p1 = toInt(tipo!=0?"0":str);
        while(isOpRel()){
            code = CODE;
            matchOpRel(); // TODO: capturar o operador para diferenciar as operações abaixo
            Expr(); 
            m2 = str.equals("true");
            
            console("m1: "+m1+" m2: "+m2);
            
            switch(code){
                case REL_OR: m1 |= m2;break;
                case REL_AND: m1 &= m2;break;
            }
        }
        if(tipo==0) str = ""+p1;
        else if(tipo==2) str = m1?"true":"false";
    }

    // <Expr>    ->  <Prod> ( ( "+" | "-" ) <Prod> )*
    void Expr(){
        Prod();
        int p2, p1 = toInt(tipo!=0?"0":str);
        String s2, s1 = str;
        while(isPlusOrMinus()){
            matchPlusOrMinus(); // TODO: capturar o operador para diferenciar as operações abaixo
            Prod();
            p2 = toInt(tipo!=0?"0":str);
            p1 += p2; // só tá somando os inteiros. falta subtração
            s2 = str;
            s1 += s2; // concatenando strings assim, provisoriamente
        }
        if(tipo==1) str = s1;
        else if(tipo==0) str = ""+p1;
    }
    
    // <Prod>    ->  <Val>  ( ( "*" | "/" ) <Val>  )*
    void Prod(){
        Val();
        int p2, p1 = toInt(tipo!=0?"0":str);
        while(isDivOrTimes()){
            if(tipo!=0) erro("operação ilegal"); // string ou bool do lado esquerdo
            matchDivOrTimes();
            Val();
            if(tipo!=0) erro("operação ilegal"); // string ou bool do lado direito
            p2 = toInt(str);
            p1 *= p2;
        }
        if(tipo==0) str = ""+p1;    
    }
    
    // <Val>     ->  "(" <Expr> ")" | ( <ID> | <STRING> | <NUMBER>  | <BOOL> ) 
    void Val(){
        if(isID()){
            Var v = GETVAR(STR); 
            if(!v.inic) erro("a variável '"+STR+"' não tem valor");
            str = v.str;
            nextToken();
        }else if(isBool()){
            str = STR;
            if(tipo==0)  // conversão bol>>num
                if(STR.equals("false")) str = "0";
                else str = "1";
            nextToken();
        }else if(isNumber()){
            str = STR;
            if(tipo==2) // conversão num>>bol
                if(STR.equals("0")) str = "false";
                else str = "true";
            nextToken();
        }else if(isString()){
            if(tipo==0){       // SIM, é um pog.        
                if(pog1) {     // me envergonho de não 
                    tipo=1;    //saber resolver isso de outra manaira
                    str = noQuotes(STR);
                }
                else erro("variável numérica não aceita string");
            }else if(tipo==2){
                str = STR.length()>0?"true":"false";
            }else 
                str = noQuotes(STR);
            nextToken();
        }else{
            abreParenteses();
            ExpREL();
            fechaParenteses();
        }
    }
}




