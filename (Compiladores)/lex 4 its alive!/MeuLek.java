import java.io.*;
class MeuLek extends Scanner {
    MeuLek(String file){super(file);}

    public boolean getToken(){
        
        // posiciona o cursor para o primeiro provavel token valido
        while(c<=' '||c=='\n'||c=='\r'||c=='\f'||c=='\t') 
            getChar(); 
        
        // cria o container que levará as informações pedidas pelo parser
        token = new Token(arquivo.lin, arquivo.col);

        // fim de arquivo
        if(c=='\uffff') {
            token.code = EOF; 
            return false; 
        }

        // todos os casos possiveis que consegui imaginar
        else if(c==',') match( DELIMIT_COMMA); // Tokens de 2 chars
        else if(c==';') match( DELIMIT_SEMICOLON);
        else if(c==':') match( DELIMIT_DP);
        else if(c=='{') match( DELIMIT_LBRACE );
        else if(c=='}') match( DELIMIT_RBRACE );
        else if(c=='[') match( DELIMIT_LBRACK );
        else if(c==']') match( DELIMIT_RBRACK );
        else if(c=='(') match( DELIMIT_LPAR );
        else if(c==')') match( DELIMIT_RPAR );
        else if(c=='%') match( OP_MOD );
        else if(c=='-') match( OP_MINUS, '-', OP_DEC );  // Tokens de 2 chars
        else if(c=='+') match( OP_PLUS,  '+', OP_INC );
        else if(c=='*') match( OP_TIMES, '*', OP_EXP);
        else if(c=='!') match( OP_NEG,   '=', REL_NE );
        else if(c=='=') match( OP_ASSIGN,'=', REL_EQT );
        else if(c=='>') match( REL_GT,   '=', REL_GE );
        else if(c=='<') match( REL_LT,   '=', REL_LE );
        else if(c=='&') match( BIT_AND,  '&', LOGICAL_AND); 
        else if(c=='|') match( BIT_OR,   '|', LOGICAL_OR);

        else if(isAlpha(c)){               // T_ID   _b4n4n45
            while(isDigit(c)||isAlpha(c)) 
                match(T_ID);
            for(int i=0; i<nomes.length;i++)
                if(token.texto.equals(nomes[i]))
                    token.code = i;
        }
            
        else if(c == '.'){                 // T_REAL .123
            match(P_DOT); 
            if(isDigit(c)) 
                while(isDigit(c)) 
                    match(NUMBER2);
        }

        else if(c == '"'){                 // T_STRING "LoL @#?$ /* lOl */ "
            match(TOKEN_INVALIDO); 
            while(c != '"' && c != '\uffff') match(TOKEN_INVALIDO); 
            if(c == '"') match(T_STRING);
            else debug("Fodeu: String sem fim", 666);
        }

        else if(isDigit(c)){            // T_REAL  123.123
            while(isDigit(c)) 
                match(NUMBER);          // T_INT   123
            if(c=='.'){
                match(TOKEN_INVALIDO);
                if(isDigit(c))
                    while(isDigit(c)) 
                        match(NUMBER2);
            }
        }

        else if(c == '\''){                   // T_CHAR 'A'
            match(TOKEN_INVALIDO); 
            if(c >= ' ' && c<= '~' && c != '\\'){
                match(TOKEN_INVALIDO); 
                if(c == '\'') match(T_CHAR); 
            }
            else if(c == '\\'){              // chars doidos
                match(TOKEN_INVALIDO); 
                if(c == 'n' ||c == 'r' ||c == 't' ||c == 'f' ||c == '\'' ||c == '\\'){
                    match(TOKEN_INVALIDO); 
                    if(c == '\'') match(T_CHAR);  
                }
            }
        }

        else if(c == '/'){        // parse comment é foda
            match(OP_DIV);
            if(c=='/') {
                while(c!='\n' && c!='\uffff') match(COMMENT);
                return getToken(); // captura, ignora
            }
            else if(c == '*') {
                match(COMMENT); 
                int estado = 0;           // Automatozinho :p
                while(estado!=666){
                    switch(estado){
                        case 0: 
                            estado = 0;
                            if(c=='*') estado = 1;
                            if(c=='\uffff') debug("Fodeu: Comment sem fim", 666);
                            break;
                        case 1: 
                            estado = 0;
                            if(c=='/') estado = 666;
                            if(c=='*') estado = 1;
                    }
                    match(COMMENT);
                }
                return getToken(); // captura, ignora
            }
        }
        
        else match(TOKEN_INVALIDO);   // ?, ., @, #, \, \\, \", \uffff,  
        return true;
    }
}


class Scanner{
    public final int TOKEN_INVALIDO = 0, 
        COMMENT = 1, T_ID = 2, NUMBER2 = 3, NUMBER = 4, 
        DELIMIT_LBRACK = 5, DELIMIT_LBRACE = 6, DELIMIT_LPAR = 7, 
        DELIMIT_RBRACK = 8, DELIMIT_RPAR = 9, DELIMIT_RBRACE = 10, 
        OP_ASSIGN = 11, OP_MINUS = 12, OP_MOD = 13, OP_NEG = 14, OP_EXP = 15, 
        OP_TIMES = 16, OP_DEC = 17, OP_INC = 18, OP_PLUS = 19, OP_DIV = 20, 
        REL_LT = 21, REL_GE = 22, REL_GT = 23, REL_LE = 24, REL_NE = 25, REL_EQT = 26, 
        DELIMIT_COMMA = 27, P_DOT = 28, DELIMIT_SEMICOLON = 29,  
        BIT_AND = 30, LOGICAL_AND = 31, BIT_OR = 32, LOGICAL_OR = 33, DELIMIT_DP = 34,
        T_CHAR = 35, T_STRING = 36, EOF = 37, LITERAL_PRINT = 38, LITERAL_DECLARE = 39;


    public final String[] nomes = { 
        "TOKEN_INVALIDO                          ----#", 
        "COMMENT", "T_ID", "NUMBER2", "NUMBER", 
        "DELIMIT_LBRACK", "DELIMIT_LBRACE", "DELIMIT_LPAR", 
        "DELIMIT_RBRACK", "DELIMIT_RPAR", "DELIMIT_RBRACE", 
        "OP_ASSIGN", "OP_MINUS", "OP_MOD", "OP_NEG", "OP_EXP", 
        "OP_TIMES", "OP_DEC", "OP_INC", "OP_PLUS", "OP_DIV", 
        "REL_LT", "REL_GE", "REL_GT", "REL_LE", "REL_NE", "REL_EQT", 
        "DELIMIT_COMMA", "P_DOT", "DELIMIT_SEMICOLON", 
        "BIT_AND", "LOGICAL_AND", "BIT_OR", "LOGICAL_OR", "P_TP", 
        "T_CHAR", "T_STRING", "EOF", "PRINT", "DECLARE",
    };

    public Token token;
    public OpenFile arquivo;
    public char c;

    Scanner(String file){
        arquivo = new OpenFile(file);
    }

    // funcs uteis
    public void getChar(){arquivo.getChar();c = arquivo.c;}
    public void match(int code){token.code = code; token.texto += c; getChar();} // consome o char, monta a string e anota o tipo
    public void match(int code1, char c2, int code2){match(code1);if(c==c2) match(code2);} // match de dois chars
    public boolean isAlpha(char c){String lol = ""+c;return (lol.toUpperCase() != lol.toLowerCase()) || c == '_';}
    public boolean isDigit(char c){return c >= '0' && c <= '9';}
    public void debug(String str){System.out.println(str);}
    public void debug(String str, int lol){
        System.out.println(str);
        System.exit(256+24);
    }
}



class OpenFile{
    public BufferedReader br;
    public int lin, col;
    public char c;
    OpenFile(String filename){
        lin = 1; col = 0;
        try{
            FileReader f = new FileReader(filename);
            br = new BufferedReader(f);
        }catch(IOException e){
            System.err.println("[OpenFile Diz:"+e.getMessage()+"]");
        }
    }
    public void getChar(){
        try{
            col++;
            c = (char) br.read();
            if(c=='\n'){col=0; lin++;}
        }
        catch(IOException e){c = '\uffff';}
    }
}

class Token{
    public int lin, col, code;
    public String texto;

    Token(int lin, int col){
        this.texto = "";
        this.lin = lin;
        this.col = col;
    }
}
