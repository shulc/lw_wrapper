/*
 * LWSDK Header File
 *
 * LWNODEEDITOR.H -- LightWave Node Editor Functions.
 *
 *$copyright$
 */
#ifndef LWSDK_NODEEDITOR_H
#define LWSDK_NODEEDITOR_H

#include <lwtypes.h>
#include <lwserver.h>
#include <lwrender.h>
#include <lwnodes.h>
#include <lwaovs.h>

#define LWNODEEDITORFUNCS_GLOBAL "NodeEditorFuncs 7"

typedef int nodeAutoSizeFunc(NodeEditorID, void* userData, void* autoSizeData, double[3][2]);
// Autosize function, which is used when calling NodeAutosize, from LWNodeUtilityFuncs (lwnodes.h)

typedef void nodeEditorUpdateFunc(NodeEditorID);
// Update function, which is called when "Instance Update" global function is called with LWNODE_HCLASS.


// This is the root (Destination) node for the editor.
/* $wrapper: type=ignore, name=LWRootNode$ */
typedef struct LWRootNode_t {
    NodePreviewType previewType;
    LWError         (*init)(NodeEditorID, int); // Init for the root node.
    LWError         (*newTime)(NodeEditorID, LWFrame, LWTime); // newTime for the root node.
    void            (*cleanup)(NodeEditorID); // Cleanup for the root node.
    LWXPanelID      (*panel)(NodeEditorID); // Interface panel function, for the embedded panels.
    LWError         (*options)(NodeEditorID); // Options is called when no panel is defined for the root node.
    void            (*preview)(NodeEditorID vinst, LWShadingGeometry* na, LWDVector pcolor); // Preview function to draw the preview sphere for the root node.
    void            (*customPreview)(NodeEditorID vinst, int w, int h); // Custom preview function, for doing custom previews for the root node.
} LWRootNode;

// This is the input node for the editor.
/* $wrapper: type=ignore, name=LWInputNode$ */
typedef struct LWInputNode_t {
    LWError         (*init)(NodeEditorID, int); // Init for the input node.
    LWError         (*newTime)(NodeEditorID, LWFrame, LWTime); // newTime for the input node.
    void            (*cleanup)(NodeEditorID); // Cleanup for the input node.
    void            (*evaluate)(NodeEditorID, LWShadingGeometry*, NodeOutputID, NodeValue);
    LWXPanelID      (*panel)(NodeEditorID); // Interface panel function, for the embedded panels.
    LWError         (*options)(NodeEditorID); // Options is called when no panel is defined for the input node.
} LWInputNode;

/* $wrapper: type=global, name=LWNodeEditorFuncs$ */
/* $wrapper: type=ignore, name=LWNodeEditorFuncs, arg=create$ */
/* $wrapper: type=ignore, name=LWNodeEditorFuncs, arg=destroy$ */
/* $wrapper: type=ignore, name=LWNodeEditorFuncs, arg=rename$ */
/* $wrapper: type=ignore, name=LWNodeEditorFuncs, arg=setUpdateFunc$ */
/* $wrapper: type=ignore, name=LWNodeEditorFuncs, arg=init$ */
/* $wrapper: type=ignore, name=LWNodeEditorFuncs, arg=newTime$ */
/* $wrapper: type=ignore, name=LWNodeEditorFuncs, arg=cleanup$ */
/* $wrapper: type=ignore, name=LWNodeEditorFuncs, arg=addInput$ */
/* $wrapper: type=ignore, name=LWNodeEditorFuncs, arg=remInput$ */
/* $wrapper: type=ignore, name=LWNodeEditorFuncs, arg=addOutput$ */
/* $wrapper: type=ignore, name=LWNodeEditorFuncs, arg=remOutput$ */
/* $wrapper: type=ignore, name=LWNodeEditorFuncs, arg=setEnvGroup$ */
/* $wrapper: type=ignore, name=LWNodeEditorFuncs, arg=setAutosize$ */
/* $wrapper: type=ignore, name=LWNodeEditorFuncs, arg=setUserData$ */
/* $wrapper: type=ignore, name=LWNodeEditorFuncs, arg=getUserData$ */
/* $wrapper: type=ignore, name=LWNodeEditorFuncs, arg=getState$ */
/* $wrapper: type=ignore, name=LWNodeEditorFuncs, arg=setState$ */
/* $wrapper: type=ignore, name=LWNodeEditorFuncs, arg=getParentEditorID$ */
/* $wrapper: type=ignore, name=LWNodeEditorFuncs, arg=setContext$ */
/* $wrapper: type=ignore, name=LWNodeEditorFuncs, arg=usedItems$ */
typedef struct LWNodeEditorFuncs_t {

    NodeEditorID        (*create)(LWCStringUTF8 name, LWCStringUTF8 title, LWRootNode*, LWInputNode*, void*, NodeEditorID); // Create a node editor ID.
    void                (*destroy)(NodeEditorID); // Destroy a node editor ID.

    void                (*rename)(LWCStringUTF8 title, NodeEditorID); // Rename the editor. It is essentially the title for the editor window.

    void                (*setUpdateFunc)(NodeEditorID, nodeEditorUpdateFunc*); // Set the update function for the editor.

    LWError             (*copy)(NodeEditorID, NodeEditorID); // Copy the node editor data.
    LWError             (*save)(NodeEditorID, const LWSaveState*); // Save the node editor data.
    LWError             (*load)(NodeEditorID, const LWLoadState*); // Load the node editor data.

    // init, newTime, and cleanup are the same as in LWRenderFuncs.
    LWError             (*init)(NodeEditorID, int);
    LWError             (*newTime)(NodeEditorID, LWFrame, LWTime);
    void                (*cleanup)(NodeEditorID);
    // Init needs to be called before any attempt to evaluate the inputs from the destination node.
    // Cleanup needs to be called after rendering is finished.

    NodeInputID         (*addInput)(NodeEditorID, ConnectionType, LWCStringASCII name, NodeInputEvent*); // Add an input to the root node.
    void                (*remInput)(NodeEditorID, NodeInputID); // Remove an input from the root node.

    NodeOutputID        (*addOutput)(NodeEditorID, ConnectionType, LWCStringASCII name); // Add an output to the input node.
    void                (*remOutput)(NodeEditorID, NodeOutputID); // Remove an output from the input node.

    void                (*setEnvGroup)(NodeEditorID, LWChanGroupID); // Set the envelope group for the editor. All node envelope groups are parented into this group.
    void                (*setAutosize)(NodeEditorID, nodeAutoSizeFunc*, void* autoSizeData); // Set the autosize function for the editor.

    void                (*setUserData)(NodeEditorID, void*); // Set the userdata for this editor.
    void                *(*getUserData)(NodeEditorID); // Get the userdata from this editor.

    int                 (*numberOfNodes)(NodeEditorID); // Returns the number of nodes in this editor.
    NodeID              (*nodeByIndex)(NodeEditorID, unsigned int index); // Returns a node by index from this editor.

    unsigned int        (*numInputs)(NodeEditorID);
    NodeInputID         (*getInputByName)(NodeEditorID, LWCStringASCII name);
    NodeInputID         (*getInputByIndex)(NodeEditorID, int);
    // These return an NodeInputID from the destination node,
    // which can be used to evaluate an input from the destination,
    // using the NodeInputFuncs global evaluate.

    unsigned short int  (*getState)(NodeEditorID); // Get the state. Enabled/Disabled.
    void                (*setState)(NodeEditorID, unsigned short int); // Set the state.

    int                 (*OpenNodeEditor)(NodeEditorID); // Open the editor window.
    int                 (*isOpenNodeEditor)(NodeEditorID); // Is the node editor open, and set to this NodeEditorID?
    NodeEditorID        (*currentNodeEditorID)(void); // Returns the NodeEditorID of the open Node Editor window, or NULL if not open.

    NodeID              (*getRootNodeID)(NodeEditorID); // Get a NodeID for the root node;
    NodeID              (*getInputNodeID)(NodeEditorID); // Get a NodeID for the input node;
    NodeEditorID        (*getEditorID)(NodeID); // Get the NodeEditorID for a node.
    NodeEditorID        (*getParentEditorID)(NodeEditorID); // Get the parent NodeEditorID for a NodeEditorID.

    LWError             (*connect)(NodeOutputID, NodeInputID); // Create a connection from the output to the input.
    NodeID              (*addNode)(NodeEditorID, LWCStringUTF8 server_name); // Add a node to the flow using a server name.
    void                (*destroyNode)(NodeID); // Destroy a node.
    void                (*setXY)(NodeID, int, int); // Set the X and Y coordinates for the node.

    void                (*setContext)(NodeEditorID, LWCStringASCII context); // Set the context for the Node Editor
    LWCStringASCII      (*getContext)(NodeEditorID); // Get the context from the Node Editor

    const LWItemID*     (*usedItems)(NodeEditorID); // Returns the used items for the whole Node Editor and it's nodes.

    void                (*reset)(NodeEditorID); // Destroys all nodes except the root and input nodes.
} LWNodeEditorFuncs;

#endif
