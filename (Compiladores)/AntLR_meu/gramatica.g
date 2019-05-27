
class MeuParser extends Parser;

{
  String operador;
  int    resultado;
  java.util.ArrayList<String> novaNotacao;
  
  public void init(){
      resultado = 0;
      novaNotacao = new java.util.ArrayList<String>();
  }
}





prog   : declara
         atribui
         expr
       ;
       
declara:  "declare" ID (VIRG ID)* PF    
       ;
       
atribui:  (ID EQ NUMERO PF)+ 
       ;

expr   :  "res" 

                {System.out.println("Initializing...");}
            
          termo 
            
                {  //resultado = Integer.parseInt(LT(0).getText());
                novaNotacao.add(LT(0).getText()); 
                }
          
          exprl 
                {
                    System.out.println("Agora a notacao posfixa...");
                    for (String s: novaNotacao){
                        System.out.print(s + "  ");
                    }
                    System.out.println();
                    System.out.println("A conta vai dar "+resultado);
                }
       ;
       
       
       
       
exprl  :    (OP  
                {operador = LT(0).getText();}
            
            termo
                {
                    if (operador.equals("+")){
                    //    resultado+=Integer.parseInt(LT(0).getText());
                    }else{
                    //    resultado-=Integer.parseInt(LT(0).getText());
                    }
                    novaNotacao.add(LT(0).getText());
                    novaNotacao.add(operador);
                }
           )*
       ;

       
termo  : ID  
       | NUMERO 
       ;







class MeuLexico extends Lexer;

options
{
   caseSensitive = true;   
}

OP    :  ('+' | '-' )
      ;
 
ID    :  ('a'..'z') ('a'..'z' | '0'..'9')*
      ;
      
NUMERO   :  ('0'..'9')+
      ;
      

BLANK : (' ' | '\t' | '\n' | '\r') { _ttype = Token.SKIP; }
      ;
      
PF    : '.'
      ;
      
VIRG  : ','
      ;
      
EQ    : '='
      ;
      