/*
 * LWSDK Header File
 *
 * LWCOMMANDPORT.H -- LightWave Command Port
 *
 * This header contains declarations for retrieving information
 * about the state of the application's Command Port
 *
 *$copyright$
 */
#ifndef LWSDK_COMMANDPORT_H
#define LWSDK_COMMANDPORT_H

#include <lwtypes.h>

#define LWCOMMANDPORT_GLOBAL "LW Command Port"

/* $wrapper: type=global, name=LWCommandPort$ */
typedef struct st_LWCommandPort
{
    int         (*currentPort)();       /* 0 = disabled, >0 = port in use */
    int         (*enable)(int port);    /* port range 1025 - 65535*/
    int         (*disable)();
} LWCommandPort;

#endif
