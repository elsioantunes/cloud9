/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author francisco.massetto
 */
public class MeuErro {
    public void A(){
        if (Lexer.currentToken().equals("X")){
            Lexer.nextToken();
        }
        else{
            ERROR.e("Erro ao consumir X");
            while (!Lexer.currentToken().equals("W")) Lexer.nextToken();
        }
        if (Lexer.currentToken().equals("W"))
            Lexer.nextToken();
        else{
            ERROR.e("Erro ao consumir W");
        }
        
        if (Lexer.currentToken().equals("EOF")){
            System.out.println("Compilacao concluida");
        }
    }    
}
