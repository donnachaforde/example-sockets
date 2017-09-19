// Socket client

#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>



/******************************************************************************\
 ******************************************************************************
 ******************************************************************************
 *********************************    MAIN    *********************************
 ******************************************************************************
 ******************************************************************************
\******************************************************************************/

int main(int argc, char* argv[])
{
	//
	// First, parse command args - get the port number
	//

	// rudimentary form of arg checking
	int nPortNumber = 0;
	if (argc != 3)
	{
		::fprintf(stdout, "ERROR: Insufficient number of parameters!\n");
		::fprintf(stdout, "Usage:\n");
		::fprintf(stdout, "client -pn <PortNumber>\n");
		return -1;
	}
	else
	{
		if (::strcmp(argv[1], "-pn") == 0)
		{
			nPortNumber = ::atoi(argv[2]);
		}
		else
		{
			::fprintf(stdout, "ERROR: Invalid switch!\n");
			return -1;
		}
	}

	::fprintf(stdout, "INFO: Client started.\n");


	//
	// Resolve our host's network address
	//

	::fprintf(stdout, "INFO: Resolving Host='localhost'...\n");

	char* szHostname = "localhost";
	struct hostent* pHostInfo = ::gethostbyname(szHostname);

	if (pHostInfo == NULL) 
	{
        ::fprintf(stderr, "ERROR: Unknown host=%s.\n", szHostname);
        ::exit(1);
    }

	::fprintf(stdout, "INFO: Host='localhost' successfully resolved.\n");

	 

	//
	// Create the socket & connect to it
	//

	// create the socket
	::fprintf(stdout, "INFO: Opening the socket...\n");
	int	iSockDscrptr = ::socket(AF_INET, SOCK_STREAM, 0);

    if (iSockDscrptr < 0) 
	{
        ::perror("socket");
		::exit(1);
    }


	// specify the address of the server
	struct sockaddr_in socketAddress;
    ::memset(&socketAddress, 0, sizeof(struct sockaddr_in));
    socketAddress.sin_family = AF_INET;
    socketAddress.sin_port = ::htons(nPortNumber);	// htons is used for 'network byte order'
    ::memcpy(&socketAddress.sin_addr, pHostInfo->h_addr_list[0], pHostInfo->h_length);

	// make the conection
	int iRetCode = ::connect(iSockDscrptr, (struct sockaddr *) &socketAddress, sizeof(struct sockaddr_in));
    if (iRetCode < 0) 
	{
        ::perror("connect");
        ::exit(1);
    }

	::fprintf(stdout, "INFO: Socket successfully opened.\n");


	//
	// Send a request
	//

	// send something to the server
	::fprintf(stdout, "INFO: Sending msg to the server...\n");
	char* szMessage = "12345678901234567|servicefilename.ext";
	iRetCode = ::send(iSockDscrptr, szMessage, strlen(szMessage), 0);
	
	if (iRetCode < 0) 
	{
		::perror("send");
		::exit(1);
	}
	::fprintf(stdout, "INFO: Msg successfully sent to server.");


	//
	// Receive a response
	//

	::fprintf(stdout, "INFO: Checking for a response from the server...\n");
	char szBuffer[1024];
	iRetCode = ::recv(iSockDscrptr, szBuffer, sizeof(szBuffer), 0);

	if (iRetCode > 0)
	{
		// extract the return code
		char szServerRetCode[2];
		szServerRetCode[0] = szBuffer[0];
		szServerRetCode[1] = '\0';
		int iServerRetCode = ::atoi(szServerRetCode);

		if (iServerRetCode == 0)
		{
			::fprintf(stdout, "INFO: Response from server successfully received.\n");
		}
		else if (iServerRetCode == 1)
		{
			::fprintf(stderr, "ERROR: Call failed due to invalid data.\n");
		}
		else 
		{
			::fprintf(stdout, "Opps, it didn't seem to work\n");
			::fprintf(stderr, "ERROR: Failed to receive msg from server, Error Code = %d\n", iServerRetCode);
		}
	}
	else
	{
		::fprintf(stderr, "ERROR: Nothing received back from the server.\n");
	}


	//
	// Close the socket 
	//

	::fprintf(stdout, "INFO: Closing socket...\n");
	::close(iSockDscrptr);
	::fprintf(stdout, "INFO: Socket successfully closed.\n");

	return 0;
}


