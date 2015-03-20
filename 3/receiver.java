//File Receiver.java 
import java.io.*;
import java.net.*;

class Receiver
{
  public static void main(String argv[]) throws IOException {
   System.out.println("Starting up Receiver");
   try 
    {
      //Create the Server Socket
      ServerSocket serverSocket=new ServerSocket(40064); //Port 40040 is open on munro    
      //Listen for a connection request - program waits for an incoming connection
      Socket socket = serverSocket.accept();
      System.out.println("We have a connection!!!");

      //Create data input and output streams based on client socket info
      BufferedReader remoteInput=new BufferedReader(new InputStreamReader(socket.getInputStream()));
     //The following could be used to create a synchronized conversation 
      BufferedReader localInput=new BufferedReader(new InputStreamReader(System.in));  //could have used Scanner - just did this to make both inputs look alike
      
      PrintWriter    remoteOutput=new PrintWriter(socket.getOutputStream(),true);
       

      String message,getMessage;
      while(true)
       {
         message=remoteInput.readLine();
         System.out.println("Msg from client: "+message);
          System.out.println("Enter Reply from Server: ");
	  getMessage = localInput.readLine();
          System.out.println("sending the message: "+getMessage);
		//sender.send
          remoteOutput.println(getMessage);
         }
      } catch(IOException ex) { ex.printStackTrace(); }
   }
 }
