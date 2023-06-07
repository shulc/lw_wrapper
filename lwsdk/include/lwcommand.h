/*
 * LWSDK Header File
 *
 * LWCOMMAND.H -- LightWave Layout command evaluation
 *
 * This header contains declarations for executing commands in Layout
 *
 *$copyright$
 */
#ifndef LWSDK_COMMAND_H
#define LWSDK_COMMAND_H

#ifdef __cplusplus
extern "C" {
#endif

#include <lwtypes.h>
#include <lwdyna.h>

#define LWCOMMANDINTERFACE_GLOBAL "LW Command Interface 2"

/* $wrapper: type=global, name = LWCommandInterface$ */
typedef struct st_LWCommandInterface
{
    void* data;

    int (*lookup)(void* data, LWCStringUTF8 cmd);
    int (*execute)(void* data, int tag, int argc, const DynaValue *argv, DynaValue *result);
    int (*evaluate)(void* data, LWCStringUTF8 cmdline);

} LWCommandInterface;

/* legacy (deprecated) */
#define LWCOMMANDFUNC_GLOBAL "LW Command Interface"
typedef int LWCommandFunc(LWCStringANSI cmd);

#ifdef __cplusplus
}
#endif

#endif

