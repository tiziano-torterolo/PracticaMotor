#include "./includes/Memory.hpp"

namespace Engine{
//******************************************************************************************************************************************************* */
template<typename... Components>
Memory<Components...>::Memory(std::size_t n)
    : pools() { reserve(n); }

template<typename... Components>
Memory<Components...>::~Memory(){}                                

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
//******************************************************************************************************************************************************* */


template<typename... Components>
constexpr void Memory<Components...>::reserve(std::size_t n) {
    (getPool<Components>().reserve(n),...);
}

template<typename... Components>
template<typename T>
__forceinline std::vector<T>& Memory<Components...>::getPool() {
    return std::get<std::vector<T>>(pools);
}

template<typename... Components>
template<typename T, typename... Args>
inline void Memory<Components...>::emplace(Args&&... args) {
    getPool<T>().emplace_back(std::forward<Args>(args)...);
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