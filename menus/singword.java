import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.*;
import java.io.DataInput;
import java.io.Reader;

public class singword{
//This class make the word to be single. No duplicate words
 static public String[] getContents(File aFile) {
	 int j=0;
	 try{
	 BufferedReader reader=new BufferedReader(new FileReader(aFile));
    try {
		String tempchar=null;	
      while(( tempchar= reader.readLine()) != null){
			j++;
		}
		System.out.println(j);
	 }
	 finally{
	 reader.close();
	 }
	 }
	 catch (IOException ex){
      ex.printStackTrace();
    }
	 StringBuffer[] contents=new StringBuffer[j];
	 for(int i=0;i<j;i++)
	    contents[i]=new StringBuffer();
    int i=0;
	 try{
	 BufferedReader reader1=new BufferedReader(new FileReader(aFile));
    try {
		String tempchar=null;	
      while(( tempchar= reader1.readLine()) != null){ 
			contents[i].append(tempchar);
			i++;
			}
			System.out.println(i);
	 }
	 finally{
	 reader1.close();
	 }
	 }
    catch (IOException ex){
      ex.printStackTrace();
    }
	 String[] newContents=new String[j];
	 for(int n=0;n<j;n++)
	 newContents[n]=contents[n].toString();
	 for(int n=0;n<j;n++){
	    for(int k=n+1;k<j;k++){
		   if(newContents[k].equals(newContents[n])){
			   newContents[k]="";
	      }
	    }
	 }
    return newContents;
  }
  
  static public void setContents(File aFile, String[] aContents)
 throws FileNotFoundException, IOException {
 
	 if (aFile == null) {
      throw new IllegalArgumentException("File should not be null.");
    }
    if (!aFile.exists()) {
      throw new FileNotFoundException ("File does not exist: " + aFile);
    }
    if (!aFile.isFile()) {
      throw new IllegalArgumentException("Should not be a directory: " + aFile);
    }
    if (!aFile.canWrite()) {
      throw new IllegalArgumentException("File cannot be written: " + aFile);
    }
   
    //use buffering
    Writer output = new BufferedWriter(new FileWriter("menu.txt"));
    try {  
	   for(int i=0;i<aContents.length;i++){
		 if(aContents[i].length()>0){
			output.write( aContents[i]);
			output.write("\n");
			}
    }
	 }
    finally {
      output.close();
    }
 }

 public static void main (String... aArguments) throws IOException {

	 setContents(new File("menu.txt"),getContents(new File("menu.txt")));
  }
} 