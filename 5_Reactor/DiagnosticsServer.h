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

#ifndef DIAGNOSTICS_SERVER_H
#define DIAGNOSTICS_SERVER_H

/* An opaque, incomplete type for the FIRST-CLASS ADT. */
typedef struct DiagnosticsServer* DiagnosticsServerPtr;

/**
* Creates a server listening for connect requests on the given port.
* The server registers itself at the Reactor upon creation.
*/
DiagnosticsServerPtr createServer(unsigned int tcpPort);

/**
* Unregisters at the Reactor and deletes all connected clients 
* before the server itself is disposed.
* After completion of this function, the server-handle is invalid.
*/
void destroyServer(DiagnosticsServerPtr server);

#endif
