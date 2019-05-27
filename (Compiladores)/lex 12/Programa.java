class Programa{
    Programa[] cmdList;
    int i;
    Programa(){
        cmdList = new Programa[300];i = 0;
    }

    void push(Programa cmd){
        cmdList[i++] = cmd;
    }

    String ident(int s){
    	String ident = ""; for(int i=0;i<s;i++) ident += "   ";
    	return ident;
    }
    
    void run(int s){
        System.out.println("executando raiz");
        for(int j=0;j<i;j++)
            cmdList[j].run(s+1);
    }

    String writeCode(int s){
        String str = "";
        str+="import java.util.Scanner;\n";
        str+="class MeuProg{// code by robot\n";
        str+="   public static void main(String args[]){\n";
        str+="      Scanner scan = new Scanner(System.in);\n";

        for(int j=0;j<i;j++)
            str+=cmdList[j].writeCode(2);

        str+="      scan.close();\n";
        str+="   }\n";
        str+="}\n\n";
        return str;
    };
}

class CmdInput extends Programa{
    String sc, var;
    CmdInput(Tipo tip, String var){
        this.var = var;
        switch (tip){
            case INT: sc = "Int()"; break;
            case STRING: sc = "Line()"; break;
            case FLOAT: sc = "Float()"; break;
            case BOOL: sc = "Boolean()"; break;
        }
    }

    void run(int s){
        System.out.println(ident(s) + "executando cmdInput");
    }

    String writeCode(int s){
        String ident = ident(s);
        String str = ident+var+" = scan.next"+sc+";\n";
        return str;
    };
}


class CmdPrint extends Programa {
    String exp, val;
    CmdPrint(String exp, Var a){
        this.exp = exp;
        this.val = a.str;
    }
    
    void run(int s){
        System.out.println(ident(s) + "executando print");
        System.out.println(ident(s) + "\t" + exp + " = " + val);
    }
    
    String writeCode(int s){
        String ident = ident(s);
        String str = ident+"System.out.println("+this.exp+");\n";
        return str;
    };
}

class CmdDecl extends Programa {
    String tip, exp;
    CmdDecl(Tipo tipo, String exp){
        switch (tipo){
            case INT: tip = "int"; break;
            case STRING: tip = "String"; break;
            case BOOL: tip = "boolean"; break;
            case FLOAT: tip = "float"; break;
        }
        this.exp = exp;
    }

    void run(int s){
        System.out.println(ident(s) + "executando declara");
    }

    String writeCode(int s){
        String ident = ident(s);
        String str = ident+this.tip+" "+this.exp+";\n";
        return str;
    };
}


class CmdAtrib extends Programa {
    String var, exp;
    CmdAtrib(String var, String exp){
        this.var = var;
        this.exp = exp;
    }

    void run(int s){
        System.out.println(ident(s) + "executando atrib");
    }

    String writeCode(int s){
        String ident = ident(s);
        String str = ident+this.var+" = "+this.exp+";\n";
        return str;
    };
}



class CmdWhile extends Programa {
    String exp;
    CmdWhile(String exp, int wu){
        if(wu==1) this.exp = "!("+exp+")";
        else  this.exp = exp;
    }

    void run(int s){
        System.out.println(ident(s) + "executando while");
        for(int j=0;j<i;j++)
            cmdList[j].run(s+1);
    }

    String writeCode(int s){
        String ident = ident(s);
        String str = ident+"while("+exp+"){\n";
        for(int j=0;j<i;j++)
            str+=cmdList[j].writeCode(s+1);
        str += ident+"}\n";
        return str;
    };
}

class CmdIf extends Programa {
    String exp;
    CmdIf(String exp){
        this.exp = exp;
    }

    void run(int s){
        System.out.println(ident(s) + "executando if: "+i);
        for(int j=0;j<i;j++)
            cmdList[j].run(s+1);
    }

    String writeCode(int s){
        String ident = ident(s);
        String str = ident+"if("+exp+"){\n";
        for(int j=0;j<i;j++)
            str+=cmdList[j].writeCode(s+1);
        str += ident+"}\n";
        return str;
    };
}

class CmdElse extends Programa {
    CmdElse(){
    }

    void run(int s){
        System.out.println(ident(s) + "executando else");
        for(int j=0;j<i;j++)
            cmdList[j].run(s+1);
    }

    String writeCode(int s){
        String ident = ident(s);
        String str = ident+"else{\n";
        for(int j=0;j<i;j++)
            str+=cmdList[j].writeCode(s+1);
        str += ident+"}\n";
        return str;
    };
}

