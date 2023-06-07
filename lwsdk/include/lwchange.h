/*
 * LWSDK Header File
 *
 * LWCHANGE.H -- LightWave change.
 *
 *$copyright$
 */
#ifndef LWSDK_CHANGE_H
#define LWSDK_CHANGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <lwrender.h>

#define LWCHANGEFUNCS_GLOBAL    "Change Functions"

/* $wrapper: type=global, name=LWChangeFuncs$ */

typedef struct st_LWChangeFuncs {
    int (*getObjectChangedState)( LWItemID );   /* Gets object save state. */
    int (*getSceneChangedState )( void );       /* Gets scene  save state. */
    int (*anyChangesAtAll      )( void );       /* Checks for any changes at all in scene. */
} LWChangeFuncs;

#ifdef __cplusplus
}
#endif

#endif
