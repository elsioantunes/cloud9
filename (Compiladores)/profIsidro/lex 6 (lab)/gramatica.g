class MeuParser extends Parser;
{
  private String operador;
  private int    resultado;
  private java.util.ArrayList<String> novaNotacao;
  private java.util.HashMap<String, Integer> mapaValores;
  private String idVar;
  private int    valVar;
  
  public void init(){
      resultado = 0;
      novaNotacao = new java.util.ArrayList<String>();
      mapaValores = new java.util.HashMap<String, Integer>();
  }
}

prog   : declara
         atribui
         expr
         
         { 
           Object[] valores = mapaValores.values().toArray();
           for (Object o: valores){
              System.out.println(o);
           }
         }
       ;
       
declara:  "declare" ID {mapaValores.put(LT(0).getText(),0);}
           (
           VIRG ID {mapaValores.put(LT(0).getText(),0);}  
           )* PF    
       ;
       
atribui:  (ID {idVar = LT(0).getText();}
           EQ 
           NUM {mapaValores.put(idVar,Integer.parseInt(LT(0).getText()));}
           PF)+ 
       ;

expr   :  "res" {System.out.println("Initializing...");}
          termo 
          {  resultado = valVar;
             novaNotacao.add(LT(0).getText()); }
          
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
       
exprl  :  (OP  {operador = LT(0).getText();}
           termo
           {
              if (operador.equals("+")){
                 resultado+=valVar;
              }
              else{
                 resultado-=valVar;
              }
              novaNotacao.add(LT(0).getText());
              novaNotacao.add(operador);
           }
           )*
       ;
       
termo  : ID   {valVar = mapaValores.get(LT(0).getText()).intValue();}  
       | NUM  {valVar = Integer.parseInt(LT(0).getText());}
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
      
NUM   :  ('0'..'9')+
         
      ;
      
BLANK : (' ' | '\t' | '\n' | '\r') { _ttype = Token.SKIP; }
      ;
      
PF    : '.'
      ;
      
VIRG  : ','
      ;
      
EQ    : '='
      ;
      