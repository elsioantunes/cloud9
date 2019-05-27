public class Parser{
    public Token token;
    public MeuLek lex;
    String code;
    public void list(){
        int j = 0;
        while(!lastToken()){
            System.out.println(token.str+"\t\t\t"+token.tipo);
            nextToken();
            if(j++>120) throw new IllegalStateException("mais de 120 tokens. Loop infinito?");
        }
        lex.reset();
        nextToken();
    }
    Parser(String str){lex = new MeuLek(str);nextToken();}
    public void falha(){if(!lastToken()) throw new IllegalStateException(" A expressao contem falha. Não esperava: "+code + " char:"+token.i);};
    public void nextToken(){token=lex.nextToken(); code=token.tipo;}
    public boolean lastToken(){return token.tipo.equals("[EOF]");}
}