import java.util.ArrayList;
import java.util.List;

public class AnalisadorLexico {

    private static final int S0 = 0;
    private static final int S1 = 1;
    private static final int S2 = 2;
    private static final int S3 = 3;
    private static final int S4 = 4;
    private static final int S5 = 5;
    private static final int S6 = 6;
    private static final int S7 = 7;
    private static final int SL = 10;

    private String fileContent;
    private int index;
    private int estado;
    private boolean _verbose;

    private List<Token> _tokens;

    public AnalisadorLexico(String chain, boolean verbose) {
        this(chain);
        _verbose = verbose;
}

    public AnalisadorLexico(String chain) {
        fileContent = chain + '\0';
        index = 0;
        estado = S0;
        _tokens = new ArrayList<>();
    }

    public List<Token> getTokens() {
        while (!isEOF()) {
            Token t = nextToken();
            if (t != null) {
                if (_verbose) {
                    System.out.println("Reconhecido " + t.getCode() + "  " + t.getSymbol());
                }
                _tokens.add(t);
            } else {
                throw new IllegalArgumentException("Token invalido");
            }
        }
        System.out.println("Analise Léxica concluída com sucesso.");
        return _tokens;
    }

    private char nextChar() {
        if (index < fileContent.length()) {
            return fileContent.charAt(index++);
        } else {
            return '\0';
        }
    }

    private boolean isDigit(char ch) {
        return (ch >= '0' && ch <= '9');
    }

    private boolean isAlpha(char ch) {
        return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
    }

    private void retroceder() {
        index--;
    }

    private boolean isEOF() {
        return (index == fileContent.length() - 1);
    }

    private Token nextToken() {
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
                    } else if (isDigit(c)) {
                        symbol += c;
                        estado = S1;
                    } else if (c == '.') {
                        symbol += c;
                        estado = S2;
                    } else if (c == '+' || c == '-' || c == '/') {
                        symbol += c;
                        estado = S4;
                    } else if (c == '*') {
                        symbol += c;
                        estado = S5;
                    } else if (isAlpha(c)) {
                        symbol += c;
                        estado = S7;
                    } else {
                        estado = SL;
                    }
                    break;
                case S1:
                    c = nextChar();
                    if (isDigit(c)) {
                        symbol += c;
                        estado = S1;
                    } else if (c == '.') {
                        symbol += c;
                        estado = S2;
                    } else {
                        token = new Token();

                        retroceder();
                        estado = S0;
                        token.setCode(Token.NUMERO_INTEIRO);
                        token.setSymbol(symbol);
                        symbol = "";
                        return token;
                    }
                    break;
                case S2:
                    c = nextChar();

                    if (isDigit(c)) {
                        symbol += c;
                        estado = S3;
                    } else {
                        estado = SL;
                    }
                    break;
                case S3:
                    c = nextChar();

                    if (isDigit(c)) {
                        symbol += c;
                        estado = S3;
                    } else {
                        token = new Token();
                        token.setCode(Token.NUMERO_PONTO_FIXO);
                        token.setSymbol(symbol);
                        estado = S0;
                        symbol = "";
                        retroceder();
                        return token;
                    }
                    break;
                case S4: // Operador Aritmetico (+, -, /)
                    token = new Token();
                    estado = S0;
                    token.setCode(Token.OPERADOR_ARIT);
                    token.setSymbol(symbol);
                    symbol = "";
                    return token;

                case S5: // Operador Aritmetico (*)
                    c = nextChar();

                    if (c == '*') {
                        symbol += c;
                        estado = S6;
                    } else {
                        token = new Token();
                        token.setCode(Token.OPERADOR_ARIT);
                        token.setSymbol(symbol);
                        estado = S0;
                        symbol = "";
                        retroceder();
                        return token;
                    }
                    break;
                case S6:
                    token = new Token();
                    estado = S0;
                    token.setCode(Token.OPERADOR_ARIT);
                    token.setSymbol(symbol);
                    symbol = "";
                    return token;
                case S7:
                    c = nextChar();

                    if (isAlpha(c)) {
                        symbol += c;
                        estado = S7;
                    } else {
                        token = new Token();
                        retroceder();
                        estado = S0;
                        token.setCode(Token.ID);
                        token.setSymbol(symbol);
                        symbol = "";
                        return token;
                    }
                    break;
                case SL:
                    estado = S0;
                    return null;
            }
        }
    }
}
