/*
 * LWSDK Header File
 *
 * LWSCENECV.H -- LightWave Scene Converters
 *
 *$copyright$
 */
#ifndef LWSDK_SCENECV_H
#define LWSDK_SCENECV_H

#include <lwtypes.h>
#include <lwhandler.h>

#define LWSCENECONVERTER_CLASS      "SceneConverter"
#define LWSCENECONVERTER_VERSION    2


typedef struct st_LWSceneConverter {
    LWCStringUTF8 filename;
    LWError       readFailure;
    LWCStringUTF8 tmpScene;
    void        (*deleteTmp) (LWCStringUTF8 tmpScene);
} LWSceneConverter;


#endif

