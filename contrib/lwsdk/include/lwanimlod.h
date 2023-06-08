/*
 * LWSDK Header File
 *
 * LWANIMLOD.H -- LightWave Animation Loaders
 *
 *$copyright$
 */
#ifndef LWSDK_ANIMLOD_H
#define LWSDK_ANIMLOD_H

#include <lwimageio.h>
#include <lwhandler.h>

#define LWANIMLOADER_HCLASS "AnimLoaderHandler"
#define LWANIMLOADER_ICLASS "AnimLoaderInterface"
#define LWANIMLOADER_VERSION 5

/* $wrapper: type=access, name=LWAnimFrameAccess$ */
typedef struct st_LWAnimFrameAccess
{
    void *priv_data;
    LWImageProtocolID   (*begin) (void *, int type);
    void                (*done)  (void *, LWImageProtocolID);
} LWAnimFrameAccess;

/* $wrapper: type=handler, name=LWAnimLoaderHandler, context=const char *, accessor=LWANIMLOADER$ */
typedef struct st_LWAnimLoaderHandler {
    LWInstanceFuncs *inst;
    int             (*frameCount) (LWInstance);
    double          (*frameRate)  (LWInstance);
    double          (*aspect)     (LWInstance, int *w, int *h, double *pixAspect);
    void            (*evaluate)   (LWInstance, double, LWAnimFrameAccess *);
} LWAnimLoaderHandler;

#endif
