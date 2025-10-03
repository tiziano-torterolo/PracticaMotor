#include "./includes/Entity.hpp"
#include "./includes/Macros.hpp"

namespace Engine{

template<typename... Components>
template<typename T>
FORCEINLINE void Entity<Components...>::setComponent(T** component){
    std::get<T**>(comps) = component;
}

template<typename... Components>
template<typename T>
FORCEINLINE void Entity<Components...>::getComponent() const{
    return std::get<T**>(comps);
}

template<typename... Components>
FORCEINLINE void Entity<Components...>::setParent(Entity** parent){
    this->Parent = parent;
}

template<typename... Components>
FORCEINLINE auto Entity<Components...>::getParent() const{
    return this->Parent;
}

}