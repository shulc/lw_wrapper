#pragma once

#ifdef MODOSDK
#include <lx_mesh.hpp>
#endif

#ifdef LWSDK
#include <lwmeshedt.h>
#endif

namespace NSdk {

#ifdef MODOSDK
    using TMode = LXtMarkMode;
#endif

#ifdef LWSDK
    struct TMode {
        int Set{};
        int Clear{};
    };
#endif

} // namespace NSDK
