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

/******************************************************************************
* A simulation of a diagnostics server.
*
* A client that wants to log a diagnostic connects to this server using TCP/IP.
* The server gets notified about a connecting client through the Reactor.
* Upon such a notification, the server creates a client representation.
*******************************************************************************/

#include "DiagnosticsServer.h"
#include "DiagnosticsClient.h"
#include "EventHandler.h"
#include "ServerEventNotifier.h"
#include "Reactor.h"

#include "Error.h"
#include "TcpServer.h"

#include <stdlib.h>
#include <stdio.h>

#define MAX_NO_OF_CLIENTS 10

struct DiagnosticsServer
{
   Handle listeningSocket;
   EventHandler eventHandler;
  
   /* All connected clients able to send diagnostics messages. */
   DiagnosticsClientPtr clients[MAX_NO_OF_CLIENTS];
};

/************************************************************
* Function declarations.
************************************************************/

static void deleteAllClients(DiagnosticsServerPtr server);

static int matchControlledClientByPointer(const DiagnosticsServerPtr server,
                                          const DiagnosticsClientPtr clientToMatch);

static int findFreeClientSlot(const DiagnosticsServerPtr server);

static int findMatchingClientSlot(const DiagnosticsServerPtr server,
                                  const DiagnosticsClientPtr client);

static Handle getServerSocket(void* instance);

static void handleConnectRequest(void* instance);

static void onClientClosed(void* server,
                           void* closedClient);

/************************************************************
* Implementation of the EventHandler interface.
************************************************************/

static Handle getServerSocket(void* instance)
{
   const DiagnosticsServerPtr server = instance;
   return server->listeningSocket;
}

static void handleConnectRequest(void* instance)
{
   DiagnosticsServerPtr server = instance;
  
   const int freeSlot = findFreeClientSlot(server);
   
   if(0 <= freeSlot) {
      /* Define a callback for events requiring the actions of the server (for example 
         a closed connection). */
      ServerEventNotifier eventNotifier = {0};
      eventNotifier.server = server;
      eventNotifier.onClientClosed = onClientClosed;
      
      server->clients[freeSlot] = createClient(server->listeningSocket, &eventNotifier);
        
      (void) printf("Server: Incoming connect request accepted\n");
   }
   else {
      (void) printf("Server: Not space for more clients\n");
   }
}

/************************************************************
* Implementation of the ServerEventNotifier interface. 
************************************************************/

/**
* This function is invoked as a callback from the client representation 
* in case it detects a disconnect on TCP level.
*/
static void onClientClosed(void* server,
                           void* closedClient)
{
   DiagnosticsServerPtr serverInstance = server;
   DiagnosticsClientPtr clientInstance = closedClient;
   
   const int clientSlot = findMatchingClientSlot(serverInstance, clientInstance);
   
   if(0 > clientSlot) {
      error("Phantom client detected");
   }
   
   destroyClient(clientInstance);
   
   serverInstance->clients[clientSlot] = NULL;
}

/************************************************************
* Implementation of the ADT functions of the server. 
************************************************************/

/**
* Creates a server listening for connect requests on the given port.
* The server registers itself at the Reactor upon creation.
*/
DiagnosticsServerPtr createServer(unsigned int tcpPort)
{
   DiagnosticsServerPtr newServer = malloc(sizeof *newServer);

   if(NULL != newServer) {
      int i = 0;
      
      for(i = 0; i < MAX_NO_OF_CLIENTS; ++i) {
         newServer->clients[i] = NULL;
      }
      
      newServer->listeningSocket = createServerSocket(tcpPort);

      /* Successfully created -> register the listening socket. */
      newServer->eventHandler.instance = newServer;
      newServer->eventHandler.getHandle = getServerSocket;
      newServer->eventHandler.handleEvent = handleConnectRequest;

      Register(&newServer->eventHandler);
   }
   
   return newServer;
}

/**
* Unregisters at the Reactor and deletes all connected clients 
* before the server itself is disposed.
* After completion of this function, the server-handle is invalid.
*/
void destroyServer(DiagnosticsServerPtr server)
{
   deleteAllClients(server);
   
   /* Before deleting the server we have to unregister at the Reactor. */
   Unregister(&server->eventHandler);

   disposeServerSocket(server->listeningSocket);
   free(server);
}

/************************************************************
* Definition of the local utility functions.
************************************************************/

static void deleteAllClients(DiagnosticsServerPtr server)
{
   int i = 0;
      
   for(i = 0; i < MAX_NO_OF_CLIENTS; ++i) {
      
      if(NULL != server->clients[i]) {
         destroyClient(server->clients[i]);
      }
   }
}

/**
* Returns the index where a client matching the given pointer is found.
* Returns -1 if no match was found. 
*/
static int matchControlledClientByPointer(const DiagnosticsServerPtr server,
                                          const DiagnosticsClientPtr clientToMatch)
{
   int clientSlot = -1;
   int slotFound = 0;
   int i = 0;
      
   for(i = 0; (i < MAX_NO_OF_CLIENTS) && (0 == slotFound); ++i) {
      
      if(clientToMatch == server->clients[i]) {
         clientSlot = i;
         slotFound = 1;
      }
   }
   
   return clientSlot;
}

static int findFreeClientSlot(const DiagnosticsServerPtr server)
{
   return matchControlledClientByPointer(server, NULL);
}

static int findMatchingClientSlot(const DiagnosticsServerPtr server,
                                  const DiagnosticsClientPtr client)
{  
   return matchControlledClientByPointer(server, client);
}
