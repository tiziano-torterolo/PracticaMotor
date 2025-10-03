#include "./includes/Memory.hpp"
#include "Memory.hpp"

namespace Engine{


//******************************************************************************************************************************************************* */
template<typename... Components>
Memory<Components...>::Memory(std::size_t n) 
    :   pools{SlotMap<Components>(n)...} ,entities(n){}

template<typename... Components>
Memory<Components...>::~Memory() = default   ;

template<typename... Components>
template<typename... Sizes>
Memory<Components...>::Memory(std::size_t entityCount, Sizes... sizes)
    : pools{SlotMap<Components>(sizes)...}, entities(entityCount) {
        static_assert(sizeof...(Sizes) == sizeof...(Components),"Debe haber un tamaño por cada componente");
    }

/*      
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
template<typename... Cs, typename... Args>
auto Memory<Components...>::createEntity(Args&&... args) {
    auto entityRef = entities.create();
    auto argsTuple = std::forward_as_tuple(std::forward<Args>(args)...);

    [&]<std::size_t... I>(std::index_sequence<I...>) {
        ((*entityRef)->setComponent(
            getPool<Cs>().create(std::get<I>(argsTuple))
        ), ...);
    }(std::index_sequence_for<Cs...>{});
    
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
inline auto Memory<Components...>::begin() {
    return entities.begin();
}

template<typename... Components>
inline auto Memory<Components...>::end() {
    return entities.end();
}

template<typename... Components>
template<typename T>
void Memory<Components...>::remove(T& t){}

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