public class ComandoRead extends Comando{
    private String id;
    
    public void setId(String id){
        this.id = id;
    }
    public String getId(){
        return this.id;
    }
    
    public void run(){
        
    }
    public String writeCode(){
        return "<read>"+id+"</read>\n";
    }
}