// Socket Server

#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#include <assert.h>



bool ExtractStringValues(char* szBuffer, char* szMACAddress, char* szServiceFilename);



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

	int nPortNumber = 0;

	if (argc !=3)
	{
		::fprintf(stdout, "ERROR: Insufficient number of parameters!\n");
		::fprintf(stdout, "Usage:\n");
		::fprintf(stdout, "server -pn <PortNumber>\n");
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
			::fprintf(stderr, "Invalid switch!\n");
			return -1;
		}
	}

	::fprintf(stdout, "INFO: Server started.\n");



	//
	// Create the socket
	//
	
	// create the socket
	::fprintf(stdout, "INFO: Opening the socket...\n");
	int	iSockDscrptr = ::socket(AF_INET, SOCK_STREAM, 0);
    if (iSockDscrptr < 0) 
	{
        ::perror("socket");
        ::exit(-1);
    }

	//
	// Bind to the socket
	//

	// create the address of the server.
    struct sockaddr_in socketAddress;
    ::memset(&socketAddress, 0, sizeof(struct sockaddr_in));
    socketAddress.sin_family = AF_INET;
    socketAddress.sin_port = ::htons(nPortNumber);	// htons is used for 'network byte order'
	
	// use the wildcard address.
    int iNetworkAddr = INADDR_ANY;
    ::memcpy(&socketAddress.sin_addr, &iNetworkAddr, sizeof(long));

	 
	// bind the socket to the address.
	int iAddressLength = sizeof(struct sockaddr_in);
	int iRetCode = ::bind(iSockDscrptr, (struct sockaddr*)&socketAddress, iAddressLength);
	if (iRetCode == -1)
	{
        ::perror("bind");
        exit(-1);
	}
	::fprintf(stdout, "INFO: Socket successfully opened.\n");



	//
	// Enter listening mode...
	//
	
	// listen for connections - note that the 'backlog' parameter is set to 5
	iRetCode = ::listen(iSockDscrptr, 5);
    if (iRetCode < 0) 
	{					
        ::perror("listen");
        ::exit(-1);
    }

	for ( ; ; )
	{
		// accept a connection
		::fprintf(stdout, "INFO: Listening for client connections...\n");
		int	iAcptdSockDscrptr = ::accept(iSockDscrptr, (struct sockaddr*)&socketAddress, (socklen_t*)&iAddressLength);
		if (iAcptdSockDscrptr < 0) 
		{
			::perror("accept");
			::exit(-1);
		}
		
		::fprintf(stdout, "INFO: Client connection accepted.\n");

    
		char szBuffer[1024];
		::memset(szBuffer, 0, sizeof(szBuffer));

		int iReceiveSize = 0;
		do
		{
			// read request from socket client
			iReceiveSize = ::recv(iAcptdSockDscrptr, szBuffer, sizeof(szBuffer), 0);
			if (iReceiveSize > 0)
			{
				// string terminate the buffer
				szBuffer[iReceiveSize] = '\0';

				::fprintf(stdout, "INFO: Msg from client received.\n");

				// extract the values we're expecting
				char szMACAddress[17 + 1];
				char szServiceFilename[255 + 1];
				bool IsOkay = ExtractStringValues(szBuffer, szMACAddress, szServiceFilename);

	
				// acknowledge receipt
				if (IsOkay)
				{
					// print what we have
					::fprintf(stdout, "\t[MACAddress: %s] [Service Filename: %s]\n", szMACAddress, szServiceFilename);

					// report success
					::strcpy(szBuffer, "0");
				}
				else
				{
					// report failure
					::strcpy(szBuffer, "1");
				}
				
				::fprintf(stdout, "INFO: Sending response...\n");
				int iSendSize  = ::send(iAcptdSockDscrptr, szBuffer, ::strlen(szBuffer), 0);
				if (iSendSize < 0)
				{
					::perror("send");
					::exit(-1);
				}
				::fprintf(stdout, "INFO: Response successfully sent.\n");

			}
		
		} while (iReceiveSize > 0);


		::fprintf(stdout, "INFO: Closing client connection...\n");
		::close(iAcptdSockDscrptr);
		::fprintf(stdout, "INFO: Client connection closed.\n");
	}
	
	// we'll never get here
	::fprintf(stdout, "INFO: Socket server closing ..... Goodbye!\n");
	::close(iSockDscrptr);

    ::exit(0);

} /* end-main */



bool ExtractStringValues(char* szBuffer, char* szMACAddress, char* szServiceFilename)
{
	assert((szBuffer != NULL) && (szMACAddress != NULL) && (szServiceFilename != NULL));
	
	// initialise the out params
	::strcpy(szMACAddress, "");
	::strcpy(szServiceFilename, "");

	// extract the strings
	char* pchToken = ::strtok(szBuffer, "|");

	if (pchToken == NULL)
	{
		return false;
	}

	// copy out the MACAddress
	::strcpy(szMACAddress, pchToken);
	
	
	pchToken = ::strtok(NULL, "|");
	if (pchToken == NULL)
	{
		return false;
	}

	// copy out the Service Filename
	::strcpy(szServiceFilename, pchToken);

	// return true if we have valid strings
	return ( (szMACAddress != NULL) && (szMACAddress[0] != NULL) && (szServiceFilename != NULL) && (szServiceFilename[0] != NULL) );
}

