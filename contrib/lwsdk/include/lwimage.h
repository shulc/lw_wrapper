/*
 * LWSDK Header File
 *
 * LWIMAGE.H -- LightWave Images
 *
 *$copyright$
 */
#ifndef LWSDK_IMAGE_H
#define LWSDK_IMAGE_H

#include <lwtypes.h>
#include <lwimageio.h>
#include <lwio.h>

#define LWIMAGELIST_GLOBAL  "LW Image List 9"
#define LWIMAGEUTIL_GLOBAL  "Image Utility 6"

// change-event codes

enum {
        LWCEV_CHANGE = 0,
        LWCEV_REPLACE,
        LWCEV_DESTROY
};

// change-event callback prototype

typedef void (*LWImageEventFunc)(int eventCode, LWImageID );

// event regitration codes (second argument to changeEvent())

enum {
        LWERC_REGISTER = 0,
        LWERC_UNREGISTER
};

// Texture repetition / mapping modes.
typedef enum {LWTEXTURE_RESET = 0, LWTEXTURE_REPEAT, LWTEXTURE_MIRROR, LWTEXTURE_EDGE} LWTextureWrap;

/* When surface plugins save an image in an LWO, it is necessary to call clipSetMark to tell the LWO saver which clips are being saved. */

typedef LWImageID (*LWImageSaverNotify)( LWInstance );  /* Prototype for the save notify callback. */

/* $wrapper: type=global, name=LWImageList$ */
typedef struct st_LWImageList {
    LWImageID       (*first      )( void );
    LWImageID       (*next       )( LWImageID img );
    LWImageID       (*load       )( LWCStringUTF8 filename );
    LWCStringUTF8   (*name       )( LWImageID img);
    LWCStringUTF8   (*filename   )( LWImageID img, LWFrame frame);
    int             (*isColor    )( LWImageID img );
    void            (*needAA     )( LWImageID img );
    /* $argument: method=LWImageList:size, arg2=out:int:1, arg3=out:int:1$ */
    void            (*size       )( LWImageID img, int *w, int *h );
    LWBufferValue   (*luma       )( LWImageID img, int x, int y );
    /* $argument: method=LWImageList:RGB, arg4=out:LWBufferValue:3$ */
    void            (*RGB        )( LWImageID img, int x, int y, LWBufferValue values[3] );
    double          (*lumaSpot   )( LWImageID img, double x, double y, double spotSize, int in_blend);
    /* $argument: method=LWImageList:RGBSpot, arg6=out:double:3$ */
    void            (*RGBSpot    )( LWImageID img, double x, double y, double spotSize, int in_blend, double rgb[3]);
    void            (*clear      )( LWImageID img );
    LWImageID       (*sceneLoad  )( const LWLoadState *load );
    void            (*sceneSave  )( const LWSaveState *save, LWImageID img );
    int             (*hasAlpha   )( LWImageID img);
    LWBufferValue   (*alpha      )( LWImageID img, int x, int y );
    double          (*alphaSpot  )( LWImageID img, double x, double y, double spotSize, int in_blend);
    LWPixmapID      (*evaluate   )( LWImageID img, LWTime t);
    void            (*changeEvent)( LWImageEventFunc func, int code);
    int             (*replace    )( LWImageID img, LWCStringUTF8 filename );
    LWPixmapID      (*create     )( LWCStringUTF8 name, int width, int height, LWImageType type );
    void            (*saverNotifyAttach)( LWInstance, LWImageSaverNotify );
    void            (*saverNotifyDetach)( LWInstance );
    void            (*saverNotifyMarkUsage)( LWTextureID );
    double          (*evaluateImage)(LWImageID img, double u, double v, double dudx, double dvdx, double dudy, double dvdy,
                                     int pixelBlending, int useMip, double mipStrength, LWTextureWrap uWrap, LWTextureWrap vWrap, LWDVector color);
    int             (*getMipMapLevel)( LWImageID img );
    int             (*setMipMapLevel)( LWImageID img, int );
    LWImageID       (*getSelection)( int index );
    int             (*getSequenceDigits)( LWImageID img );
    double          (*getFrameRate)( LWImageID img );
    int             (*getFirstFrame)( LWImageID img );
    int             (*getLastFrame)( LWImageID img );
    int             (*getStartFrame)( LWImageID img );
    int             (*getPreBehavior)( LWImageID img );
    int             (*getPostBehavior)( LWImageID img );
    int             (*getInFrame)( LWImageID img );
    int             (*getOutFrame)( LWImageID img );
} LWImageList;

/* $wrapper: type=global, name=LWImageUtil$ */
typedef struct st_LWImageUtil
{
    LWPixmapID    (*create        )( int w, int h, LWImageType type );
    void          (*destroy       )( LWPixmapID img );
    int           (*save          )( LWPixmapID img, int saver, LWCStringUTF8 name );
    int           (*setPixel      )( LWPixmapID img, int x, int y,  void *pix );
    int           (*getPixel      )( LWPixmapID img, int x, int y,  void *pix );
    /* $argument: method=LWImageUtil:getInfo, arg2=out:int:1, arg3=out:int:1, arg4=out:int:1$ */
    int           (*getInfo       )( LWPixmapID img, int *w, int *h, int *type );
    LWPixmapID    (*resample      )( LWPixmapID img, int w, int h, int mode );
    int           (*saverCount    )( void );
    LWCStringUTF8 (*saverName     )( int saver );
    int           (*setPixelTyped )( LWPixmapID img, int x, int y, int type, void *pix );
    int           (*getPixelTyped )( LWPixmapID img, int x, int y, int type, void *pix );
    int           (*getIndex8Map  )( LWPixmapID img, LWPixelRGB24 *map );
    int           (*getAttr       )( LWPixmapID img, LWImageParam tag, void* data );
    int           (*getMakerNote  )( LWPixmapID img, LWMakerNote tag, void* data );
    int           (*setIndex8Map  )( LWPixmapID img, LWPixelRGB24 *map );
    int           (*setAttr       )( LWPixmapID img, LWImageParam tag, void* data );
    int           (*setMakerNote  )( LWPixmapID img, LWMakerNote tag, LWCStringUTF8 note );
    int           (*setLineTyped  )( LWPixmapID img, int, int, void * );
    int           (*getLineTyped  )( LWPixmapID img, int, int, void * );
    int           (*copyAttributes)( LWPixmapID dest, LWPixmapID sorc );
} LWImageUtil;

/* resample modes */
enum {
        LWISM_SUBSAMPLING = 0,
        LWISM_MEDIAN,           /* for shrinking */
        LWISM_SUPERSAMPLING,
        LWISM_BILINEAR,         /* for expanding */
        LWISM_BSPLINE,          /* for expanding */
        LWISM_BICUBIC           /* for expanding */
};

#endif
