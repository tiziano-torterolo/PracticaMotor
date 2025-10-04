#pragma once
#ifdef _WIN32
    #define FORCEINLINE __forceinline
#else
    #define FORCEINLINE inline __attribute__((always_inline))
#endif
namespace Engine{

template<typename Memory, typename... Comps>
concept MemoryType = (requires(Memory a, Comps comp) {
    { a.template emplace<Comps>(std::move(comp)) } ; 
    
} && ...);    
}

