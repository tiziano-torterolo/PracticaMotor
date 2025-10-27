#pragma once
#ifdef _WIN32
    #define FORCEINLINE __forceinline
#else
    #define FORCEINLINE inline __attribute__((always_inline))
#endif
#include <concepts>
namespace Engine{

template<typename Memory, typename... Comps>
concept MemoryType = (requires(Memory a, Comps comp) {
    { a.template emplace<Comps>(std::move(comp)) } ; 
} && ...);    

template<typename T>
concept Drawable = requires(T a) {
    { a.setWidth() }  -> std::convertible_to<std::size_t>;
    { a.setHeight() } -> std::convertible_to<std::size_t>;
    { a.Enable() }    -> std::convertible_to<bool>;
    { a.mask() }      -> std::convertible_to<char>;
    { a.begin() }      -> std::convertible_to<T**>;
    { a.end() }        -> std::convertible_to<T**>;
};
template<typename T>
concept Positionable = requires(T a) {
    { a.getX() } -> std::convertible_to<std::size_t>;
    { a.getY() } -> std::convertible_to<std::size_t>;
};

template<typename T, typename Memory, typename... Comps>
concept MemoryDestruible = MemoryType<Memory, Comps...> && requires(T t, Memory* mem) {
    { t.destroy(mem) } -> std::same_as<void>;
};

// helper: solo se instanciará cuando MemoryDestruible sea true
template<typename C, typename M>
requires MemoryDestruible<C, M, C>
static void call_destroy_if(C* c, M* mem) {
    c->destroy(mem);
}

}

