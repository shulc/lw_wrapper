/*
 * LWSDK Header File
 *
 * LWFRAMBUF.H -- LightWave Framebuffers
 *
 *$copyright$
 */
#ifndef LWSDK_FRAMBUF_H
#define LWSDK_FRAMBUF_H

#include <lwtypes.h>
#include <lwrender.h>

#define LWFRAMEBUFFER_HCLASS    "FrameBufferHandler"
#define LWFRAMEBUFFER_ICLASS    "FrameBufferInterface"
#define LWFRAMEBUFFER_GCLASS    "FrameBufferGizmo"
#define LWFRAMEBUFFER_VERSION   7

/* $wrapper: type=handler, name=LWFrameBufferHandler$ */
typedef struct st_LWFrameBufferHandler {
    LWInstanceFuncs *inst;
    LWItemFuncs     *item;
    int              type;
    LWError         (*open) (LWInstance, int w, int h);
    void            (*close) (LWInstance);
    LWError         (*begin) (LWInstance);
    LWError         (*write) (LWInstance, const void *R, const void *G, const void *B, const void *alpha);
    void            (*pause) (LWInstance, LWCStringUTF8 display_name);
    LWPixmapID      (*getPixelMap) (LWInstance);
} LWFrameBufferHandler;

#define LWFBT_UBYTE 0
#define LWFBT_FLOAT 1

#endif
