#pragma once

#include "lxmesh.h"
#ifdef MODOSDK
#include <lx_mesh.hpp>
#endif

#ifdef LWSDK
#include <lwmeshedt.h>
#endif

namespace NSDK {

#ifdef MODOSDK
    using TMaskMode = LXtMarkMode;
#endif

#ifdef LWSDK
    using TMaskMode = int;
#endif


} // namespace NSDK
