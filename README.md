# example-sockets
An example of a socket client and server for Unix/Linux/macOS platforms (i.e. Network/Berkeley Sockets). 

## Supported Platforms
The project will build and run on pretty much any Unix/Linux platform, including Unix-derived platforms such as macOS. I've built and run the demo on several platforms, most recently:


* macOS
* Ubuntu Linux
* Cygwin on Windows

Originally, the project was built on Solaris SVR4 and will still work on this platform. 

**Windows:** This project uses Unix/Berkeley Sockets, which are not natively available on Windows. To build and run on Windows, use a Unix-compatible environment — [WSL](https://learn.microsoft.com/en-us/windows/wsl/) (Windows Subsystem for Linux) is the recommended modern option; [Cygwin](https://www.cygwin.com/) also works. Note that WinSock, the native Windows socket API, has a similar but not identical interface.

## Requirements
The project build needs:
* make
* gcc (or clang)

## Building the project
Use `make` to build both client and server:
```
$ make
```
Or
```
$ make all
```



To build the client:
```
$ make client
```

To build the server:
```
$ make server
```

To perform a clean build:
```
$ make clean; make
```

Depending on your environment, you may need to explicitly include or explicitly exclude the linker directives that pull in the required network libraries. There are a few versions of the `makefile` so choose the one most suitable to your environment. 

The project creates two binaries, namely `client` and `server`, representing either end of a client/server socket.

## Running the example
First, run the server, passing in a unique (unused) port number:
```
$ ./server --port 12346
```

The server will report that it's completed initialization and is listening for client connections.
    
Next, run the client, passing in the same port number:
```
$ ./client --port 12346
```

The client will connect to the server and send a structured message before exiting. The server will print the structured message received from the client, and then continue to listen for the next connection. 

For the purpose of keeping the demo simple, `localhost` has been hardcoded as the target host. Ensure you run both the client and server on the same host.
 
