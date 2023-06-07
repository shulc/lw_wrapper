/*
 * LWSDK Header File
 *
 * LWCMDSEQ.H -- LightWave CommandSequence Server
 *
 * This header contains the types and declarations for the Modeler
 * CommandSequence class.
 *
 *$copyright$
 */
#ifndef LWSDK_CMDSEQ_H
#define LWSDK_CMDSEQ_H

#include <lwtypes.h>
#include <lwdyna.h>
#include <lwmeshedt.h>

#define LWMODCOMMAND_CLASS      "CommandSequence"
#define LWMODCOMMAND_VERSION     4

/* $wrapper: type=access, name=LWModCommand$ */
typedef struct st_LWModCommand
{
    void                 *data;
    LWCStringUTF8         argument;
    LWCommandCode       (*lookup)           (void *, LWCStringUTF8 cmdName);
    /* $argument: method=LWModCommand:execute, arg6=out:DynaValue:$ */
    int                 (*execute)          (void *, LWCommandCode cmd, int argc, const DynaValue *argv, EltOpSelect, DynaValue *result);
    MeshEditBegin        *editBegin;
    int                 (*evaluate)         (void *, LWCStringUTF8 command);
    void                (*undoGroupBegin)   (void);
    void                (*undoGroupEnd)     (void);
    MeshEditBegin2       *editBegin2;
} LWModCommand;

#define CSERR_NONE   0
#define CSERR_MEMORY     1
#define CSERR_IO     2
#define CSERR_USERABORT  4
#define CSERR_ARGCOUNT   2901
#define CSERR_ARGTYPE    2902
#define CSERR_ARGVALUE   2903
#define CSERR_OPFAILURE  2904
#define CSERR_BADSEL     2905

#endif
