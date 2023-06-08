/*
 * LWSDK Header File
 *
 * LWMESHEDT.H -- LightWave MeshDataEdit Server
 *
 * This header contains the types and declarations for the Modeler
 * MeshDataEdit class.
 *
 *$copyright$
 */
#ifndef LWSDK_MESHEDT_H
#define LWSDK_MESHEDT_H

#include <lwtypes.h>
#include <lwmodeler.h>
#include <lwmeshes.h>
#include <generators/lwpointgenerator.h>
#include <generators/lwedgegenerator.h>
#include <generators/lwpolygenerator.h>

#define LWMESHEDIT_CLASS "MeshDataEdit"
#define LWMESHEDIT_VERSION 9

typedef struct st_MeshEditState* EDStateRef;

typedef struct st_EDPointInfo
{
    LWPntID          pnt;
    void            *userData;
    int              layer;
    int              flags;

    double           position[3];
    float           *vmapVec;

    int              numEdges;
    const LWEdgeID  *edges;

    LWMeshID         meshid;

} EDPointInfo, LWPointInfo;

typedef struct st_EDPolygonInfo
{
    LWPolID          pol;
    void            *userData;
    int              layer;
    int              flags;

    int              numPnts;
    const LWPntID   *points;

    LWCStringUTF8    surface;
    unsigned int     type;
    int              typeFlags;
    unsigned int     smGrps;

    LWMeshID         meshid;

} EDPolygonInfo, LWPolyInfo;

typedef struct st_EDEdgeInfo
{
    LWEdgeID         edge;
    void            *userData;
    int              layer;
    int              flags;

    LWPntID          p1, p2;

    int              numPols;
    const LWPolID*   pols;

    LWMeshID         meshid;

} EDEdgeInfo, LWEdgeInfo;

#define EDDF_SELECT     (1<<0)
#define EDDF_DELETE     (1<<1)
#define EDPF_CCEND      (1<<2)
#define EDPF_CCSTART    (1<<3)

typedef int EDError;
#define EDERR_NONE       0
#define EDERR_NOMEMORY   1
#define EDERR_BADLAYER   2
#define EDERR_BADSURF    3
#define EDERR_USERABORT  4
#define EDERR_BADARGS    5
#define EDERR_BADVMAP    6

#define EDSELM_CLEARCURRENT (1<<0)
#define EDSELM_SELECTNEW    (1<<1)
#define EDSELM_FORCEVRTS    (1<<2)
#define EDSELM_FORCEPOLS    (1<<3)

#define OPSEL_MODIFY        (1<<15)

#define EDCOUNT_ALL          0
#define EDCOUNT_SELECT       1
#define EDCOUNT_DELETE       2

typedef EDError      EDPointScanFunc        (void*, const EDPointInfo*);
typedef EDError      EDEdgeScanFunc         (void*, const EDEdgeInfo*);
typedef EDError      EDPolyScanFunc         (void*, const EDPolygonInfo*);

typedef EDError      EDFastPointScanFunc    (void*, LWPntID);
typedef EDError      EDFastEdgeScanFunc     (void*, LWEdgeID);
typedef EDError      EDFastPolyScanFunc     (void*, LWPolID);

typedef struct st_EDBoundCv
{
    LWPolID     curve;
    int         start, end;
} EDBoundCv;

/* $wrapper: type=access, name=MeshEditOp$ */
typedef struct st_MeshEditOp
{
    /* $modifier: class=MeshEditOp, arg=state, modifier=const$ */
    EDStateRef           state;
    /* $modifier: class=MeshEditOp, arg=layerNum, modifier=const$ */
    int                  layerNum;

    void                (*done)             (EDStateRef, EDError, int selm);

    int                 (*pointCount)       (EDStateRef, EltOpLayer, int mode);
    int                 (*polyCount)        (EDStateRef, EltOpLayer, int mode);

    EDError             (*pointScan)        (EDStateRef, EDPointScanFunc *, void *, EltOpLayer);
    EDError             (*polyScan)         (EDStateRef, EDPolyScanFunc *, void *, EltOpLayer);

    EDPointInfo *       (*pointInfo)        (EDStateRef, LWPntID);
    EDPolygonInfo *     (*polyInfo)         (EDStateRef, LWPolID);

    /* $argument: method=MeshEditOp:polyNormal, arg3=out:double:3$ */
    int                 (*polyNormal)       (EDStateRef, LWPolID, double[3]);

    LWPntID             (*addPoint)         (EDStateRef, double *xyz);
    LWPolID             (*addFace)          (EDStateRef, LWCStringUTF8 surf, int numPnt, const LWPntID *);
    LWPolID             (*addCurve)         (EDStateRef, LWCStringUTF8 surf, int numPnt, const LWPntID *, int flags);
    EDError             (*addQuad)          (EDStateRef, LWPntID, LWPntID, LWPntID, LWPntID);
    EDError             (*addTri)           (EDStateRef, LWPntID, LWPntID, LWPntID);
    EDError             (*addPatch)         (EDStateRef, int nr, int nc, int lr, int lc, EDBoundCv *r0, EDBoundCv *r1, EDBoundCv *c0, EDBoundCv *c1);

    EDError             (*remPoint)         (EDStateRef, LWPntID);
    EDError             (*remPoly)          (EDStateRef, LWPolID);

    EDError             (*pntMove)          (EDStateRef, LWPntID, const double *);
    EDError             (*polSurf)          (EDStateRef, LWPolID, LWCStringUTF8 surf);
    EDError             (*polPnts)          (EDStateRef, LWPolID, int, const LWPntID *);
    EDError             (*polFlag)          (EDStateRef, LWPolID, int mask, int value);

    EDError             (*polTag)           (EDStateRef, LWPolID, LWID, LWCStringUTF8 tag);
    EDError             (*pntVMap)          (EDStateRef, LWPntID, LWID, LWCStringUTF8 vmap_name, int, float *);

    LWPolID             (*addPoly)          (EDStateRef, LWID type, LWPolID, LWCStringUTF8 surf, int numPnt, const LWPntID *);
    LWPntID             (*addIPnt)          (EDStateRef, double *xyz, int numPnt, const LWPntID *, const double *wt);
    EDError             (*initUV)           (EDStateRef, float *uv);

    void *              (*pointVSet)        (EDStateRef, void *vmap_id, LWID vmap_type, LWCStringUTF8 vmap_name);
    int                 (*pointVGet)        (EDStateRef, LWPntID point_id, float *vmap_vector);
    LWCStringUTF8       (*polyTag)          (EDStateRef, LWPolID polygon_id, LWID tag_type);

    EDError             (*pntSelect)        (EDStateRef, LWPntID point_id, int selection_state);
    EDError             (*polSelect)        (EDStateRef, LWPolID polygon_id, int selection_state);

    int                 (*pointVPGet)       (EDStateRef, LWPntID point_id, LWPolID polygon_id, float *vmap_vector);
    int                 (*pointVEval)       (EDStateRef, LWPntID point_id, LWPolID polygon_id, float *vmap_vector);
    EDError             (*pntVPMap)         (EDStateRef, LWPntID point_id, LWPolID polygon_id, LWID vmap_type, LWCStringUTF8 vmap_name, int vmap_dimensions, float *vmap_vector);

    // new in Lightwave 9.0 - LWMESHEDIT_VERSION 5
    int                 (*edgeCount)        (EDStateRef, EltOpLayer, int mode);
    EDError             (*edgeScan)         (EDStateRef, EDEdgeScanFunc*, void*, EltOpLayer);
    EDEdgeInfo *        (*edgeInfo)         (EDStateRef, LWEdgeID);
    EDError             (*edgeSelect)       (EDStateRef, LWEdgeID, int);
    int                 (*edgePolys)        (EDStateRef, LWEdgeID, const LWPolID**);
    LWPntID             (*edgePoint1)       (EDStateRef, LWEdgeID);
    LWPntID             (*edgePoint2)       (EDStateRef, LWEdgeID);
    LWEdgeID            (*edgeFromPoints)   (EDStateRef, LWPntID, LWPntID);
    void                (*edgeFlip)         (EDStateRef, LWEdgeID);

    /* $argument: method=MeshEditOp:pointPos, arg3=out:double:3$ */
    void                (*pointPos)         (EDStateRef, LWPntID, double[3]);
    int                 (*pointEdges)       (EDStateRef, LWPntID, const LWEdgeID**);

    unsigned int        (*polyType)         (EDStateRef, LWPolID);
    int                 (*polyPoints)       (EDStateRef, LWPolID, const LWPntID**);

    int                 (*pointFlags)       (EDStateRef, LWPntID);
    int                 (*edgeFlags)        (EDStateRef, LWEdgeID);
    int                 (*polyFlags)        (EDStateRef, LWPolID);

    void *              (*pointData)        (EDStateRef, LWPntID);
    void *              (*edgeData)         (EDStateRef, LWEdgeID);
    void *              (*polyData)         (EDStateRef, LWPolID);

    EDError             (*fastPointScan)    (EDStateRef, EDFastPointScanFunc*, void*, EltOpLayer, int selectedOnly);
    EDError             (*fastEdgeScan)     (EDStateRef, EDFastEdgeScanFunc*, void*, EltOpLayer, int selectedOnly);
    EDError             (*fastPolyScan)     (EDStateRef, EDFastPolyScanFunc*, void*, EltOpLayer, int selectedOnly);

    int                 (*pointLayer)       (EDStateRef, LWPntID);
    int                 (*edgeLayer)        (EDStateRef, LWEdgeID);
    int                 (*polyLayer)        (EDStateRef, LWPolID);

    int                 (*setLayer)         (EDStateRef, int layerNum);
    int                 (*advanceLayer)     (EDStateRef);

    int                 (*pointNew)         (EDStateRef, LWPntID);
    int                 (*edgeNew)          (EDStateRef, LWEdgeID);
    int                 (*polyNew)          (EDStateRef, LWPolID);

    struct LWPointGenerator*   (*genPoints) (EDStateRef, EltOpLayer, int selectedOnly);
    struct LWEdgeGenerator*    (*genEdges)  (EDStateRef, EltOpLayer, int selectedOnly);
    struct LWPolyGenerator*    (*genPolys)  (EDStateRef, EltOpLayer, int selectedOnly);

    /// New in Lightwave 9.6 - LWMESHEDIT_VERSION 6
    /// @{
    void *              (*vMapSelect)       (EDStateRef es, LWCStringUTF8 vmap_name, LWID type, int dim);
    int                 (*vMapExists)       (EDStateRef es, LWCStringUTF8 vmap_name, LWID type);
    unsigned int        (*vMapGetDimension) (EDStateRef es);
    void                (*vMapSet)          (EDStateRef es, LWPntID point_id, LWPolID polygon_id, const float *value);
    void                (*vMapSetIdeal)     (EDStateRef es, LWPntID point_id, LWPolID polygon_id, const float *value);
    void                (*vMapRename)       (EDStateRef es, LWCStringUTF8 new_name);
    void                (*vMapRemove)       (EDStateRef es);
    /// @}

    /// New in LightWave 11 - LWMESHEDIT_VERSION 7
    /// @{
    /// @return the surface of a polygon.
    LWCStringUTF8       (*polySurface)(EDStateRef es, LWPolID p);
    /// @}

    EDError             (*polType)           (EDStateRef es, LWPolID pol, unsigned int type);

    const int*          (*smoothingGroups)   (EDStateRef es, LWPolID pol);
    int                 (*setSmoothingGroups)(EDStateRef es, LWPolID pol, int *, int);

    /// New in Lightwave 2019 - LWMESHEDIT_VERSION 8
    /// @{
    /// @}

} MeshEditOp;

// Required for backward compatability
typedef MeshEditOp * MeshEditBegin(int pntBuf, int polBuf, EltOpSelect);

// newer, alternative function with edge buffer allocation
typedef MeshEditOp * MeshEditBegin2 (int pntBuf, int edgeBuf, int polBuf, EltOpSelect);

#endif
