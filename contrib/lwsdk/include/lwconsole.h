/*
 * LWSDK Header File
 *
 * LWCONSOLE.H -- LightWave Console Access
 *
 *$copyright$
 */
#ifndef LWSDK_PCORECONSOLE_H
#define LWSDK_PCORECONSOLE_H

#include <lwtypes.h>

#define LWPCORECONSOLE_GLOBAL    "LW PCore Console"

/* $wrapper: type=global, name=LWPCoreConsole$ */
typedef struct st_LWPCoreConsole
{
    void        (*info)(LWCStringUTF8 message);
    void        (*error)(LWCStringUTF8 message);
    void        (*clear)();
    void        (*show)();
    void        (*hide)();
    int         (*visible)();
} LWPCoreConsole;

#endif
