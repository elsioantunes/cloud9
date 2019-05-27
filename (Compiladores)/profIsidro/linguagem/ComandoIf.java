import java.util.ArrayList;

public class ComandoIf extends Comando{
    private ArrayList<Comando> commandList;
    private String             logicalExpr;
    
    public ComandoIf(){
        this.commandList = new ArrayList<Comando>();
    }
    public void setLogicalExpr(String expr){
        this.logicalExpr = expr;
    }
    public void addCommand(Comando comando){
        this.commandList.add(comando);
    }
    
    
    public void run(){
        
    }
    public String writeCode(){
        StringBuilder str = new StringBuilder();
        str.append("<if expr=\"").append(logicalExpr).append("\">\n");
        str.append("<commandList>\n");
        for(Comando c: commandList){
            str.append(c.writeCode());
        }
        str.append("</coomandList>\n");
        str.append("</if>\n");
        return str.toString();
    }
}