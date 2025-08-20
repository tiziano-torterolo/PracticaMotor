#include "./includes/Memory.hpp"

namespace Engine{
//******************************************************************************************************************************************************* */
template<typename... Components>
Memory<Components...>::Memory(std::size_t n) 
    :   pools{ SlotMap<Components>(n)... } ,entities(n){}

template<typename... Components>
Memory<Components...>::~Memory(){}   

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
inline void Memory<Components...>::emplace(Args&&... args) {
    getPool<T>().create(std::forward<Args>(args)...);
}

template<typename... Components>
template<typename... Cs, typename... Args>
auto Memory<Components...>::createEntity(Args&&... args) {
    // cada componente de Cs se construye con un argumento de Args
    // auto entityPtr = entities.create(); // Entity<Components...>**

    // // Para los argumentos, los recibimos en un tuple
    // auto argTuple = std::forward_as_tuple(std::forward<Args>(args)...);

    // // Creamos y asociamos cada componente Cs con sus args
    // ([&] {
    //     // Cada Cs toma su argumento en la posición correspondiente
    //     auto compPtr = getPool<Cs>().create(std::get<Cs>(argTuple));
    //     (*entityPtr)->setComponent(compPtr);
    // }(), ...);
    static_assert(sizeof...(Cs) == sizeof...(Args),
                  "Debe haber un argumento por cada componente Cs");

    // 1) crear la entidad (Entity<Components...>**)
    auto entityPtr = entities.create();

    // // 2) emparejar Cs[i] con args[i]
    // auto argsTuple = std::forward_as_tuple(std::forward<Args>(args)...);
    // using CsTuple = std::tuple<Cs...>;

    // [&]<std::size_t... Is>(std::index_sequence<Is...>) {
    //     ( 
    //         (*entityPtr)->setComponent(
    //             // getPool del componente Cs[i]
    //             getPool<std::tuple_element_t<Is, CsTuple>>()
    //                 // create con el argumento args[i]
    //                 .create(std::get<Is>(argsTuple))
    //         )
    //     , ...);
    // }(std::index_sequence_for<Cs...>{});
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