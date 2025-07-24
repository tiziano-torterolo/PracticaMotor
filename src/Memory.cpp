#include "./includes/Memory.hpp"

//******************************************************************************************************************************************************* */
template<typename... Components>
Memory<Components...>::Memory(std::size_t n)
    : pools() { setSize(n); }

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
void Memory<Components...>::setSize(std::size_t n) {
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
inline auto Memory<Components...>::begin() -> typename std::vector<T>::iterator{
    return getPool<T>().begin();
}

template<typename... Components>
template<typename T>
inline auto Memory<Components...>::end() -> typename std::vector<T>::iterator{
    return getPool<T>().end();
}

template<typename... Components>
template<typename T>
auto Memory<Components...>::begin() const {
    return getPool<T>().begin();
}

template<typename... Components>
template<typename T>
auto Memory<Components...>::end() const {
    return getPool<T>().end();
}