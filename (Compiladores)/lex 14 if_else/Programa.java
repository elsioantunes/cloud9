
    class Comando{
        Comando escopo, cmdList[];
        int i;
        boolean sc;

        Comando(){
            cmdList = new Comando[300];
            i = 0;
            sc = false;
        }

        void run(int s){}
        void setScan(){sc = true;}
        void push(Comando cmd){cmdList[i++] = cmd;}

        String toJava(int s){
            String str1 = "";
            if(sc) str1   +=  "import java.util.Scanner;\n";
            str1          +=  "class MeuProg{// code by robot\n";
            str1          +=  "   public static void main(String args[]){\n";
            if(sc) str1   +=  "      Scanner scan = new Scanner(System.in);\n";

            for(int x=0;x<i;x++)
                str1+=cmdList[x].toJava(2);

            if(sc) str1   +=  "      scan.close();\n";
            str1          +=  "   }\n";
            str1          +=  "}\n\n";
            return str1;
        };
        
        String ident(int s){String ident = "";for(int i=0;i<s;i++)ident+="   ";return ident;}
    }

    class Declare extends Comando{
        String exp, tip;
        Declare(int tipo, String exp){
            this.exp = exp;
            switch (tipo){
                case 0: tip = "int "; break;
                case 1: tip = "double "; break;
                case 2: tip = "boolean "; break;
                case 3: tip = "String "; break;
            }
        }
        String toJava(int s){
            String ident = ident(s);
            ident += tip+exp+";\n";
            return ident;
        }
    }

    class Atrib extends Comando{
        String exp, id, str;
        int tipo;
        Atrib(String id, Var b){
            this.id = id;
            this.tipo = b.tipo;
            this.exp = b.exp;
            this.str = b.str;
        }
        String toJava(int s){
            String ident = ident(s);
            ident += id + " = " + exp + ";";
            ident += " \t//"+str+" tipo:"+tipo;
            ident += "\n";
            return ident;
        }
    }
    
    class Print extends Comando{
        String exp, str;
        int tipo;
        Print(Var b){
            this.tipo = b.tipo;
            this.exp = b.exp;
            this.str = b.str;
        }
        String toJava(int s){
            String ident = ident(s);
            ident += "System.out.println("+exp+");";
            ident += " \t//"+str+", \t tipoexp:"+tipo;
            ident += "\n";
            return ident;
        }
    }
    
    class Input extends Comando{
        String id, tip;
        int tipo;
        Input(String id, int tipo){
            this.id = id;
            this.tipo = tipo;
            switch (tipo){
                case 0: tip = "Int()"; break;
                case 3: tip = "Line()"; break;
                case 1: tip = "Float()"; break;
                case 2: tip = "Boolean()"; break;
            }
        }
        String toJava(int s){
            String ident = ident(s);
            ident+= id+" = scan.next"+tip+";\n";
            return ident;
        }
    }


    
    class While extends Comando{
        String exp;
        While(Var a){this.exp = a.exp;}
        String toJava(int s){
            String ident = ident(s);
            String str1 = ident+"while("+exp+"){\n";
            for(int x=0;x<i;x++)
                str1 += cmdList[x].toJava(s+1);
            str1 += ident+"};\n";
            return str1;
        }
    }
    
    class If extends Comando{
        Comando cmdList[], elseList[];
        boolean elsemode;
        String exp;
        int i, j;

        If(Var a){
            this.exp = a.exp;
            elseList = new Comando[300];
            cmdList = new Comando[300];
            i = 0;
            j = 0;
            elsemode = false;
        }

        void changeElseMode(){elsemode = true;}
        void push(Comando cmd){
            if(elsemode) elseList[j++] = cmd;
            else cmdList[i++] = cmd;
        }

        String toJava(int s){
            String ident = ident(s);
            String str1 = ident+"if("+exp+"){\n";
            for(int x=0;x<i;x++)
                str1 += cmdList[x].toJava(s+1);
            if(j>0){
                str1 += ident+"}else{\n";
                for(int x=0;x<j;x++)
                    str1 += elseList[x].toJava(s+1);
            }
            str1 += ident+"};\n";
            return str1;
        }
    }
    
    
    
  /***********************************************
   ***********************************************/
    
    

    class Pilha{
        Comando[] buf;
        int topo;
        Pilha(){
            topo = 0;
            buf = new Comando[12];
        }
        void push(Comando Cmd){
            buf[topo++] = Cmd;
        }
        boolean vazia(){
            return topo == 0;
        }
        Comando pop(){
            return buf[--topo];
        }
        Comando getTopo(){
            return buf[topo-1];
        }
    }
    
    class Var{
        String str, id, exp, res;
        boolean inic;
        int tipo;
        Var(int tipo, String id){
            this.id = id;
            this.tipo = tipo;
            this.inic = false;
            this.str = "0";
            this.exp = "";
        }
        
        String show(){
            String str1="";
            str1+="id: {"+id+"}, \t";
            str1+="str: {"+str+"}, \t";
            str1+="exp: {"+exp+"}, \t";
            str1+="tipo: {"+tipo+"} \t";
            return str1;
        }
    }