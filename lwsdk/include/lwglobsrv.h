/*
 * LWSDK Header File
 *
 * LWGLOBSERV.H -- LightWave Global Server
 *
 * This header contains declarations necessary to define a "Global"
 * class server.
 *
 *$copyright$
 */
#ifndef LWSDK_GLOBSERV_H
#define LWSDK_GLOBSERV_H

#include <lwtypes.h>

#define LWGLOBALSERVICE_CLASS   "Global"
#define LWGLOBALSERVICE_VERSION 1

typedef struct st_LWGlobalService {
    LWCStringASCII  id;
    void           *data;
} LWGlobalService;

#endif

