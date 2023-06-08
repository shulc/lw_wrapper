/*
 * LWSDK Header File
 *
 * LWSURFED.H -- LightWave Surface Editor
 *
 *$copyright$
 */
#ifndef LWSDK_SURFED_H
#define LWSDK_SURFED_H

#include <lwsurf.h>

#define LWSURFEDFUNCS_GLOBAL    "SurfaceEditor Functions 2"

#define LWSURFEDFUNCS_PRIMARYINDEX -1

/* $wrapper: type=global, name=LWSurfEdFuncs$ */
typedef struct st_LWSurfEdFuncs {
    void            (*open)(int);
    void            (*close)(void);
    int             (*isOpen)(void);
    void            (*setSurface)(LWSurfaceID);
    void            (*setPosition)(int  x, int  y);
    /* $argument: method=LWSurfEdFuncs:getPosition, arg1=out:int:, arg2=out:int:, arg3=out:int:, arg4=out:int:$ */
    void            (*getPosition)(int  *x, int *y,int *w,int *h);
    void            (*addLib)(LWSurfLibID lib);
    LWSurfaceID     (*getSelection)(int index);
} LWSurfEdFuncs;

#endif
