#pragma once
#include <vector>
#include <type_traits>
#include "Macros.hpp"
#include "ASCIIPixelComponent.hpp"
#include "Component.hpp"
#include <concepts>
#include <utility>   // std::move
#include <algorithm> // std::transform
namespace Engine{

template<std::size_t width,std::size_t height,Positionable Position>
class SpriteComponent : public Component<Position>
{

private:
    std::array<ASCIIPixelComponent**, width*height> pixels;
    bool ASCIIPixelComponentOwned;
    bool Enabled;
    std::size_t Mask;

public:

    

    SpriteComponent() = default;
    
    template<typename Memory>
    requires MemoryType<Memory, ASCIIPixelComponent>
    SpriteComponent(Memory* mem,std::array<ASCIIPixelComponent, width*height>&& input);

    template<typename Memory>
    requires MemoryType<Memory, ASCIIPixelComponent>
    SpriteComponent(Memory* mem,ASCIIPixelComponent*&& input);  //Crear a travez de un arreglo de ASCIIPixelComponent no creado en memory

    template<typename Memory>
    requires MemoryType<Memory, ASCIIPixelComponent>
    SpriteComponent(Memory* mem,ASCIIPixelComponent*** input);  //Crear a travez de un arreglo de ASCIIPixelComponent ya creado en memory

    template<typename Memory>
    requires MemoryType<Memory, ASCIIPixelComponent>
    SpriteComponent(Memory*,unsigned char* ,ASCIIPixelComponent::ColorBG*, ASCIIPixelComponent::ColorFG*);  //Crear a travez de arreglos de chars y colores

    template<typename Memory>
    requires MemoryType<Memory, ASCIIPixelComponent>
    SpriteComponent(Memory*,std::initializer_list<unsigned char>&& ,std::initializer_list<ASCIIPixelComponent::ColorBG>&&, std::initializer_list<ASCIIPixelComponent::ColorFG>&&);  //Crear a travez de initializer_list de chars y colores
    
    // Variantes que reciben además un Position
    template<typename Memory>
    requires MemoryType<Memory, ASCIIPixelComponent>
    SpriteComponent(Memory* mem,std::array<ASCIIPixelComponent, width*height>&& input, Position&& position);

    template<typename Memory>
    requires MemoryType<Memory, ASCIIPixelComponent>
    SpriteComponent(Memory* mem,ASCIIPixelComponent*&& input, Position&& position);  // input no creado en memory

    template<typename Memory>
    requires MemoryType<Memory, ASCIIPixelComponent>
    SpriteComponent(Memory* mem,ASCIIPixelComponent*** input, Position** position);  // input ya creado en memory, position ya creado en memory

    template<typename Memory>
    requires MemoryType<Memory, ASCIIPixelComponent>
    SpriteComponent(Memory* mem,unsigned char* chars,ASCIIPixelComponent::ColorBG* cbg, ASCIIPixelComponent::ColorFG* fbg, std::size_t x, std::size_t y);

    template<typename Memory>
    requires MemoryType<Memory, ASCIIPixelComponent>
    SpriteComponent(Memory* mem,std::initializer_list<unsigned char>&& chars_list,std::initializer_list<ASCIIPixelComponent::ColorBG>&& cbg_list, std::initializer_list<ASCIIPixelComponent::ColorFG>&& fbg_list, std::size_t x, std::size_t y);
    
    

    // Destructor personalizado que limpia del Memory (declaración)
    template<typename Memory>
    requires MemoryType<Memory, ASCIIPixelComponent>
    void destroy(Memory* mem);

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
    FORCEINLINE auto begin() const;
    FORCEINLINE auto end() const;

    template<typename Memory>
    requires MemoryType<Memory, Position>
    void setPosition(Memory* mem, Position&& position);

    // Set position to an existing Position** (SpriteComponent does NOT own the Position)
    void setPosition(Position** position);


public:

};


}