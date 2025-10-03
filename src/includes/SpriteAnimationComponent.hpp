#pragma once
#include <vector>
#include <type_traits>
#include "Macros.hpp"
#include "SpriteComponent.hpp
#include <concepts>
#include <utility>   // std::move
#include <algorithm> // std::transform
namespace Engine{

template<typename Memory>
concept MemoryType = requires(Memory a, SpriteComponent comp) {
    { a.template emplace<SpriteComponent>(std::move(comp)) }
        -> std::convertible_to<SpriteComponent**>;
};

template<std::size_t size>
class SpriteAnimationComponent{

private:
    std::array<SpriteComponent**, size> pixels;
    bool Enabled;
    std::size_t Mask;
public:

    

    SpriteAnimationComponent() = default;
    template<MemoryType Memory>
    SpriteAnimationComponent(Memory* mem,std::array<SpriteComponent, width*height>&& input);
    ~SpriteAnimationComponent() = default;                                // Destructor
    SpriteAnimationComponent(const SpriteAnimationComponent& other) = default; // Constructor de copia
    SpriteAnimationComponent(SpriteAnimationComponent&& other) noexcept = default; // Constructor de movimiento
    SpriteAnimationComponent& operator=(const SpriteAnimationComponent& other) = default; // Asignación copia
    SpriteAnimationComponent& operator=(SpriteAnimationComponent&& other) noexcept = default; // Asignación movimiento

public:
    FORCEINLINE std::size_t getWidth() const;
    FORCEINLINE std::size_t getHeight() const;
    FORCEINLINE bool getEnabled() const;
    FORCEINLINE char getMask() const;

public:

};


}