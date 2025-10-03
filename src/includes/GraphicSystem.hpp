#pragma once
#include "Memory.hpp"
#include <concepts>
namespace Engine{

template<typename Memory, typename... GraphicComponents>
class GraphicSystem{

private:
    /* data */

    Memory* mem;

public:
    //auto mask;

    explicit GraphicSystem(Memory* mem);
    ~GraphicSystem() = default;                                // Destructor
    GraphicSystem(const GraphicSystem& other) = default; // Constructor de copia
    GraphicSystem(GraphicSystem&& other) noexcept = default; // Constructor de movimiento
    GraphicSystem& operator=(const GraphicSystem& other) = default; // Asignación copia
    GraphicSystem& operator=(GraphicSystem&& other) noexcept = default; // Asignación movimiento

public:

    template<typename T>
    void update();

    void update();
};


}
/*
concept Drawable = requires(T a) {
    { a.setWidth() }  -> std::convertible_to<size_t>;
    { a.setHeight() } -> std::convertible_to<size_t>;
    { a.Enable() }    -> std::convertible_to<bool>;
    { a.mask() }      -> std::convertible_to<char>;
};
*/
