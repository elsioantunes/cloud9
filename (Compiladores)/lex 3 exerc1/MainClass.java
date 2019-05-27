public class MainClass{
    public static void main(String args[]){
        //String str = "laranjas -    b4n4n45 + ab4cax1s - 3.14 + 42 * t / o00";
        //String str = "003 ** asdf 5656  -zbolonhesas - \t . 2. .. \n  _b4n4n45 + ab4cax1s - 3.14 + 42 * \t / o00";
        //String str = "001 ? ** asdf 5656  -zbolonhesas - \t . 2. .. \n  _b4n4n45 + ab4cax1s - 3.14 + 42 * \t / o00,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,";
        
        String str = "12 /* lol */  \t+ 6*  4//aqui um comentário\n\n-45 /  /**/     _b4n4n45                ** 2.123";
        
        MeuParsa s = new MeuParsa(str);

        System.out.println("A expressão:\n \"" + str + "\"");

        if(s.isOK())
            System.out.println("\nA sintaxe está ok!");
        else
            System.out.println("deu grozóbi nessa babaça");
            
    }
}