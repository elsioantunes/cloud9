/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


/**
 *
 * @author francisco.massetto
 */
public class Lexer {

    public static String tokens[];

    static {
        tokens = new String[10];
        tokens[0] = "Q";
        tokens[1] = "Y";
        tokens[2] = "Z";
        tokens[3] = "W";
        tokens[4] = "EOF";
    }

    public static int pos = 0;

    public static String currentToken() {
        return tokens[pos];
    }

    public static void nextToken() {
        pos++;
    }
}
