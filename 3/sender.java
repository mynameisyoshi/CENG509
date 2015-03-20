//File Sender.java
import java.io.*;
import java.net.*;

class Sender extends Socket
{
    Socket socket=null;
    PrintWriter out=null;
    BufferedReader in = null;

    public Sender(String machineName,int port)
    {
	try {
	    socket = new Socket(InetAddress.getByName(machineName), port);
            out = new PrintWriter(socket.getOutputStream(), true);
	    in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
	} catch (IOException e) {
	    System.out.println("Could not send to " + machineName + ":"+ port);
	    e.printStackTrace();
	    System.exit(-1);
	}
         catch(Exception e)
         {
           System.out.println("Generic exception");
           e.printStackTrace();
         }

    }


   void receive( )
  {try{
    String message;
    message = in.readLine();
    System.out.println("Msg from server: "+message);
    }catch (IOException e){e.printStackTrace();}
  }
    void send(String msg)
    {
	out.println(msg);
    }

    public static void main(String argv[]) throws IOException
    {
	String message;
        if(argv.length<2) 
        {
         System.err.println("Useage:  Sender hostname port");
         System.exit(-1);
         }

	BufferedReader input=new BufferedReader(new InputStreamReader(System.in));
        System.out.println("Remote host: " + argv[0] + " Port: " + argv[1]);
	Sender sender=new Sender(argv[0], Integer.parseInt(argv[1]));
	while(true)
	{
	    System.out.print("Enter msg: ");
	    message=input.readLine();
	    sender.send(message); 
            sender.receive();
	}
    }
}
