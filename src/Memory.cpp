#include "./includes/Memory.hpp"
#include "Memory.hpp"

namespace Engine{


//******************************************************************************************************************************************************* */
template <typename... Components>
Memory<Components...>::Memory(std::size_t n)
    : Memory(((void)Components{}, n)...)  // delega al otro constructor
{}

template<typename... Components>
Memory<Components...>::~Memory() = default   ;

template<typename... Components>
template<typename... Sizes>
Memory<Components...>::Memory(Sizes... sizes)
    : pools(std::forward<Sizes>(sizes)...)
{
    static_assert(sizeof...(Sizes) == sizeof...(Components),
                  "Debe haber un tamaño por cada componente");
}



/*      

template<typename... Components>
template<typename... Sizes>
Memory<Components...>::Memory(std::size_t entityCount, Sizes... sizes)
    : pools{SlotMap<Components>(sizes)...}, entities(entityCount) {
        static_assert(sizeof...(Sizes) == sizeof...(Components),"Debe haber un tamaño por cada componente");
    }

Temporalmente desactivo los construcotres de copia y movimiento porque me da paja hacer los 
Constructores de copia y movimiento del SlotMap   

template<typename... Components>
Memory<Components...>::Memory(const Memory& other)
    : pools(other.pools) {} // Constructor de copia

template<typename... Components>
Memory<Components...>::Memory(Memory&& other) noexcept
    : pools(std::move(other.pools)) {}  // Constructor de movimiento

template<typename... Components>
Memory<Components...>& Memory<Components...>::operator=(const Memory<Components...>& other){pools = other.pools;} // Asignación copia

template<typename... Components>
Memory<Components...>& Memory<Components...>::operator=(Memory<Components...>&& other) noexcept{pools = std::move(other.pools);} // Asignación movimiento
*/

//******************************************************************************************************************************************************* */




template<typename... Components>
constexpr void Memory<Components...>::reserve(std::size_t n) {
    (getPool<Components>().reserve(n),...);
}

template<typename... Components>
template<typename T>
FORCEINLINE SlotMap<T>& Memory<Components...>::getPool() {
    return std::get<SlotMap<T>>(pools);
}

template<typename... Components>
template<typename T, typename... Args>
auto Memory<Components...>::emplace(Args&&... args) {
    return getPool<T>().create(std::forward<Args>(args)...);
}

template<typename... Components>
template<typename T>
inline auto Memory<Components...>::begin() {
    return getPool<T>().begin();
}

template<typename... Components>
template<typename T>
inline auto Memory<Components...>::end() {
    return getPool<T>().end();
}

template<typename... Components>
template<typename T>
void Memory<Components...>::remove(T& t){
    if constexpr (MemoryDestruible<T, Memory, T>) {
        call_component_destroy<T, Memory>(t, this);
    }
    getPool<T>().remove(&t);
}

template<typename... Components>
template<typename T>
void Memory<Components...>::remove(T** t){
    if constexpr (MemoryDestruible<T, Memory, T>) {
        call_component_destroy<T, Memory>(*t, this);
    }
    getPool<T>().remove(t);
}

template<typename... Components>
template<typename T>
void Memory<Components...>::removeIf(T& t){}

template<typename... Components>
template<typename M>
void Memory<Components...>::forEach(M& t){}

template<typename... Components>
template<typename T,typename M>
void Memory<Components...>::forEach(M& t){}

}