#include "./includes/Entity.hpp"
#include "./includes/Macros.hpp"

namespace Engine{

template<typename... Components>
template<typename T>
FORCEINLINE void Entity<Components...>::setComponent(T** component){
    std::get<T**>(comps) = component;
}

}