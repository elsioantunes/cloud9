import java.io.*;
class OpenFile{
    public BufferedReader br;
    public int lin, col;
    public char c;
    
    OpenFile(String filename){
        lin = 1; col = 0;
        try{
            FileReader f = new FileReader(filename);
            br = new BufferedReader(f);
        }catch(IOException e){
            System.err.println("[OpenFile Diz:"+e.getMessage()+"]");
        }
    }
    
    public void getChar(){
        try{
            col++;
            c = (char) br.read();
            if(c=='\n'){col=0; lin++;}
        }
        catch(IOException e){c = '\uffff';}
    }
}

