/*
 * LWSDK Header File
 *
 * LWGIZMO.H -- Viewport widgets
 *
 *$copyright$
 */
#ifndef LWSDK_GIZMO_H
#define LWSDK_GIZMO_H

#include <lwtypes.h>
#include <lwtool.h>
#include <lwcustobj.h>

#define LWGIZMO_VERSION 5

/* $wrapper: type=base, name=LWGizmoFuncs, prefix=gizmo$ */
typedef struct st_LWGizmoFuncs {
    void            (*done)     (LWInstance);
    void            (*draw)     (LWInstance, LWCustomObjAccess *);
    LWCStringUTF8   (*help)     (LWInstance, LWToolEvent *);
    int             (*dirty)    (LWInstance);
    int             (*count)    (LWInstance, LWToolEvent *);
    int             (*handle)   (LWInstance, LWToolEvent *, int i, LWDVector pos);
    /* $return: method=IGizmoFuncs:start, value=-1$ */
    int             (*start)    (LWInstance, LWToolEvent *);
    int             (*adjust)   (LWInstance, LWToolEvent *, int i);
    int             (*down)     (LWInstance, LWToolEvent *);
    void            (*move)     (LWInstance, LWToolEvent *);
    void            (*up)       (LWInstance, LWToolEvent *);
    void            (*event)    (LWInstance, int code);
    LWXPanelID      (*panel)    (LWInstance);
    int             (*end)      (LWInstance, LWToolEvent *, int i);
} LWGizmoFuncs;

typedef struct st_LWGizmo {
    LWInstance       instance;
    LWGizmoFuncs     *gizmo;
    const LWItemID* (*pickItems) (LWInstance, const LWItemID* drawitems, const unsigned int* drawparts);
} LWGizmo;


#endif
