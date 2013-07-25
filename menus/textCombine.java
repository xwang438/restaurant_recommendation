import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.*;

public class textCombine{
//This class combines the texts into a big one from which we can select features. 
  static public String[] getContents(File[] aFile) {
	  StringBuffer[] contents=new StringBuffer[aFile.length];
	  for(int i=0;i<aFile.length;i++)
	    contents[i]=new StringBuffer();
	  for(int i=1;i<aFile.length;i++){
	    FileInputStream reader=null;
        try {
		      int tempchar=0;	
          reader =  new FileInputStream(aFile[i]);
          while(( tempchar= reader.read()) != -1){ 
		        contents[i].append((char)tempchar);
	        }  
	      }
        catch (IOException ex){
          ex.printStackTrace();
        }
    }
	  String[] cont=new String[aFile.length];
    for(int i=1;i<aFile.length;i++)  
	    cont[i]=contents[i].toString();
	  return cont;
  }

  static public String[] getFeature(File aFile1) {
   int j=0;
   try{
   BufferedReader reader=new BufferedReader(new FileReader(aFile1));
     try {
    String tempchar=null; 
      while(( tempchar= reader.readLine()) != null){
      j++;
    }
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
    BufferedReader reader1=new BufferedReader(new FileReader(aFile1));
    try {
      String tempchar=null; 
      while(( tempchar= reader1.readLine()) != null){ 
        if(tempchar.length()>0){
          contents[i].append(tempchar);
          i++;
        }  
      }
    }
    finally{
   reader1.close();
   }
  }
  catch (IOException ex){
    ex.printStackTrace();
  }
  String[] abc=new String[j];
  for(int n=0;n<j;n++)
    abc[n]=contents[n].toString();
  return abc; 
}
 static public void setContents(File[] aFile, String[] aContents)
 throws FileNotFoundException, IOException {
  for(int i=0;i<aFile.length;i++){  
	 if (aFile[i] == null) {
      throw new IllegalArgumentException("File should not be null.");
    }
    if (!aFile[i].exists()) {
      throw new FileNotFoundException ("File does not exist: " + aFile);
    }
    if (!aFile[i].isFile()) {
      throw new IllegalArgumentException("Should not be a directory: " + aFile);
    }
    if (!aFile[i].canWrite()) {
      throw new IllegalArgumentException("File cannot be written: " + aFile);
    }
   }
    //use buffering
    Writer output = new BufferedWriter(new FileWriter("menu.txt"));
    try {  
	 for(int j=1;j<aFile.length;j++){ 
		   output.write( aContents[j]);
			output.write("\n");
    }
	 }
    finally {
      output.close();
    }
	 }
public static void main (String... aArguments) throws IOException {
String dir = new String("menus");
		File directory = new File(dir);
		File[] testFile = directory.listFiles(); 
	 setContents(testFile, getContents(testFile));
}
} 