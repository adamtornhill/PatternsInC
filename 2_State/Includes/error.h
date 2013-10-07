#ifndef ERROR_H
#define ERROR_H

/*
The error function is invoked as illegal state transitions are detected.
Obviously real-world error handling is more complex than that.
You typically want to return the condition to the calling client 
and let it make the decision.
The intent with error(reason) is just to put a compilable comment 
into the code.
*/
void error(const char* reason);

#endif
