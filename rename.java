import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.*;

public class rename{
//This class makes the words line by line, there is only one word in each line. 
 static public String[] getContents(File[] aFile) {
	  StringBuffer[] contents=new StringBuffer[aFile.length];
	  for(int i=0;i<aFile.length;i++)
	     contents[i]=new StringBuffer();
	  for(int i=0;i<aFile.length;i++){
	    contents[i]=new StringBuffer();
      try {
		    String tempchar=null; 
        BufferedReader reader=new BufferedReader(new FileReader(aFile[i]));
        while(( tempchar= reader.readLine()) != null){ 
		      contents[i].append(tempchar);
          contents[i].append("\n");
	      }  
	    }
      catch (IOException ex){
        ex.printStackTrace();
      }
    }
	  String[] cont=new String[aFile.length];
    for(int i=0;i<aFile.length;i++)  
	    cont[i]=contents[i].toString();
	  return cont;
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
    Writer[] output = new BufferedWriter[aFile.length];
	 for(int j=1;j<aFile.length;j++){
	      output[j]=new BufferedWriter(new FileWriter(Integer.toString(j-1)+".txt"));
    try {  
	  for(int i=0;i<aContents[j].length();i++){
      if(aContents[j].charAt(i) != '\n')
		    output[j].write( aContents[j].charAt(i) );
      else
        output[j].write("\n");
    }
	  }
    finally {
      output[j].close();
    }
	 }
  }
public static void main (String... aArguments) throws IOException {
String dir = new String("0originmenus");
		File directory = new File(dir);
		File[] testFile = directory.listFiles(); 
	 setContents(testFile, getContents(testFile));
  }
} 