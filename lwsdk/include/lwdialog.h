/*
 * LWSDK Header File
 *
 * LWDIALOG.H -- LightWave Standard Dialogs
 *
 * LightWave makes some of its more common requests from the user using
 * standard dialogs.  These dialogs (or "requesters") are used for getting
 * files and paths for saving and loading, and for getting color choices.
 * By default, the standard system dialogs are used, but these can be
 * overridden by plug-ins of the right class.
 *
 *$copyright$
 */
#ifndef LWSDK_DIALOG_H
#define LWSDK_DIALOG_H

#include <lwtypes.h>

/*
 * File dialogs can be configured by servers of this class.
 */
#define LWFILEREQ_CLASS     "FileRequester"
#define LWFILEREQ_VERSION   4

/* $wrapper: type=access, name=LWFileReqLocal$ */
typedef struct st_LWFileReqLocal {
    /* $modifier: class=LWFileReqLocal, arg=reqType, modifier=const$ */
    int         reqType;
    int         result;
    /* $comment: ------------------------------------------------------------- */
    /* $comment: Make the pointers for 'title' and 'fileType' const so they    */
    /* $comment: are not modified in the wrapper-generated push()/pull() code. */
    /* $comment: ------------------------------------------------------------- */
    /* $modifier: class=LWFileReqLocal, arg=title, modifier=const, apply=pointer$ */
    LWCStringUTF8 title;
    /* $modifier: class=LWFileReqLocal, arg=fileType, modifier=const, apply=pointer$ */
    LWCStringUTF8 fileType;
    LWMutableCStringUTF8 path;
    LWMutableCStringUTF8 baseName;
    LWMutableCStringUTF8 fullName;
    /* $wrapper: type=ignore, name=LWFileReqLocal, arg=bufLen */
    int         bufLen;
    /* $wrapper: type=ignore, name=LWFileReqLocal, arg=pickName$ */
    int       (*pickName)( void );
} LWFileReqLocal;

#define FREQ_LOAD       1
#define FREQ_SAVE       2
#define FREQ_DIRECTORY  3
#define FREQ_MULTILOAD  4


/*
 * Color dialogs can be configured by servers of this class.
 */
#define LWCOLORPICK_CLASS   "ColorPicker"
#define LWCOLORPICK_VERSION 6           /* This version means your need to supply your own color correction. */

typedef void LWHotColorFunc( void *data, float r, float g, float b );

typedef struct st_LWColorPickLocal {
    int             result;
    LWCStringUTF8   title;
    float           red, green, blue;
    void           *data;
    LWHotColorFunc *hotFunc;
    LWCStringUTF8   colorSpace;
} LWColorPickLocal;

#endif
