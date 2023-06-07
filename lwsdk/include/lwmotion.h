/*
 * LWSDK Header File
 *
 * LWMOTION.H -- LightWave Item Motions
 *
 *$copyright$
 */
#ifndef LWSDK_MOTION_H
#define LWSDK_MOTION_H

#include <lwrender.h>

#define LWITEMMOTION_HCLASS "ItemMotionHandler"
#define LWITEMMOTION_ICLASS "ItemMotionInterface"
#define LWITEMMOTION_GCLASS "ItemMotionGizmo"
#define LWITEMMOTION_VERSION 6


/* $wrapper: type=access, name=LWItemMotionAccess$ */
typedef struct st_LWItemMotionAccess {
    LWItemID      item;
    LWFrame       frame;
    LWTime        time;
    /* $argument: method=LWItemMotionAccess:getParam, arg3=out::$ */
    void        (*getParam) (LWItemParam, LWTime, LWDVector);
    void        (*setParam) (LWItemParam, const LWDVector);
    int       animationPass;
} LWItemMotionAccess;

/* $wrapper: type=handler, name=LWItemMotionHandler, context=LWItemID$ */
typedef struct st_LWItemMotionHandler {
    LWInstanceFuncs  *inst;
    LWItemFuncs  *item;
    void        (*evaluate) (LWInstance, const LWItemMotionAccess *);
    unsigned int    (*flags)    (LWInstance);
} LWItemMotionHandler;

#define LWIMF_AFTERIK   (1<<0)


#endif

