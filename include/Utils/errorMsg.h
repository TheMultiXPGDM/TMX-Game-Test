#ifndef ERRORMSG_H
#define ERRORMSG_H

#include <stdio.h>
#ifdef WIN32
#include <windows.h> // for MessageBox
#endif

inline void errorMsg(const char* msg) {
    fprintf(stderr, "%s\n", msg);
#ifdef WIN32
    MessageBox(NULL, msg, "Error", MB_OK);
#endif
}

#endif // ERRORMSG_H