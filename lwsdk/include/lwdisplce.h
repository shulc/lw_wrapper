/*
 * LWSDK Header File
 *
 * LWDISPLCE.H -- LightWave Vertex Displacements
 *
 *$copyright$
 */
#ifndef LWSDK_DISPLCE_H
#define LWSDK_DISPLCE_H

#include <lwrender.h>
#include <lwmeshes.h>

#define LWDISPLACEMENT_HCLASS   "DisplacementHandler"
#define LWDISPLACEMENT_ICLASS   "DisplacementInterface"
#define LWDISPLACEMENT_GCLASS   "DisplacementGizmo"
#define LWDISPLACEMENT_VERSION  6


/* $wrapper: type=access, name=LWDisplacementAccess$ */
typedef struct st_LWDisplacementAccess {
    LWDVector    oPos;
    LWDVector    source;
    LWPntID      point;
    LWMeshInfo  *info;
    LWDVector    wNorm;
} LWDisplacementAccess;

/* $wrapper: type=handler, name=LWDisplacementHandler, context=LWItemID, pythonuserext=(Displacement)$ */
typedef struct st_LWDisplacementHandler {
    LWInstanceFuncs  *inst;
    LWItemFuncs  *item;
    LWRenderFuncs    *rend;
    void            (*evaluate) (LWInstance, LWDisplacementAccess *);
    unsigned int    (*flags) (LWInstance);
} LWDisplacementHandler;

#define LWDMF_WORLD         (1<<0)
#define LWDMF_BEFOREBONES   (1<<1)
#define LWDMF_AFTERMORPH    (1<<2)
#define LWDMF_NEED_NORMALS  (1<<3)
#define LWDMF_LAST          (1<<4)

#endif

