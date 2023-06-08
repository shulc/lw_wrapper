/*
 * LWSDK Header File
 *
 * LWENVEL.H -- LightWave Animation Envelopes and Channel Info
 *
 *$copyright$
 */
#ifndef LWSDK_ENVEL_H
#define LWSDK_ENVEL_H

#include <lwtypes.h>
#include <lwio.h>

typedef void *LWEnvelopeID;
typedef void *LWChanGroupID;
typedef void *LWEnvKeyframeID;

typedef enum {
        LWKEY_VALUE,
        LWKEY_TIME,
        LWKEY_SHAPE,
        LWKEY_TENSION,
        LWKEY_CONTINUITY,
        LWKEY_BIAS,
        LWKEY_PARAM_0,
        LWKEY_PARAM_1,
        LWKEY_PARAM_2,
        LWKEY_PARAM_3,
        LWKEY_TAN_IN,
        LWKEY_TAN_OUT
} LWKeyTag;

/* Envelope Type */

#define LWET_FLOAT        2
#define LWET_DISTANCE     3
#define LWET_PERCENT      4
#define LWET_ANGLE        5

typedef enum {
        LWENVTAG_VISIBLE,
        LWENVTAG_PREBEHAVE,
        LWENVTAG_POSTBEHAVE,
        LWENVTAG_KEYCOUNT,
        LWENVTAG_VALUE,
        LWENVTAG_SUBTYPE,
        LWENVTAG_TYPE
} LWEnvTag;


typedef enum {
        LWEEVNT_DESTROY,
        LWEEVNT_KEY_INSERT,
        LWEEVNT_KEY_DELETE,
        LWEEVNT_KEY_VALUE,
        LWEEVNT_KEY_TIME,
        LWCEVNT_VALUE,  // Any change to channel, from channel event only
        LWCEVNT_TRACK,
        LWCEVNT_CREATE,
        LWCEVNT_EDITTEST,
        LWEEVNT_RENAME  // group has been renamed
} LWEnvEvent;

typedef int (*LWEnvEventFunc) (void *data, LWEnvelopeID env, LWEnvEvent event, void *eventData);

/****
 *
 * The existing EnvAccess API supported multi-valued keyframes.
 * These no longer exist.
 *
 * The previous syetem also left the number of channels indeterminate
 * until the UI was called, and exposed structures without accepting
 * independently created instances of these.
 *
 * The replacement global is "Animation Envelopes". Multiple channels
 * will be organized into groups, and plugins can logically gather
 * their parameters.
 *
 ****
 */
#define LWENVELOPEFUNCS_GLOBAL "Animation Envelopes 4"

/* $wrapper: type=global, name=LWEnvelopeFuncs$ */
typedef struct st_LWEnvelopeFuncs {
  LWEnvelopeID     (*create)       ( LWChanGroupID group, LWCStringUTF8 name, int type );
  void             (*destroy)      ( LWEnvelopeID  env );
  LWChanGroupID    (*createGroup)  ( LWChanGroupID parent, LWCStringUTF8 name );
  void             (*destroyGroup) ( LWChanGroupID group);
  /* $rename: class=LWEnvelopeFuncs, method=copy, arg=from, name=fromenv$ */
  LWError          (*copy)         ( LWEnvelopeID  to, LWEnvelopeID from);
  LWError          (*load)         ( LWEnvelopeID  env, const LWLoadState *load);
  LWError          (*save)         ( LWEnvelopeID  env, const LWSaveState *save);
  double           (*evaluate)     ( LWEnvelopeID  env, LWTime attime);
  int              (*edit)         ( LWChanGroupID group, LWEnvelopeID env, int flags, void *data);
  int              (*envAge)       ( LWEnvelopeID  env );
  LWEnvKeyframeID  (*createKey)    ( LWEnvelopeID  env, LWTime keytime, double value);
  void             (*destroyKey)   ( LWEnvelopeID  env, LWEnvKeyframeID key);
  LWEnvKeyframeID  (*findKey)      ( LWEnvelopeID  env, LWTime keytime);
  LWEnvKeyframeID  (*nextKey)      ( LWEnvelopeID  env, LWEnvKeyframeID key);
  LWEnvKeyframeID  (*prevKey)      ( LWEnvelopeID  env, LWEnvKeyframeID key);
  int              (*keySet)       ( LWEnvelopeID  env, LWEnvKeyframeID key, LWKeyTag tag, void *value);
  int              (*keyGet)       ( LWEnvelopeID  env, LWEnvKeyframeID key, LWKeyTag tag, void *value);
  int              (*setEnvEvent)  ( LWEnvelopeID  env, LWEnvEventFunc   ev, void *data);
  int              (*egSet)        ( LWEnvelopeID  env, LWChanGroupID group, int tag, void *value);
  int              (*egGet)        ( LWEnvelopeID  env, LWChanGroupID group, int tag, void *value);
  void             (*renameGroup)  ( LWChanGroupID group, LWCStringUTF8 name );
} LWEnvelopeFuncs;


/**********************************************************************/


/****
 *
 * The entire list of grouped envelopes can be accessed with the
 * "Channel Info" global. These envelopes may include plugin effects,
 * and are thus called channels, to distinguish them from the LWEnvelope
 * structures, which can be altered through keyframe manipulations. A
 * channel's underlying envelope data may also be read.
 ****
 */

#define LWCHANNELINFO_GLOBAL        "Channel Info 3"

typedef int (*LWChanEventFunc)(void *data, LWChannelID ch, int event, void *eventData);

/* $wrapper: type=global, name=LWChannelInfo$ */
typedef struct st_LWChannelInfo {
  /* next group, first on NULL in parent group or root on NULL */
  LWChanGroupID                       (*nextGroup)       ( LWChanGroupID parent, LWChanGroupID group);
  /* next channel, first on NULL in parent group or root on NULL */
  LWChannelID                         (*nextChannel)     ( LWChanGroupID parent, LWChannelID chan);
  LWCStringUTF8                       (*groupName)       ( LWChanGroupID group);
  LWCStringUTF8                       (*channelName)     ( LWChannelID   chan);
  LWChanGroupID                       (*groupParent)     ( LWChanGroupID group);
  LWChanGroupID                       (*channelParent)   ( LWChannelID   chan);
  int                                 (*channelType)     ( LWChannelID   chan);
  double                              (*channelEvaluate) ( LWChannelID   chan, LWTime chantime);
  LWEnvelopeID                        (*channelEnvelope) ( LWChannelID   chan);
  int                                 (*setChannelEvent) ( LWChannelID   chan,  LWChanEventFunc ev, void *data );
  LWCStringUTF8                       (*server)          ( LWChannelID   chan, LWCStringASCII cls, int idx );

  /* Version 2 additions, all index arg.s are 1-based, matching layout */
  unsigned int                        (*serverFlags)     ( LWChannelID   chan, LWCStringASCII cls, int idx );
  LWInstance                          (*serverInstance)  ( LWChannelID   chan, LWCStringASCII cls, int idx );
  /*  Return 1-based index, or 0 on failure */
  int                                 (*serverApply)     ( LWChannelID   chan, LWCStringASCII cls, LWCStringUTF8 name, int flags );
  void                                (*serverRemove)    ( LWChannelID   chan, LWCStringASCII cls, LWCStringUTF8 name, LWInstance inst );

} LWChannelInfo;

#endif
