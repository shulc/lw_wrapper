/*
 * LWSDK Header File
 *
 * LWCOLORSPACE.H -- LightWave Color Space
 *
 *$copyright$
 */
#ifndef LWSDK_COLORSPACE_H
#define LWSDK_COLORSPACE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <lwtypes.h>

#define LWCOLORSPACEFUNCS_GLOBAL "LWColorSpace"

/* Color Space Names. */

#define LW_COLORSPACE_VIEWER            "ColorSpaceViewer"
#define LW_COLORSPACE_SURFACE_COLOR     "ColorSpaceSurfaceColor"
#define LW_COLORSPACE_LIGHT_COLOR       "ColorSpaceLightColor"
#define LW_COLORSPACE_PALETTE_FILES     "ColorSpacePaletteFiles"
#define LW_COLORSPACE_8BIT_FILES        "ColorSpace8BitFiles"
#define LW_COLORSPACE_FLOAT_FILES       "ColorSpaceFloatFiles"
#define LW_COLORSPACE_ALPHA             "ColorSpaceAlpha"
#define LW_COLORSPACE_OUTPUT            "ColorSpaceOutput"
#define LW_COLORSPACE_OUTPUT_ALPHA      "ColorSpaceOutputAlpha"
#define LW_COLORSPACE_OUTPUT_VPR        "ColorSpaceOutputVPR"
#define LW_COLORSPACE_OUTPUT_VPR_ALPHA  "ColorSpaceOutputVPRAlpha"
#define LW_COLORSPACE_OUTPUT_BUFFER     "ColorSpaceOutputBuffer"
#define LW_COLORSPACE_AUTO_SENSE        "ColorSpaceAutoSense"
#define LW_COLORSPACE_CORRECT_OPENGL    "ColorSpaceCorrectOpenGL"
#define LW_COLORSPACE_AFFECT_PICKER     "ColorSpaceAffectPicker"
#define LW_COLORSPACE_8BIT_TO_FLOAT     "ColorSpace8BitToFloat"

typedef enum en_lwcolorspace {
    lwcs_linear = 0,                /*!< LightWave linear color space.      */
    lwcs_sRGB,                      /*!< Standard RGB color space.          */
    lwcs_rec709,                    /*!< Recommendation BT.709, HDTV.       */
    lwcs_cineon,                    /*!< Eastman Kodak Co.                  */
    lwcs_ciexyz,                    /*!< CIE XYZ.                           */
#ifdef ACES_CS
    lwcs_aces,                      /*!< Aces color space.                  */
#endif
    lwcs_sizeof
} LWCOLORSPACE;

typedef enum en_lwcolorspacetypes {
    lwcst_viewer = 0,               /*!< Viewer           color space.      */
    lwcst_surface_color,            /*!< Surface          color space.      */
    lwcst_palette_files,            /*!< Palette files    color space.      */
    lwcst_8bit_files,               /*!< 8 bit   files    color space.      */
    lwcst_float_files,              /*!< Float   files    color space.      */
    lwcst_alpha_files,              /*!< Alpha   files    color space.      */
    lwcst_output,                   /*!< Output  files    color space.      */
    lwcst_output_alpha,             /*!< Alpha   files    color space.      */
    lwcst_light_color,              /*!< Light            color space.      */
    lwcst_output_vpr,               /*!< Output VPR       color space.      */
    lwcst_output_alpha_vpr,         /*!< Output VPR alpha color space.      */
    lwcst_output_buffer,            /*!< Output Buffer    color space.      */
    lwcst_sizeof
} LWCOLORSPACETYPES;

typedef enum en_lwcolorspaceconversion {
    lwcsc_colorspaceToLinear = 0,   /*!< Convert from non-linear to linear. */
    lwcsc_linearToColorspace,       /*!< Convert from linear to non-linear. */
    lwcsc_sizeof
} LWCOLORSPACECONVERSION;

typedef enum en_lwcolorspacelayer {
    lwcsl_RGB = 0,                  /*!< RGB   Channel.                     */
    lwcsl_Alpha,                    /*!< Alpha Channel.                     */
    lwcsl_sizeof
} LWCOLORSPACELAYER;

/**
 *      struct st_lwimagelookup *
 *
 *      Is a forward reference to the internal lw instance structure ( defined internally ).
 *      This is used instead of a void * pointer.
 */

typedef struct st_lwimagelookup* LWImageLookupID;

typedef void LWPIXELCONVERSIONRGB(   LWImageLookupID, float *, float * ); /*!< Conversion function prototype. */
typedef void LWPIXELCONVERSIONALPHA( LWImageLookupID, float *, float * ); /*!< Conversion function prototype. */

/**
 *      Color space functions.
 *
 *      Color spaces file references are save in the scene file if they are used,
 *      in the viewer, color space file defaults or in a LWO from the image viewer.
 */

/* $wrapper: type=global, name=LWColorSpaceFuncs$ */
typedef struct LWColorSpaceFuncs_t {

    /* These function are used to get the color space of a loaded converter or load one from the disk. */

    LWCOLORSPACE            (*nameToColorSpace       )( LWCStringUTF8 name );   /*!< Color space name. */
    LWCOLORSPACE            (*loadPixelLookupTable   )( LWCStringUTF8 file );   /*!< File name.        */

    /* These functions are used to get the pixel conversion functions. */

    /* $wrapper: type=ignore, name=LWColorSpaceFuncs, arg=getPixelConversionRGB$ */
    LWPIXELCONVERSIONRGB   *(*getPixelConversionRGB  )( LWCOLORSPACE, LWCOLORSPACECONVERSION, LWImageLookupID* );
    /* $wrapper: type=ignore, name=LWColorSpaceFuncs, arg=getPixelConversionAlpha$ */
    LWPIXELCONVERSIONALPHA *(*getPixelConversionAlpha)( LWCOLORSPACE, LWCOLORSPACECONVERSION, LWImageLookupID* );

    /* These functions are used to get color space names and file names, based on type. */

    LWCStringUTF8           (*colorSpaceName         )( LWCOLORSPACETYPES );    /*!< Gets the name of the current color space of the type selected. */
    LWCStringUTF8           (*colorSpaceFile         )( LWCOLORSPACETYPES );    /*!< Gets the file of the current color space of the type selected. */

    /* These functions are used in pop-ups. */

    int                     (*numberOfColorSpaces    )( LWCOLORSPACELAYER );    /*!< Gets the number of loaded color spaces in the layer.           */
    LWCStringUTF8           (*nameOfColorSpaces      )( LWCOLORSPACELAYER, int);/*!< Gets the name of the color space in the layer.                 */
    LWCOLORSPACE            (*indexToColorSpace      )( LWCOLORSPACELAYER, int);/*!< Used to convert from indexes of pop-ups to color spaces.       */
    int                     (*colorSpaceToIndex      )( LWCOLORSPACELAYER, LWCOLORSPACE );

    /* This functions is to change the currently selected color space. */

    int                     (*setColorSpace          )( LWCOLORSPACETYPES, LWCOLORSPACE );
    LWCOLORSPACE            (*getColorSpace          )( LWCStringUTF8 );         /*!< Returns the color space setting of the color space type */
    int                     (*getColorSpaceBoolean   )( LWCStringUTF8 );         /*!< Returns the state of a color space check box.           */
    int                     (*setColorSpaceBoolean   )( LWCStringUTF8, int );    /*!< Sets the state of a color space check box.              */
} LWColorSpaceFuncs;

#ifdef __cplusplus
}
#endif

#endif
