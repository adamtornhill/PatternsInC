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

/*********************************************************************************
*
* The server side representation of a client sending diagnostic messages to the log.
*
* An instance of this client ADT is created as the server detects a connect request.
* Upon creation, the instance registers itself at the Reactor. The Reactor will notify 
* this client representation as an incoming diagnostics message is pending. 
* This client representation simply reads the message and prints it to stdout.
**********************************************************************************/

#include "DiagnosticsClient.h"
#include "DiagnosticsServer.h"
#include "EventHandler.h"
#include "Reactor.h"
#include "Error.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct DiagnosticsClient
{
   Handle clientSocket;
   EventHandler eventHandler;
   
   ServerEventNotifier eventNotifier;
}; 

#define MAX_MESSAGE_SIZE 1024

/************************************************************
* Function declarations.
************************************************************/

static Handle acceptClientConnection(int serverHandle);

static Handle getClientSocket(void* instance);

static void handleReadEvent(void* instance);

/************************************************************
* Implementation of the EventHandler interface.
************************************************************/

static Handle getClientSocket(void* instance)
{
   const DiagnosticsClientPtr client = instance;
   return client->clientSocket;
}

static void handleReadEvent(void* instance)
{
   const DiagnosticsClientPtr client = instance;
  
   char diagnosticMessage[MAX_MESSAGE_SIZE] = {0};
  
   const ssize_t receiveResult = recv(client->clientSocket, diagnosticMessage, sizeof diagnosticMessage, 0);
   
   if(0 < receiveResult) {
      /* In the real world, we would probably put a protocol on top of TCP/IP in 
      order to be able to restore the message out of the byte stream (it is no 
      guarantee that the complete message is received in one recv(). */
      
      (void) printf("Client: Diagnostics received - %s\n", diagnosticMessage);
   }
   else {
      client->eventNotifier.onClientClosed(client->eventNotifier.server, client);
   }
}

/************************************************************
* Implementation of the ADT functions of the client.
************************************************************/

/**
* Creates a representation of the client used to send diagnostic messages.
* The given handle must refer to a valid socket signalled for a pending connect request.
* The created client representation registers itself as the Reactor.
*/
DiagnosticsClientPtr createClient(Handle serverHandle, 
                                  const ServerEventNotifier* eventNotifier)
{
   DiagnosticsClientPtr client = malloc(sizeof *client);
   
   if(NULL != client) {
      client->clientSocket = acceptClientConnection(serverHandle);
      
      /* Successfully created -> register the client at the Reactor. */
      client->eventHandler.instance = client;
      client->eventHandler.getHandle = getClientSocket;
      client->eventHandler.handleEvent = handleReadEvent;

      Register(&client->eventHandler);
      
      assert(NULL != eventNotifier);
      client->eventNotifier = *eventNotifier;
   }
   
   return client;
}

/**
* Unregisters the given client at the Reactor and releases all associated resources.
* After completion of this function, the client-handle is invalid.
*/
void destroyClient(DiagnosticsClientPtr client)
{
   /* Before deleting the client we have to unregister at the Reactor. */
   Unregister(&client->eventHandler);
   
   (void) close(client->clientSocket);
   free(client);
}

/************************************************************
* Definition of the local utility function.
************************************************************/

static Handle acceptClientConnection(int serverHandle)
{
   struct sockaddr_in clientAddress = {0};
   
   socklen_t addressSize = sizeof clientAddress;

   const Handle clientHandle = accept(serverHandle, (struct sockaddr*) &clientAddress, &addressSize);
   
   if(0 > clientHandle) {
      /* NOTE: In the real world, this function should be more forgiving.
      For example, the client should be allowed to abort the connection request. */
      error("Failed to accept client connection");
   }
   
   (void) printf("Client: New connection created on IP-address %X\n", ntohl(clientAddress.sin_addr.s_addr));
   
   return clientHandle;
}

