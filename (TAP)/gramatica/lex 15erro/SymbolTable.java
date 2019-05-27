import java.util.ArrayList;
class SymbolTable{
    java.util.HashMap <String, Var> symbolTable;
    java.util.HashMap  arraySymbolos[];
    int contadorPilha;
    
    SymbolTable(){
        arraySymbolos = new java.util.HashMap[10];
        contadorPilha = 0;
    }
    
    void acquire(){
        symbolTable = new java.util.HashMap <String, Var>();
        arraySymbolos[contadorPilha++] = symbolTable;
    }
    void release(){
        symbolTable = arraySymbolos[--contadorPilha];
    }
    
    void createVar(int tipo, String id){
        symbolTable.put(id, new Var(tipo, id));
    }
    
    Var findVar(String id){
        int pilhaAtual = contadorPilha;
        Var a = null;
        while(a == null && pilhaAtual > 0){
            symbolTable = arraySymbolos[--pilhaAtual];
            a = symbolTable.get(id);
        }
        symbolTable = arraySymbolos[contadorPilha-1];
        return a;
    }
    int checkVarTipo(String id){ return checkVarTipo(id,0,0);}
    int checkVarTipo(String id, int lin,int col){
        Var a = findVar(id);
        if(a == null) Parser.addErros(404,1,"Var '"+id+"' precisa ser declarada previamente",lin,col);
        a.inic = true; // isso causava um erro no teste de entrada. não causa mais
        //erro("Var '"+id+"' precisa ser declarada previamente");
        return a.tipo;
    }
    Var getVar(String id){ return getVar(id,0,0); }
    Var getVar(String id, int lin,int col){
        Var a = findVar(id);
        if(a == null) Parser.addErros(404,1,"Var '"+id+"' non ecziste",lin,col);
                                //erro("Var '"+id+"' non ecziste!");
        if(!a.inic) Parser.addErros(407,1,"Var '"+id+"' foi declarada mas não foi inicializada",lin,col);
                                //erro("Var '"+id+"' foi declarada mas não foi inicializada");
        a.exp = id; 
        return a;
    }
    void setVar(String id, Var b){ setVar(id,b,0,0); }
    void setVar(String id, Var b, int lin,int col){
        Var a = findVar(id);
        if(a == null) Parser.addErros(404,1,"Var '"+id+"' não declarada",lin,col);
                                //erro("variavel '"+id+"' não declarada");
        if(a.tipo != b.tipo) Parser.addErros(507,1,"Var '"+id+"' tipo incompatível",lin,col);
                                //erro("tipo incompatível");
        a.id = b.id;
        a.str = b.str;
        a.exp = b.exp;
        a.inic = true;
    }
    
    void erro(String str){
        System.out.println(str);
        System.exit(666);
    }
}


class Var{
    String str, id, exp, res;
    boolean inic;
    int tipo;
    
    Var(){};
    Var(int tipo, String id){
        this.id = id;
        this.tipo = tipo;
        this.inic = false;
        this.str = "0";
        this.exp = id;
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
