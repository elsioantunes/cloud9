import java.io.*;

public class AnalisadorLexico {

    public static final int S0 = 0;
    public static final int S1 = 1;
    public static final int S2 = 2;
    public static final int S3 = 3;
    public static final int S4 = 5;
    public static final int S5 = 6;
    public static final int S6 = 7;
    public static final int S7 = 8;
    public static final int S9 = 10;
    public static final int SL = 4;

    private String fileContent;
    private int index;
    private int estado;


    public AnalisadorLexico(String fileName) {
        try {
            FileReader f = new FileReader(new File(fileName));
            BufferedReader br = new BufferedReader(f);
            String linha;
            StringBuilder fContent = new StringBuilder();
            fContent = new StringBuilder();
            while ((linha = br.readLine()) != null) {
                fContent.append(linha);
            }
 
            fileContent = fContent.toString() + '\0'; 
            index = 0;
            estado = S0;
 
        } catch (Exception ex) {
            System.err.println("Erro ao abrir arquivo");
        }
    }



    private char nextChar() {
        if (index < fileContent.length())
            return fileContent.charAt(index++);
        else
            return '\0';
    }


    private boolean isDigit(char ch) {
        return (ch >= '0' && ch <= '9');
    }


    private boolean isAlpha(char ch) {
        return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
    }


    public void retroceder() {
        index--;
    }


    public boolean isEOF() {
        return (index == fileContent.length());
    }



    public Token nextToken() {
        String symbol = "";
        estado = S0;
        Token token;
        char c;

        while (true) {

            switch (estado) {
                case S0:
                    c = nextChar();
                    
                    if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
                        estado = S0;

                    // detecta EOF
                    } else if (isEOF()) {
                        symbol = "EOF";
                        estado = S9;
                    
                    // detecta numero
                    } else if (isDigit(c)) {
                        symbol += c;
                        estado = S1;
                    
                    
                    // detecta identificador    
                    } else if (isAlpha(c)) {
                        symbol += c;
                        estado = S5;
                    
                    // detecta parte do numero, porquanto não deveria estar aqui 
                    } else if (c == '.') {
                        symbol += c;
                        estado = S2;
                    

                    // detecta operador. bora colocar dentro de expressão? 
                    } else if (c=='/'||c=='+'||c=='-') {
                        symbol += c;
                        estado = S4;

                    // detecta operador
                    } else if (c=='*') {
                        symbol += c;
                        estado = S6;

                    // detectou porra nenhuma. aqui dá token invalido
                    } else {estado = SL;}break;
                    
                    
                case S1:
                    c = nextChar();
                    if (isDigit(c)) { // sequencia de digitos
                        symbol += c;
                        estado = S1;
                    
                    } else if (c == '.') {
                        symbol += c;
                        estado = S2;
                    
                    } else {
                        retroceder(); // fim de numero inteiro
                        token = new Token();
                        token.setCode(Token.NUMERO_INTEIRO);
                        token.setSymbol(symbol);
                        symbol = "";
                        estado = S0;
                        return token;
                    }
                    break;


                case S2: // primeiro digito obrigatório
                    c = nextChar();

                    if (isDigit(c)) {
                        symbol += c;
                        estado = S3;
                    
                    } else {// numero terminado em ponto (invalido)
                        estado = SL;

                    }
                    break;
                
                case S3:
                    c = nextChar();

                    if (isDigit(c)) { // sequencia de digitos (do segundo em diante)
                        symbol += c;
                        estado = S3;
                    
                    } else {
                        retroceder(); // fim de numero real
                        token = new Token();
                        token.setCode(Token.NUMERO_PONTO_FIXO);
                        token.setSymbol(symbol);
                        estado = S0;
                        symbol = "";
                        return token;
                    }


                case S5:
                    c = nextChar();

                    if (isAlpha(c)) {
                        symbol += c;
                        estado = S5;

                    } else {
                        token = new Token();
                        retroceder();
                        estado = S0;
                        token.setCode(Token.IDENTIFICADOR);
                        token.setSymbol(symbol);
                        symbol = "";
                        return token;
                    }
                    break;


                case S4:
                        token = new Token();
                        token.setCode(Token.OPERADOR_ARITIMETICO);
                        token.setSymbol(symbol);
                        estado = S0;
                        symbol = "";
                        return token;
                      
                case S9:
                        token = new Token();
                        token.setCode(Token.EOF);
                        token.setSymbol(symbol);
                        estado = S0;
                        symbol = "";
                        return token;
                      
                case S6:
                        c = nextChar();
                        if (c=='*') {
                            symbol += c;
                            token = new Token();
                            estado = S0;
                            token.setCode(Token.OPERADOR_EXP);
                            token.setSymbol(symbol);
                            symbol = "";
                            return token;
                        }
                        retroceder();

                        token = new Token();
                        token.setCode(Token.OPERADOR_ARITIMETICO);
                        token.setSymbol(symbol);
                        estado = S0;
                        symbol = "";
                        return token;
                case SL:
                    estado = S0;
                    return null;

            }
        }
    }
}