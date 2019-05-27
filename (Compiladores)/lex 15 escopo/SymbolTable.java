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
        
    int checkVarTipo(String id){
        Var a = findVar(id);
        if(a == null) erro("Var '"+id+"' precisa ser declarada previamente");
        a.inic = true;
        return a.tipo;
    }

    Var getVar(String id){
        Var a = findVar(id);
        if(a == null) erro("Var '"+id+"' non ecziste!");
        if(!a.inic) erro("Var '"+id+"' foi declarada mas não foi inicializada");
        a.exp = id;
        return a;
    }

    void setVar(String id, Var b){
        Var a = findVar(id);
        if(a == null) erro("variavel '"+id+"' não declarada");
        if(a.tipo != b.tipo) erro("tipo incompatível");
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
