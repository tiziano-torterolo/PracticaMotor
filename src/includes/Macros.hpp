#pragma once
#ifdef _WIN32
    #define FORCEINLINE __forceinline
#else
    #define FORCEINLINE inline __attribute__((always_inline))
#endif
namespace Engine{


}

