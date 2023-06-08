/*
 * LWSDK Header File
 *
 * LWHUB.H -- LightWave Hub
 *
 *$copyright$
 */
#ifndef LWSDK_HUB_H
#define LWSDK_HUB_H

#ifdef __cplusplus
extern "C" {
#endif

#include <lwtypes.h>

#define LWHUB_GLOBAL "LW Hub"

/* $wrapper: type=global, name=LWHub$ */
typedef struct st_LWHub {
    int           (*isRunning    )();                                     /*!< Checks to see of the hub is running.     */
    unsigned int  (*countOfAssets)( LWCStringUTF8 type );                 /*!< Count of assets of type.                 */
    LWCStringUTF8 (*nameOfAsset  )( LWCStringUTF8 type, unsigned int i ); /*!< Name  of assets of type at N'th position.*/
} LWHub;

#ifdef __cplusplus
}
#endif

#endif
