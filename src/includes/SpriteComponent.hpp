#pragma once
#include <vector>
#include <type_traits>
#include "Macros.hpp"
#include "ASCIIPixelComponent.hpp"
#include <concepts>
#include <utility>   // std::move
#include <algorithm> // std::transform
namespace Engine{

template<typename Memory>
concept MemoryType = requires(Memory a, ASCIIPixelComponent comp) {
    { a.template emplace<ASCIIPixelComponent>(std::move(comp)) }
        -> std::convertible_to<ASCIIPixelComponent**>;
};
template<std::size_t width,std::size_t height>
class SpriteComponent{

private:
    std::array<ASCIIPixelComponent**, width*height> pixels;
    bool Enabled;
    std::size_t Mask;
public:

    

    SpriteComponent() = default;
    template<MemoryType Memory>
    SpriteComponent(Memory* mem,std::array<ASCIIPixelComponent, width*height>&& input);
    ~SpriteComponent() = default;                                // Destructor
    SpriteComponent(const SpriteComponent& other) = default; // Constructor de copia
    SpriteComponent(SpriteComponent&& other) noexcept = default; // Constructor de movimiento
    SpriteComponent& operator=(const SpriteComponent& other) = default; // Asignación copia
    SpriteComponent& operator=(SpriteComponent&& other) noexcept = default; // Asignación movimiento

public:
    FORCEINLINE std::size_t getWidth() const;
    FORCEINLINE std::size_t getHeight() const;
    FORCEINLINE bool getEnabled() const;
    FORCEINLINE char getMask() const;

public:

};


}