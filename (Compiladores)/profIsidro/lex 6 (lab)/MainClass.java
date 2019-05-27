public class MainClass{
    public static void main(String args[]) {
        try{
            MeuLexico lexer  = new MeuLexico(System.in);
            MeuParser parser = new MeuParser(lexer);
            
            parser.init();
            parser.prog();
        }
        catch(Exception ex){
            System.err.println("Deu ruim ao analisar...");
            ex.printStackTrace();
        }
    }
}