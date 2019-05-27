class Programa{
    public Programa[] cmdList;int i;
    Programa(){cmdList = new Programa[300];i = 0;}
    public void push(Programa cmd){cmdList[i++] = cmd;}

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
        str+="}\n\n\n/*";
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
    String writeCode(int s){
        String ident = ""; for(int i=0;i<s;i++) ident += "   ";
        String str = ident+var+" = scan.next"+sc+";\n";
        return str;
    };
}


class CmdPrint extends Programa {
    String exp;
    CmdPrint(String exp){
        this.exp = exp;
    }
    String writeCode(int s){
        String ident = ""; for(int i=0;i<s;i++) ident += "   ";
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
    String writeCode(int s){
        String ident = ""; for(int i=0;i<s;i++) ident += "   ";
        String str = ident+this.tip+" "+this.exp+"; // ("+s+")\n";
        return str;
    };
}


class CmdAtrib extends Programa {
    String var, exp;
    CmdAtrib(String var, String exp){
        this.var = var;
        this.exp = exp;
    }
    String writeCode(int s){
        String ident = ""; for(int i=0;i<s;i++) ident += "   ";
        String str = ident+this.var+" = "+this.exp+/*debug*/"; //("+s+")\n";
        return str;
    };
}



class CmdWhile extends Programa {
    String exp;
    CmdWhile(String exp){
        this.exp = exp;
    }
    String writeCode(int s){
        String ident = ""; for(int i=0;i<s;i++) ident += "   ";
        String str = ident+"while("+exp+"){\n";
        for(int j=0;j<i;j++)
            str+=cmdList[j].writeCode(s+1);
        str += ident+"}\n";
        return str;
    };
}

