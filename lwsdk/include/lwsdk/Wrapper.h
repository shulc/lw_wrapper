// $copyright$

#ifndef LWCPP_WRAPPER_H
#define LWCPP_WRAPPER_H

#include <lwserver.h>
#include <lwsdk/Globals.h>

namespace lwsdk
{
#ifdef LW_INTERNAL
    void init_private_globals(GlobalFunc* global);
#endif

    /// Call before using the LW SDK C++ wrapper.
    inline void init_wrapper(GlobalFunc* global)
    {
        set_global(global);
#ifdef LW_INTERNAL
        init_private_globals(global);
#endif
    }
}

#endif // LWCPP_WRAPPER_H
