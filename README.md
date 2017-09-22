# example-sockets
Example of a socket client and server for Unix/Linux/MacOS platforms (Network/Berkley Sockets). 

### Supported Platforms
The project will build and run on pretty much any Unix/Linux plaform, including Unix-derived platforms such as MacOS. I've built and run the demo on several platforms, most recently:

* Solaris SVR4
* MacOS
* Cygwin

Note: For Windows users, this is an example of Unix/Berkley Sockets. WinSock is the windows equivalent, which is very similar but not quite the same. Hence, should you want to build and run this on Windows, consider a suitable development environment such as MinGW or Cygwin. 

### Requirements
The project build needs:
* make
* gcc (2.9.5 onwards)

### Building the project
Use 'make'

    $./make

Depending on your environement, you may need to explicity include or explicity exclude the linker directives that pull in the required network libraries. There are a few versions of the Makefile in the directory so choose the one most suitable to your environment. 

The project creates two binaries, namely 'client' and 'server', representing either end of a client/server socket.

### Running the example
First, run the server, passing in a unique (unused) port number:

    $./server -pn 12346
    
The server will report that it's completed initialization and is listening for client connections.
    
Next, run the client, passing in the same port number:

    $./client -pn 12346

The client will connect to the server and send a structured message before exiting. The server will print the structured message received from the client, and then continue to listen for the next connection. 

Note: For best results, execute the client and server in separate terminals. 

Note that for the purposes of the demo, 'localhost' has been hardcoded as the target host. Ensure you run the client and server on the same host.
 
