// MeuLek extende a classe Scanner 
// que contem todas as ferramentas para que o getToken seja possivel
class MeuLek extends Scanner{
    MeuLek(String file){super(file);}
    
    // Método principal que será usado no parser
    public boolean getToken(){
        
        // posiciona o cursor para o primeiro provavel token valido
        skipChars();
        
        // cria o container que levará as informações pedidas pelo parser
        token = new Token(arq.lin, arq.col);

        // fim de arquivo?
        if( c == '\uffff' ){
            token.code = TokenTypes.EOF;
            return false;
        }

        // todos os casos possiveis que consegui imaginar
        else if( c == ',' ) match( TokenTypes.DELIMIT_COMMA); // Tokens de 1 char
        else if( c == ';' ) match( TokenTypes.DELIMIT_SEMICOLON);
        else if( c == ':' ) match( TokenTypes.DELIMIT_COLON);
        else if( c == '{' ) match( TokenTypes.DELIMIT_LBRACE );
        else if( c == '}' ) match( TokenTypes.DELIMIT_RBRACE );
        else if( c == '[' ) match( TokenTypes.DELIMIT_LBRACK );
        else if( c == ']' ) match( TokenTypes.DELIMIT_RBRACK );
        else if( c == '(' ) match( TokenTypes.DELIMIT_LPAR );
        else if( c == ')' ) match( TokenTypes.DELIMIT_RPAR );
        else if( c == '%' ) match( TokenTypes.OP_MOD );
        else if( c == '-' ) match( TokenTypes.OP_MINUS, '-', TokenTypes.OP_DEC );  // Tokens de 2 chars
        else if( c == '+' ) match( TokenTypes.OP_PLUS,  '+', TokenTypes.OP_INC );
        else if( c == '*' ) match( TokenTypes.OP_TIMES, '*', TokenTypes.OP_EXP);
        else if( c == '!' ) match( TokenTypes.OP_NEG,   '=', TokenTypes.REL_NE );
        else if( c == '=' ) match( TokenTypes.OP_ASSIGN,'=', TokenTypes.REL_EQT );
        else if( c == '>' ) match( TokenTypes.REL_GT,   '=', TokenTypes.REL_GE );
        else if( c == '<' ) match( TokenTypes.REL_LT,   '=', TokenTypes.REL_LE );
        else if( c == '&' ) match( TokenTypes.BIT_AND,  '&', TokenTypes.LOGICAL_AND); 
        else if( c == '|' ) match( TokenTypes.BIT_OR,   '|', TokenTypes.LOGICAL_OR);
        

        // casos de tokens não tão simples
        // que requerem processamento 
        // do que foi capturado

        else if( isAlpha(c) ){               // T_ID   _b4n4n45            
            while(isAlpha(c)||isDigit(c))
                match(TokenTypes.T_ID);

            for(TokenTypes t: TokenTypes.values())  // palavras reservadas
                if(t.toString().equals("LITERAL_"+token.str))
                    match(t);
        }


        else if( c == '.' ){                 // T_REAL .123
            match(TokenTypes.P_DOT); 
            if( isDigit(c) ) 
                while(isDigit(c)) 
                    match(TokenTypes.NUMBER2);
        }
        
        else if( c == '"' ){                 // T_STRING "LoL @#?$ /* lOl */ "
            match(TokenTypes.TOKEN_INVALIDO); 
            while( c != '"' && c != '\uffff') 
                match(TokenTypes.TOKEN_INVALIDO); 
            if(c == '"') 
                match(TokenTypes.T_STRING);
            else 
                print("Fodeu: String sem fim", 666);
        }

        else if( isDigit(c) ){              // Número
            while( isDigit(c) ) 
                match(TokenTypes.NUMBER);   // T_INT   123
            if( c == '.' ){                 // ponto final?
                match(TokenTypes.TOKEN_INVALIDO);
                if( isDigit(c) )            // T_REAL  123.123
                    while( isDigit(c) ) 
                        match(TokenTypes.NUMBER2);
            }
        }

        else if( c == '\''){                // T_CHAR 'A'
            match(TokenTypes.TOKEN_INVALIDO); 
            if(c >= ' ' && c<= '~' && c != '\\'){ // caracteres visíveis
                match(TokenTypes.TOKEN_INVALIDO); 
                if( c == '\'' ) 
                    match(TokenTypes.T_CHAR); // só aceita depois de fechado
                else {
                    while( c != '\'' && c != '\uffff') 
                        match(TokenTypes.TOKEN_INVALIDO); 
                    if(c == '\'') 
                        match(TokenTypes.TOKEN_INVALIDO);
                    else 
                        print("Fodeu: String malformada e sem fim na linha " + token.lin, 666);
                }
            }
            else if(c == '\\'){              // chars doidos
                match(TokenTypes.TOKEN_INVALIDO); 
                if(c == 'n' ||c == 'r' ||c == 't' ||c == 'f' ||c == '\'' ||c == '\\'){
                    match(TokenTypes.TOKEN_INVALIDO); 
                    if(c == '\'')           // só aceita depois de fechado
                        match(TokenTypes.T_CHAR);  
                }
            }
        }

        else if( c == '/' ){        // parse comment é complicado
            match(TokenTypes.OP_DIV);// div simples
            if( c == '/' ) {
                while( c != '\n' && c!= '\uffff' ) 
                    match(TokenTypes.COMMENT); // comment inline
                return getToken(); // captura, ignora
            }
            else if( c == '*' ) {
                match(TokenTypes.COMMENT); 
                int estado = 0;           // Automatozinho :p
                while(estado!=666){
                    switch(estado){
                        case 0: 
                            estado = 0;
                            if( c == '*' ) estado = 1;
                            if( c == '\uffff' ) 
                                print("Fodeu: Comment sem fim", 666);
                            break;
                        case 1: 
                            estado = 0;
                            if( c == '/' ) estado = 666;
                            if( c == '*' ) estado = 1;
                    }
                    match(TokenTypes.COMMENT);
                }
                return getToken(); // captura, ignora
            }
        }
        
        // se nada tiver sido reconhecido, retorna token invválido
        else match(TokenTypes.TOKEN_INVALIDO);
        return true;
    }
}


// A classe Scanner é a que tem as ferramentas para a analise lexica
// deixo o método getToken numa classe separada pois ela é mais complexa.
class Scanner {    
    public Token token;
    public OpenFile arq;
    public char c;
    
    Scanner(String file){
        arq = new OpenFile(file);
    }

    // ferramenta principal de getToken
    // tem a função de consumir o char reconhecido,
    // dar o nome (code) do token e montar sua string.
    public void match(TokenTypes code){
        token.str += c;
        token.code = code;
        getChar();
    }

    // versão de match para dois chars
    public void match(TokenTypes code1, char c2, TokenTypes code2){
        match(code1);
        if( c == c2 )
            match(code2);
    }

    // avança cursor
    public void getChar(){
        arq.getChar();
        c = arq.c;
    }
    
    // pula caracters espaçadores
    public void skipChars(){
        while(c<=' '||c=='\n'||c=='\r'||c=='\f'||c=='\t') 
            getChar(); 
    }

    // responde se o caractere é alfanumérico
    public boolean isAlpha(char c){
        String lol = "" + c;
        return (lol.toUpperCase() != lol.toLowerCase()) || c == '_';
    }

    // responde se o caractere é numérico
    public boolean isDigit(char c){
        return c >= '0' && c <= '9';
    }

    // debug
    public void print(String str){
        System.out.println(str);
    }

    // versão do debug que encerra o programa
    public void print(String str, int lol){
        print(str);
        System.exit(256+24);
    }
}