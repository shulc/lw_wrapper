/*
 * LWSDK Header File
 *
 * lwmeshtypes.h -- LightWave Common Mesh-Related Types
 *
 * This header contains type declarations common to mesh-related 
 * aspects of LightWave.
 *
 *$copyright$
 */
#ifndef LWSDK_COMMON_MESH_TYPES_H
#define LWSDK_COMMON_MESH_TYPES_H

#define LWMESH_TYPES_VERSION 1

/*
 * Meshes are composed of points, edges, and polygons given by their internal
 * ID reference.
 */
typedef struct LWPnt*  LWPntID;
typedef struct LWEdge* LWEdgeID;
typedef struct LWPol*  LWPolID;

typedef struct LWVMap* LWVMapID;

typedef struct LWMesh* LWMeshID;
typedef struct LWMeshDeform* LWMeshDeformID;
typedef struct LWMeshMutate* LWMeshMutateID;

typedef struct st_LWDeformableMeshAccess
{
    LWMeshID read;
    LWMeshDeformID deform;
} LWDeformableMeshAccess;

typedef struct st_LWMutableMeshAccess
{
    LWMeshID read;
    LWMeshDeformID deform;
    LWMeshMutateID mutate;
} LWMutableMeshAccess;

typedef LWDeformableMeshAccess* LWDeformableMeshID;
typedef LWMutableMeshAccess* LWMutableMeshID;

#endif
