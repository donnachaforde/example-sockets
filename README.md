# example-sockets
Example of a socket client and server (Network/Berkley Sockets). 


### Building the project
Use 'make'

    $ make

Depending on your environement, you may need to explicity include or explicity exclude the linker directives that pull in the required network libraries. There are a few versions of the Makefile in the directory so choose the one most suitable to your environment. 

The project creates two binaries, namely 'client' and 'server', representing either end of a client/server socket.

### Running the example
First, run the server, passing in a unique (unused) port number:

    $ server -pn 12346
    
The server will report that it's completed initialization and is listening for client connections.
    
Next, run the client, passing in a unique (unused) port number:

    $ client -pn 12346

The server will print the structured message received from the client, and then continue to listen for the next connection. 

Note: For best results, execute the client and server in separate terminals. 

Note that for the purposes of the demo, 'localhost' has been hardcoded as the target host. 
 
