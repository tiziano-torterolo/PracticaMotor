#pragma once
#include <vector>
#include <type_traits>
#include "Macros.hpp"
#include "ASCIIPixelComponent.hpp"
#include <concepts>
#include <utility>   // std::move
#include <algorithm> // std::transform
namespace Engine{

template<typename Memory, typename... Comps>
concept MemoryType = (requires(Memory a, Comps comp) {
    { a.template emplace<Comps>(std::move(comp)) } -> std::convertible_to<Comps**>;
} && ...);    

template<std::size_t width,std::size_t height>
class BackgroundComponent{

private:
    std::array<ASCIIPixelComponent**, width*height> pixels;
    bool Enabled;
    std::size_t Mask;
public:

    

    BackgroundComponent() = default;
    template<class Memory>
    requires MemoryType<Memory, ASCIIPixelComponent>
    BackgroundComponent(Memory* mem,std::array<ASCIIPixelComponent, width*height>&& input);
        template<MemoryType Memory>
    BackgroundComponent(Memory* mem,ASCIIPixelComponent*&& input);
    ~BackgroundComponent() = default;                                // Destructor
    BackgroundComponent(const BackgroundComponent& other) = default; // Constructor de copia
    BackgroundComponent(BackgroundComponent&& other) noexcept = default; // Constructor de movimiento
    BackgroundComponent& operator=(const BackgroundComponent& other) = default; // Asignación copia
    BackgroundComponent& operator=(BackgroundComponent&& other) noexcept = default; // Asignación movimiento

public:
    FORCEINLINE std::size_t getWidth() const;
    FORCEINLINE std::size_t getHeight() const;
    FORCEINLINE bool getEnabled() const;
    FORCEINLINE char getMask() const;

public:

};


}