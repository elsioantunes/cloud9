public class MeuLek extends Lexico {
    public Token nextToken(){
        t = new Token();
        while (!t.estado.equals("final")){
            char c = nextChar();
            t.i = i;
            t.skip = false;
            switch (t.estado){
                
                
                case "inicial":
                    if(c==' '||c=='\t'||c=='\n'||c=='\r'){t.skip=true;t.estado="inicial";}
                    else if(c=='+') Recognize("[OP_PLUS]");
                    else if(c=='%') Recognize("[OP_MOD]");
                    else if(c=='\0') Recognize("[EOF]");
                    else if(c=='-')  Recognize("[OP_MINUS]");
                    else if(c=='/') t.estado = "div_comment";
                    else if(c=='*')  t.estado = "op*";
                    else if(Digit(c)) t.estado = "digit";
                    else if(Alphan(c)) t.estado = "ident";
                    else Recognize("[TOKEN INVALIDO]");
                    break;
                
                
                case "div_comment":
                    if(c=='/') t.estado = "line_comment";
                    else if(c=='*') t.estado = "block_comment";
                    else Recognize("[OP_DIV]",1);
                    break;

                
                case "block_comment":
                    if(c!='*') t.estado = "block_comment";
                    else t.estado = "end_block_comment";
                    break;


                case "end_block_comment":
                    if(c=='/') Recognize("[COMMENT]");
                    else t.estado = "block_comment";
                    break;


                case "line_comment":
                    if(c!='\n') t.estado = "line_comment";
                    else Recognize("[COMMENT]",1);
                    break;


                case "op*":
                    if(c=='*') Recognize("[OP_EXPO]");
                    else Recognize("[OP_MULTIPLY]",1);
                    break;
                
                
                case "digit":
                    if(Digit(c)) t.estado = "digit"; // loop digitos
                    else if(c=='.') t.estado = "ponto";
                    else Recognize("[NUM INTEIRO]",1); 
                    break;
                
                case "ponto":
                    if (Digit(c)) t.estado = "mais_digitos";
                    else Recognize("[TOKEN INVALIDO]",1); // num terminado em ponto: erro
                    break;

                
                case "mais_digitos":
                    if (Digit(c)) t.estado = "mais_digitos";
                    else Recognize("[NUM REAL]",1); 
                    break;

                
                case "ident":
                    if (Alphan(c)||Digit(c)) t.estado = "ident"; // loop
                    else Recognize("[IDENTIFICADOR]",1);
                    break;
                    
                    
                    
            }
            if(!t.skip) t.montaStr(c);
        }
        return t;
    };
    MeuLek(String str){super(str);};
}




