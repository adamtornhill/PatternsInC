/********************************************************************
* (C) Adam Petersen 2005
*
* This code accompanies the article "Patterns in C, part 5: REACTOR".
* The article is available as PDF from www.adampetersen.se
*
* The code is intended as a illustration of the Reactor at work and 
* is not suitable for use in production code (in order to keep this 
* example as short as possible, the error handling has been strongly 
* simplified).
*
********************************************************************/

/********************************************************
* A wrapper around the POSIX Network API for IPv4.
********************************************************/

#include "TcpServer.h"

#include "Error.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int createServerSocket(unsigned int tcpPort)
{
   struct sockaddr_in address = {0};
   
   const int serverHandle = socket(PF_INET, SOCK_STREAM, 0);
   
   if(serverHandle < 0) {
      error("Failed to create server socket");
   }
   
   address.sin_family = AF_INET;
   address.sin_port = htons(tcpPort);
   address.sin_addr.s_addr = htonl(INADDR_ANY);
   
   if(bind(serverHandle, (struct sockaddr*) &address, sizeof address) != 0) {
      error("bind() failed");
   }

   if(listen(serverHandle, SOMAXCONN) != 0) {
      error("listen() failed");
   }
   
   return serverHandle;
}

void disposeServerSocket(int serverSocket)
{
   (void) close(serverSocket);
}

