// $ANTLR nao eh magia. Antes de ler o livro que o guru lhe deu você tem que escrever o seu!
class MeuProg{// code by robot
   public static void main(String args[]){
      int a, b;
      String s1, s2, s3;
      boolean p, q;
      double x, y;
      b = 4; 	//4 tipo:0
      System.out.println("digita tudo isso"); 	//digita tudo isso, 	 tipoexp:3
      a = 3; 	//3 tipo:0
      while(a < b){
         a = (3 + 5) * 2; 	//16 tipo:0
         p = 2 < 1; 	//false tipo:2
         if(a > b){
            System.out.println(a); 	//16, 	 tipoexp:0
            System.out.println(p); 	//false, 	 tipoexp:2
         }else{
            x = 3.5; 	//3.5 tipo:1
            y = .5; 	//.5 tipo:1
         };
      };
      System.out.println((3 + 5) * 2); 	//16, 	 tipoexp:0
      System.out.println((a + 5) * 2); 	//42, 	 tipoexp:0
   }
}


