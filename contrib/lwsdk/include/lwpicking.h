/*
 * LWSDK Header File
 *
 * picking.h -- LightWave Picking Access
 *
 *$copyright$
 */
#ifndef LWSDK_PICKING_H
#define LWSDK_PICKING_H

#include <lwtypes.h>
#include <lwmeshtypes.h>

#define LWPICKING_VERSION 1

typedef enum
{
    lwPickNone,
    lwPickPoint,
    lwPickEdge,
    lwPickPoly
} LWPickType;

typedef union
{
    LWPntID point;
    LWEdgeID edge;
    LWPolID poly;
} LWPickElement;

typedef struct st_LWPickResult
{
    /// Identifies the type of element being picked.
    LWPickType type;

    /// Specifies the actual element being picked.
    LWPickElement element;

    /// Represents where the picking ray intersected the geometry.
    double intersection[3];

    /// Internal data identifying the layer in which the element resides.
    void* layer;
} LWPickResult;

typedef struct st_LWPicking
{
    /* $modifier: class=LWPicking, arg=priv, modifier=const, apply=pointer$ */
    void* priv;

    /// @return true if the picking interface is valid.
    int (*valid)(struct st_LWPicking* self);

    /// @return the frontmost point under the cursor.
    /* $wrapper: type=ignore, name=LWPicking, arg=solidPickPoint$ */
    LWPickResult (*solidPickPoint)(struct st_LWPicking* self);

    /// @return the frontmost edge under the cursor.
    /* $wrapper: type=ignore, name=LWPicking, arg=solidPickEdge$ */
    LWPickResult (*solidPickEdge)(struct st_LWPicking* self);

    /// @return the frontmost polygon under the cursor.
    /* $wrapper: type=ignore, name=LWPicking, arg=solidPickPoly$ */
    LWPickResult (*solidPickPoly)(struct st_LWPicking* self);
} LWPicking;

#endif
