/*
 * LWSDK Header File
 *
 * LWLICENSEGLOBAL.H -- LightWave license global.
 *
 * This header contains the basic declarations need to define the
 * simplest LightWave plug-in server.
 *
 *$copyright$
 */
#ifndef LWSDK_LICENSEGLOBAL_H
#define LWSDK_LICENSEGLOBAL_H

#include <lwtypes.h>

#define LWLICENSE_GLOBAL "License Global"

/* This uses the new dongle-less license key .                  */
/* For plugins that require a special license key to startup.   */
/* This allows a plugin to get the name of the licensed plugin, */
/* and the version of LightWave it was intended to run in.      */

/* $wrapper: type=global, name=LWPluginLicenseGlobal, accessor=LWLICENSE_GLOBAL$ */

typedef struct st_LWPluginLicenseGlobal {
    int                        (*pluginValid      )( LWCStringASCII, LWCStringASCII );  /* Checks to see if a plugin is valid, by name and version.  */
    struct st_lwPluginLicense *(*nextPluginLicense)( struct st_lwPluginLicense * );     /* Return next global in list, NULL is the head of the list. */
    LWCStringASCII             (*pluginName       )( struct st_lwPluginLicense * );     /* Returns the name of the licensed plugin. */
    LWCStringASCII             (*lwVersion        )( struct st_lwPluginLicense * );     /* Returns the version of the license key.  */
    unsigned int               (*hardwareLock     )( struct st_lwPluginLicense * );     /* Returns the hardware lock.               */
} LWPluginLicenseGlobal;

#endif
