import java.util.List;

public class AnalisadorSintatico {

    private List<Token> _tokens;
    private int i;

    public AnalisadorSintatico(List<Token> tokens) {
        _tokens = tokens;
        i = 0;
    }
    

    private Token getToken(int i) {
        if (i <= _tokens.size() - 1) {
            return _tokens.get(i);
        } else {
            Token _token = new Token();
            _token.setCode(Token.BLANK);
            _token.setSymbol("");
            return _token;
        }
    }

    public void Analisar() {
        E();
        System.out.println("Analise Sintática concluída com sucesso.");
    }

    public void E() {
        T();
        E_();
    }

    public void T() {
        Token token = getToken(i);
        int code = token.getCode();
        if (code == Token.NUMERO_INTEIRO || code == Token.NUMERO_PONTO_FIXO || code == token.ID) {
            i++; //Obter simbolo
        } else {
            throw new IllegalStateException("Token não esperado pelo Analisador Sintático: " + token.getSymbol());
        }
    }

    public void E_() {
        Token token = getToken(i);
        int code = token.getCode();
        switch (code) {
            case Token.OPERADOR_ARIT:
                i++;
                E();
                break;
            case Token.BLANK:
                return;
            default:
                throw new IllegalStateException("Token não esperado pelo Analisador Sintático: " + token.getSymbol());
        }
    }
}
