
import java.util.List;

public class Compilador {

    public static void main(String[] args) {
        String chain = "10.5 - allan   +   109 - .45 + 10.10 ** variable + 20 * 15";
        
        //Analise Lexica
        AnalisadorLexico an = new AnalisadorLexico(chain);
        List<Token> tokens = an.getTokens();
        
        //Analise Sintatica
        AnalisadorSintatico as = new AnalisadorSintatico(tokens);
        as.Analisar();
    }
}