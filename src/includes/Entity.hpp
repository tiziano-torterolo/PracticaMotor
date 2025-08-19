#pragma once
#include <tuple>
#include <vector>
#include <type_traits>
namespace Engine{

template<typename... Components>
class Entity{

private:
    /* data */

public:
    std::tuple<Components**...> comps;
    //auto mask;

    Entity() = default;
    ~Entity() = default;                                // Destructor
    Entity(const Entity& other) = default; // Constructor de copia
    Entity(Entity&& other) noexcept = default; // Constructor de movimiento
    Entity& operator=(const Entity& other) = default; // Asignación copia
    Entity& operator=(Entity&& other) noexcept = default; // Asignación movimiento

public:

    template<typename T>
    void setComponent(T**);

};


}