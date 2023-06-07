/*
 * LWSDK Header File
 *
 * LWGENERIC.H -- LightWave Generic Commands
 *
 *$copyright$
 */
#ifndef LWSDK_GENERIC_H
#define LWSDK_GENERIC_H

#include <lwtypes.h>
#include <lwdyna.h>

#define LWLAYOUTGENERIC_CLASS   "LayoutGeneric"
#define LWLAYOUTGENERIC_VERSION 7

/* $wrapper: type=access, name=LWLayoutGeneric$ */
typedef struct st_LWLayoutGeneric {
    int             (*saveScene) (LWCStringUTF8 file);
    int             (*loadScene) (LWCStringUTF8 file, LWCStringUTF8 name);

    void             *data;
    LWCommandCode   (*lookup)    (void *, LWCStringUTF8 cmdName);
    /* $argument: method=LWLayoutGeneric:execute, arg5=out:DynaValue:$ */
    int             (*execute)   (void *, LWCommandCode cmd, int argc, const DynaValue *argv, DynaValue *result);
    int             (*evaluate)  (void *, LWCStringUTF8 command);
    LWCStringUTF8   (*commandArguments)(void *);
    int             (*parsedArguments)  (void *, DynaValue **argv);

} LWLayoutGeneric;

#endif

