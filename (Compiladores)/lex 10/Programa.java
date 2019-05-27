class Programa{
    Comando[] cmdList;
    int i;
    Programa(){cmdList = new Comando[300];i = 0;}
    void push(Comando cmd){cmdList[i++] = cmd;}

    void writeCode(){
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
        System.out.println(str);
    };
}






class CmdInput extends Comando {
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


class CmdPrint extends Comando {
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

class CmdDecl extends Comando {
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


class CmdAtrib extends Comando {
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

class CmdIf extends Comando {
    String exp;
    CmdIf(String exp){
        cmdList = new Comando[300];
        i = 0;
        this.exp = exp;
    }
    String writeCode(int s){
        String ident = ""; for(int i=0;i<s;i++) ident += "   ";
        
        String str = ident+"if("+exp+"){\n";
        for(int j=0;j<i;j++)
            str+=cmdList[j].writeCode(s+1);
        str += ident+"}\n";
        return str;
    };
}

class CmdElse extends Comando {
    Comando[] cmdList;
    int i;
    CmdElse(){
        cmdList = new Comando[300];
        i = 0;
    }
    void push(Comando cmd){
        cmdList[i++] = cmd;
    }
    String writeCode(int s){
        String ident = ""; for(int i=0;i<s;i++) ident += "   ";
        
        String str = ident+"else{\n";
        for(int j=0;j<i;j++)
            str+=cmdList[j].writeCode(s+1);
        str += ident+"}\n";
        return str;
    };
}



class CmdWhile extends Comando {
    Comando[] cmdList;
    int i;
    String exp;
    CmdWhile(String exp){
        cmdList = new Comando[300];
        i = 0;
        this.exp = exp;
    }
    
    void push(Comando cmd){
        cmdList[i++] = cmd;
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

class Comando{
    String id;
    Comando[] cmdList;
    int i;
    void push(Comando cmd){
        cmdList[i++] = cmd;
    }
    String writeCode(int s){return "";}
}
