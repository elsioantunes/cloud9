public class Lexico{
    public static int index;
    public static char content[];
    public static char nextChar(){return content[index++];}
    public static void rewind(){index--;}
    
    public static String nextToken(){
        for(int estado = 0;;){
            char c = nextChar();
            switch(estado){
                case 0:
                    if(c=='>') estado = 1;
                    if(c=='<') estado = 4;
                    if(c=='=') estado = 8;
                    if(estado==0) return "erro\n";
                    break;
                    
                case 1:
                    if(c=='=') return "GE ";
                    rewind();
                    return "GT ";

                case 4:
                    if(c=='=') return "LE ";
                    if(c=='>') return "NE ";
                    rewind();
                    return "LT ";
                    
                case 8:
                    if(c=='=') return "EQ ";
                    rewind();
                    return "AT ";
            }
        }
    }
    
    public static void main(String args[]){
        String linha = "<><=<<===>>=<> ";
        System.out.println(linha);
        index = 0;
        content = linha.toCharArray();
        while(index<content.length){
            System.out.print(nextToken());
        }
    }
}

/*
<><=<<===>>=<> 
NE
LE
LT
LE
EQ
GT
GE
NE
erro
*/