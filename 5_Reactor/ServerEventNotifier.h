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

#ifndef SERVER_EVENT_NOTIFIER_H
#define SERVER_EVENT_NOTIFIER_H

/**************************************************************
* Specifies callbacks from a client to its server.
**************************************************************/

/**
* This function is invoked as a callback in case a disconnect on 
* TCP level is detected.
*/
typedef void (*OnClientClosedFunc)(void* server,
                                   void* closedClient);

typedef struct
{
   /* An instance of the server owning the client.
      This instance shall be passed as an argument to the callbacks. */
   void* server;

   /* Specifies a callback to be used by the client to 
      inform its server about a closed connection. */   
   OnClientClosedFunc onClientClosed;
   
} ServerEventNotifier;

#endif
