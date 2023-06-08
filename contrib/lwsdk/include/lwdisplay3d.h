/*
 * LWSDK Header File
 *
 * LWDISPLAY3D.H -- LightWave Display 3D
 *
 *$copyright$
 */
#ifndef LWSDK_DISPLAY3D
#define LWSDK_DISPLAY3D

#ifdef __cplusplus
extern "C" {
#endif

#include <lwtypes.h>
#include <lwimage.h>
#include <lwrender.h>

#define LWDISPLAY3D_HCLASS  "Display3DHandler"
#define LWDISPLAY3D_ICLASS  "Display3DInterface"
#define LWDISPLAY3D_VERSION 4

enum en_LW3dDisplay {
    LW3D_show = 0,              /*!< Show window.          */
    LW3D_hide,                  /*!< Hide window.          */
    LW3D_sizeof
};

/* $wrapper: type=access, name=LWDisplay3DLocal$ */

typedef struct st_LWDisplay3DLocal {
    void           *priv_data;  /*!< Private data pointer. */
    int             viewNumber; /*!< Viewport number.      */
} LWDisplay3DLocal;

/**
 *  @short renderEye
 *
 *   LWCAMEYE_CENTER
 *   LWCAMEYE_LEFT
 *   LWCAMEYE_RIGHT
 */

/* $wrapper: type=handler, name=LWDisplay3DHandler, context=int *, accessor=LWDISPLAY3D$ */
typedef struct st_LWDisplay3DHandler {
    LWInstanceFuncs *inst;
    LWItemFuncs     *item;      /*!< create, destroy, copy, load, save, descln. */
    int            (*setImage )( LWInstance, int renderEye, LWPixmapID  image );
    int            (*getImage )( LWInstance, int renderEye, LWPixmapID *image );
    int            (*showImage)( LWInstance, int mode );
    int            (*viewPort )( LWInstance );
    int            (*setBuffer)( LWInstance, int renderEye, LWCStringUTF8 group, LWCStringUTF8 name, LWPixmapID  buffer, unsigned int scale );
    int            (*getBuffer)( LWInstance, int renderEye, LWCStringUTF8 group, LWCStringUTF8 name, LWPixmapID *buffer );
    LWCStringUTF8 *(*buffers  )( LWInstance, int renderEye ); /* returns NULL-terminated array */
    int            (*active   )( LWInstance );
} LWDisplay3DHandler;

#ifdef __cplusplus
}
#endif

#endif
