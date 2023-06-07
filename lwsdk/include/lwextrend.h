/*
 * LWSDK Header File
 *
 * LWEXTRENDERER.H -- LightWave Renderer
 *
 *$copyright$
 */
#ifndef LWSDK_EXTRENDERER_H
#define LWSDK_EXTRENDERER_H

#include <lwtypes.h>
#include <lwserver.h>
#include <lwgeneric.h>
#include <lwhandler.h>
#include <lwrender.h>

#define LWEXTRENDERER_HCLASS  "ExtRendererHandler"
#define LWEXTRENDERER_VERSION 3

typedef int EXTRENDERERIMAGE( void *user, int frame, int eye, LWPixmapID displayimage, LWCStringUTF8 name, LWCStringUTF8 buffer );

/* $wrapper: type=handler, name=LWExtRendererHandler$ */
typedef struct st_LWExtRendererHandler {
    LWInstanceFuncs *inst;
    LWItemFuncs     *item;
    int            (*options)( LWInstance );
    int            (*render )( LWInstance, int first_frame, int last_frame, int frame_step, EXTRENDERERIMAGE *render_image, void *user, int render_mode );
} LWExtRendererHandler;

#endif
