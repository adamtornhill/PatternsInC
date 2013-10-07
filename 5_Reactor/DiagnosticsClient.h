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

#ifndef DIAGNOSTICS_CLIENT_H
#define DIAGNOSTICS_CLIENT_H

#include "Handle.h"
#include "ServerEventNotifier.h"

/* An opaque, incomplete type for the FIRST-CLASS ADT. */
typedef struct DiagnosticsClient* DiagnosticsClientPtr;

/**
* Creates a representation of the client used to send diagnostic messages.
* The given handle must refer to a valid socket signalled for a pending connect request.
*/
DiagnosticsClientPtr createClient(Handle serverHandle, 
                                  const ServerEventNotifier* eventNotifier);

/**
* Unregisters the given client at the Reactor and releases all associated resources.
* After completion of this function, the client-handle is invalid.
*/
void destroyClient(DiagnosticsClientPtr client);

#endif
