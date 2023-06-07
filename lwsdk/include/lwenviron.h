/*
 * LWSDK Header File
 *
 * LWENVIRON.H -- LightWave Environments
 *
 * This header defines the environment render handler for backdrops and
 * fog.
 *
 *$copyright$
 */
#ifndef LWSDK_ENVIRON_H
#define LWSDK_ENVIRON_H

#include <lwrender.h>

#define LWENVIRONMENT_HCLASS    "EnvironmentHandler"
#define LWENVIRONMENT_ICLASS    "EnvironmentInterface"
#define LWENVIRONMENT_GCLASS    "EnvironmentGizmo"
#define LWENVIRONMENT_VERSION   6


typedef enum en_LWEnvironmentMode
{
    EHMODE_PREVIEW,
    EHMODE_REAL
} LWEnvironmentMode;

/* $wrapper: type=access, name=LWEnvironmentAccess$ */
typedef struct st_LWEnvironmentAccess
{
    LWEnvironmentMode   mode;
    double              h[2], p[2];
    LWDVector           I;
    double              colRect[4][3];
    LWDVector           color;
    LWDVector           dIdx;
    LWDVector           dIdy;
} LWEnvironmentAccess;

/* $wrapper: type=handler, name=LWEnvironmentHandler, accessor=LWENVIRONMENT$ */
typedef struct st_LWEnvironmentHandler
{
    LWInstanceFuncs *inst;
    LWItemFuncs     *item;
    LWRenderFuncs   *rend;
    LWError         (*evaluate)(LWInstance, LWEnvironmentAccess*);
    unsigned int    (*flags)(LWInstance);
} LWEnvironmentHandler;

#define LWENF_TRANSPARENT   (1<<0)

#endif
