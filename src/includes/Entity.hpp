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
    std::tuple<Components&...> pools;
    //auto mask;

    explicit Entity();
    ~Entity();                                // Destructor
    Entity(const Entity& other); // Constructor de copia
    Entity(Entity&& other) noexcept; // Constructor de movimiento
    Entity& operator=(const Entity& other); // Asignación copia
    Entity& operator=(Entity&& other) noexcept; // Asignación movimiento
};


}