public class ComandoWrite extends Comando{
    public static final int TYPE_TEXT = 1;
    public static final int TYPE_ID   = 2;
    
    private String content;
    private int    type;
    
    public void setContent(String content){
        this.content = content;
    }
    public void setType(int type){
        this.type = type;
    }
    public void run(){
        
    }
    public String writeCode(){
        return "<write>\n" +
            "<type>"+type+"</type>\n"+
            "<content>"+content+"</content>\n"+
            "</write>\n" ;
    }
}