import java.util.Scanner;
class MeuProg{// code by robot
   public static void main(String args[]){
      Scanner scan = new Scanner(System.in);
      int i , j; // (2)
      String s1 , sabão , égide; // (2)
      float x , y; // (2)
      i = 2; //(2)
      j = ( ( ( 3 + 4 ) / 7 + 1 ) * 13 - 5 ) / 7; //(2)
      égide = "Elsio " + "Antunes " + ( i * j * 2 + ( ( 3 + i ) * 5 + 8 ) ); //(2)
      System.out.println(égide);
      System.out.println("diga seu nome e me de dois numeros");
      sabão = scan.nextLine();
      x = scan.nextFloat();
      y = scan.nextFloat();
      System.out.println("Olá " + sabão + "\nA soma de " + x + " e " + y + " é " + ( x + y ));
      scan.close();
   }
}


/*
21,4:		CONSOLE: chegou ao fim do arquivo com sucesso




*/
