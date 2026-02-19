#include "./includes/Component.hpp"
#include "Component.hpp"

namespace Engine{   

template <typename... Comps>
FORCEINLINE Component<Comps...>::Component(Component **parent) : parent(parent) {}

template <typename... Comps>
Component<Comps...>::~Component() = default;

template <typename... Comps>
template <typename T>
FORCEINLINE T **Component<Comps...>::getChild(){
    static_assert((std::is_same_v<T, Comps> || ...), "T must be one of the component types in the template parameter pack");
    auto& Node = std::get<Component<Comps...>::ComponentNode<T>>(children);
    return Node.active ? Node.ptr : nullptr;
}

template <typename... Comps>
template <typename T>
FORCEINLINE T **Component<Comps...>::getChild() const {
    return getChild<T>();
}


template <typename... Comps>
template <typename T>
FORCEINLINE void Component<Comps...>::setChild(T **child, bool owned) {
    static_assert((std::is_same_v<T, Comps> || ...), "T must be one of the component types in the template parameter pack");
    auto& Node = std::get<Component<Comps...>::ComponentNode<T>>(children);
    Node.ptr = child;
    Node.active = (child != nullptr);
    Node.owned = owned; 
}


template <typename... Comps>
template <typename Memory>
requires MemoryType<Memory, Comps...>
FORCEINLINE void Component<Comps...>::destroy(Memory *mem){
    (destroyComponent<Comps, Memory>(mem),...);
}

template <typename... Comps>
template <typename T,typename Memory>
requires MemoryType<Memory, T>
FORCEINLINE void Component<Comps...>::destroyComponent(Memory *mem){
    auto& Node = std::get<Component<Comps...>::ComponentNode<T>>(children);
    if (Node.active && Node.ptr) {
        mem->remove(Node.ptr);
        Node.ptr = nullptr;
        Node.active = false;
    }
}

}
