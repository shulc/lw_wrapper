/*
 * LWSDK Header File
 * lwmeshmodifier.h -- LightWave Mesh Modifiers
 *
 *$copyright$
 */
#ifndef LWSDK_MESHMODIFIER_H
#define LWSDK_MESHMODIFIER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <lwrender.h>
#include <lwmeshes.h>



#define LWMESHMODIFIER_HCLASS   "MeshModifierHandler"
#define LWMESHMODIFIER_ICLASS   "MeshModifierInterface"
#define LWMESHMODIFIER_GCLASS   "MeshModifierGizmo"
#define LWMESHMODIFIER_ACLASS   "MeshModifierAttrui"
#define LWMESHMODIFIER_VERSION  2


/* $wrapper: type=access, name=LWMeshModifierAccess$ */
typedef struct st_LWMeshModifierAccess {
    /* $modifier: class=LWMeshModifierAccess, arg=mesh, modifier=const$ */
    LWMutableMeshID mesh;

    /* $modifier: class=LWMeshModifierAccess, arg=status, modifier=const$ */
    unsigned int status;

    LWDMatrix9   dirToWorld;            // worldPos = dirToWorld * localPos + offsetToWorld
    LWDVector    offsetToWorld;
    LWDMatrix9   dirFromWorld;          // localPos = dirFromWorld * worldPos + offsetFromWorld
    LWDVector    offsetFromWorld;
    LWDMatrix9   normToWorld;           // worldNormal = normalize(normToWorld * localNormal)
    LWDMatrix9   normFromWorld;         // localNormal = normalize(normFromWorld * worldNormal)
} LWMeshModifierAccess;

/* $wrapper: type=handler, name=LWMeshModifierHandler, context=LWItemID, pythonext=MM, pythonuserext=(Mesh Modifier)$ */
typedef struct st_LWMeshModifierHandler {
    LWInstanceFuncs *inst;
    LWItemFuncs     *item;
    LWRenderFuncs   *rend;
    unsigned int   (*flags)    (LWInstance);
    unsigned int   (*begin)    (LWInstance, LWMeshModifierAccess *);
    unsigned int   (*evaluate) (LWInstance, LWMeshModifierAccess *);
    void           (*end)      (LWInstance, LWMeshModifierAccess *);
} LWMeshModifierHandler;



#define LWMESHDEFORMER_HCLASS   "MeshDeformerHandler"
#define LWMESHDEFORMER_ICLASS   "MeshDeformerInterface"
#define LWMESHDEFORMER_GCLASS   "MeshDeformerGizmo"
#define LWMESHDEFORMER_ACLASS   "MeshDeformerAttrui"
#define LWMESHDEFORMER_VERSION  2

/* $wrapper: type=access, name=LWMeshDeformerAccess$ */
typedef struct st_LWMeshDeformerAccess {
    /* $modifier: class=LWMeshDeformerAccess, arg=mesh, modifier=const$ */
    LWDeformableMeshID mesh;

    /* $modifier: class=LWMeshDeformerAccess, arg=status, modifier=const$ */
    unsigned int status;

    LWDMatrix9   dirToWorld;            // worldPos = dirToWorld * localPos + offsetToWorld
    LWDVector    offsetToWorld;
    LWDMatrix9   dirFromWorld;          // localPos = dirFromWorld * worldPos + offsetFromWorld
    LWDVector    offsetFromWorld;
    LWDMatrix9   normToWorld;           // worldNormal = normalize(normToWorld * localNormal)
    LWDMatrix9   normFromWorld;         // localNormal = normalize(normFromWorld * worldNormal)

    /* $modifier: class=LWMeshDeformerAccess, arg=startIndex, modifier=const$ */
    size_t       startIndex;
    /* $modifier: class=LWMeshDeformerAccess, arg=endIndex, modifier=const$ */
    size_t       endIndex;

    /* $modifier: class=LWMeshDeformerAccess, arg=oPos, modifier=const, apply=pointer$ */
    const float *oPos;
    /* $modifier: class=LWMeshDeformerAccess, arg=fPos, modifier=const, apply=pointer$ */
    float       *fPos;
    /* $modifier: class=LWMeshDeformerAccess, arg=posStride, modifier=const$ */
    size_t       posStride;             // Number of floats between start of consecutive indices
} LWMeshDeformerAccess;

/* $wrapper: type=handler, name=LWMeshDeformerHandler, context=LWItemID, pythonext=MD, pythonuserext=(Mesh Deformer)$ */
typedef struct st_LWMeshDeformerHandler {
    LWInstanceFuncs *inst;
    LWItemFuncs     *item;
    LWRenderFuncs   *rend;
    unsigned int   (*flags)    (LWInstance);
    unsigned int   (*begin)    (LWInstance, LWMeshDeformerAccess *);
    unsigned int   (*evaluate) (LWInstance, LWMeshDeformerAccess *);
    void           (*end)      (LWInstance, LWMeshDeformerAccess *);
} LWMeshDeformerHandler;



// flags() and begin()
#define LWMESHMODIFIERF_SKIP        (1U << 0)   // Do not evaluate
#define LWMESHMODIFIERF_NO_MT       (1U << 1)   // No multithreaded evaluation
#define LWMESHMODIFIERF_NO_DISABLE  (1U << 2)   // Not affected by disabling the "Enable Deformations" toggle (flags() only)

// evaluate() and status
#define LWMESHMODIFIER_UNCHANGED    0           // No changes made to mesh
#define LWMESHMODIFIER_VERTSMOVED   (1U << 0)   // Modifier made changes to vertex positions
#define LWMESHMODIFIER_GEOCHANGED   (1U << 1)   // Modifier made changes to the geometry
#define LWMESHMODIFIER_INTERRUPT    (1U << 31)  // Evaluation was interrupted


#ifdef __cplusplus
}
#endif

#endif
