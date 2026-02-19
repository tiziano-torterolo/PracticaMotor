#pragma once
#include <tuple>
#include <type_traits>
#include <concepts>
#include "Macros.hpp"


namespace Engine{


template<typename... Comps>
class Component
{
private:

    template<typename T>
    struct ComponentNode
    {
        T** ptr;
        bool active;
        bool owned;
    };
public:
    
    Component(Component** parent = nullptr);

    ~Component();

    template<typename T>
    FORCEINLINE T** getChild();

    template<typename T>
    FORCEINLINE T** getParent();

    template<typename T>
    FORCEINLINE T** getChild() const; 

    template<typename T>
    FORCEINLINE T** getParent() const;

    FORCEINLINE void setParent(void* parent);

    template<typename T>
    FORCEINLINE void setChild(T** child, bool owned = true);

    template<typename Memory>
    requires MemoryType<Memory, Comps...>
    void destroy(Memory* mem);

    template<typename T,typename Memory>
    requires MemoryType<Memory, T>
    void destroyComponent(Memory* mem);

protected:

    std::tuple<ComponentNode<Comps>...> children;
    Component** parent;


};


}