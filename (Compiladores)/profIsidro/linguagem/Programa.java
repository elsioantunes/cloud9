import java.util.ArrayList;

public class Programa{
    ArrayList<String>  varList;
    ArrayList<Comando> comandos;
    
    public Programa(){
        this.varList = new ArrayList<String>();
        this.comandos = new ArrayList<Comando>();
    }
    
    public void addVariable(String var){
        this.varList.add(var);
    }
    public void addCommand(Comando cmd){
        this.comandos.add(cmd);
    }
    
    
    public void run(){
        
    }
    public String writeCode(){
        StringBuilder str = new StringBuilder();
        str.append("<program>\n");
        str.append("<variableList>\n");
        for (String var: varList){
            str.append("<var id=").append(var).append("/>\n");
        }
        str.append("</variableList>\n");
        str.append("<commands>");
        for (Comando cmd: comandos){
            str.append(cmd.writeCode());
        }
        str.append("</coomands>\n");
        str.append("</program>");
        return str.toString();
    }
    
}