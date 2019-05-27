
    class Comando{
        java.util.HashMap <String, Var> symbolTable;
        Comando escopo, cmdList[];
        String[] varInt,  varFloat,  varString,  varBool;
        int i, iInt, iFloat, iString, iBool, LIN;
        boolean sc;
    
        Comando(){
            symbolTable = new java.util.HashMap <String, Var>();
            cmdList = new Comando[300];
    
            varInt = new String[30];
            varFloat = new String[30];
            varBool = new String[30];
            varString = new String[30];
    
            i   = 0;
            iInt = 0;
            iBool = 0;
            iFloat = 0;
            iString = 0;
            sc = false;
        }
    
        void push(Comando cmd){
            cmdList[i++] = cmd;
        }
        
        void addvar(int tipo, String id, int LIN){
            this.LIN = LIN;
            if(!symbolTable.containsKey(id)){
                symbolTable.put(id, new Var(tipo, id));
                switch (tipo){
                    case 0: varInt[iInt++] = id; break;
                    case 1: varFloat[iFloat++] = id; break;
                    case 2: varBool[iBool++] = id; break;
                    case 3: varString[iString++] = id; break;
                }
            }else{
                waring("variavel "+id+" já consta");
            }
        }
    
    
        void run(int s){
        }
        
        String toJava(int s){
            String str1 = "";
            if(sc) str1+="import java.util.Scanner;\n";
            str1+="class MeuProg{// code by robot\n";
            str1+="   public static void main(String args[]){\n";
            if(sc) str1+="      Scanner scan = new Scanner(System.in);\n";
    
            if(iBool>0){
                str1+="      boolean ";
                str1+=varBool[0];
                for(int x=1;x<iBool;x++)
                    str1+=", "+varBool[x];
                str1+=";\n";
            }
            
            if(iString>0){
                str1+="      String ";
                str1+=varString[0];
                for(int x=1;x<iString;x++)
                    str1+=", "+varString[x];
                str1+=";\n";
            }
    
            if(iFloat>0){
                str1+="      double ";
                str1+=varFloat[0];
                for(int x=1;x<iFloat;x++)
                    str1+=", "+varFloat[x];
                str1+=";\n";
            }
    
            if(iInt>0){
                str1+="      int ";
                str1+=varInt[0];
                for(int x=1;x<iInt;x++)
                    str1+=", "+varInt[x];
                str1+=";\n";
            }
    
            str1+="\n";
    
            for(int x=0;x<i;x++)
                str1+=cmdList[x].toJava(2);
    
            if(sc) str1+="      scan.close();\n";
            str1+="   }\n";
            str1+="}\n\n";
            return str1;
        };

        String ident(int s){String ident = "";for(int i=0;i<s;i++)ident+="   ";return ident;}
        void waring(String str){print("### WARING: " + str);}
        void console(String str){print("\tCONSOLE: " + str);}
        void print(String str){System.err.println("Linha "+LIN+":\t"+str+"\n");}
    }
    
    class Atrib extends Comando{
        String exp, id, str;
        int tipo, tipov;
        Atrib(Comando escopo, String id, Var b, int LIN){
            this.id = id;
            this.tipov = -1;
            this.LIN = LIN;

            this.tipo = b.tipo;
            this.exp = b.exp;
            this.str = b.str;
    
            if(!escopo.symbolTable.containsKey(id)){
                waring("variavel '"+id+"' não declarada");
            }else{
                Var v = escopo.symbolTable.get(id);
                this.tipov = v.tipo;
                if(tipov!=tipo)waring("tipo incompatível");
                v.tipo = tipo;
                v.exp = exp;
                v.str = str;
                v.inic = true;
                escopo.symbolTable.put(id, v);
            }
        }
        String toJava(int s){
            String ident = ident(s);
            ident += id + " = " + exp + ";";
            ident += " \t//"+str+" tipovar:"+tipov+" tipoexp:"+tipo;
            ident += "\n";
            return ident;
        }
    }
    
    
    
    class While extends Comando{
        String exp;
        While(Var a, int LIN){
            this.LIN = LIN;
            this.exp = a.exp;
        }

        String toJava(int s){
            String ident = ident(s);
            String str1 = ident+"while("+exp+"){;\n";
            for(int x=0;x<i;x++)
                str1 += cmdList[x].toJava(s+1);
            str1 += ident+"};\n";
            return str1;
        }
    }
    
    class Print extends Comando{
        String exp, str;
        int tipo;
        Print(Var b, int LIN){
            this.LIN = LIN;
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
        Input(Comando escopo, String id, int LIN){
            //raiz.sc = true;
            if(!escopo.symbolTable.containsKey(id)) waring("a variável '"+id+"' precisa ser declarada previamente");
            this.id = id;
            this.tipo = escopo.symbolTable.get(id).tipo;
            this.LIN = LIN;
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