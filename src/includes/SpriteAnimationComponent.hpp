#pragma once
#include <vector>
#include <type_traits>
#include "Macros.hpp"
#include <utility>   // std::move
#include <algorithm> // std::transform
namespace Engine{

template<DrawableSprite Sprite ,std::size_t size>
class SpriteAnimationComponent{

private:
    std::array<Sprite** , size> pixels;
    std::size_t currentSprite;
    bool Enabled;
public:

    SpriteAnimationComponent() = default;
    template<MemoryType Memory>
    requires MemoryType<Memory, Sprite>
    SpriteAnimationComponent(Memory* mem,std::array<Sprite, size>&& input);  //Igual que el de abajo pero mas ineficiente supongo

    template<MemoryType Memory>
    requires MemoryType<Memory, Sprite>
    SpriteAnimationComponent(Memory* mem,Sprite*&& input);  //Crear a travez de un arreglo de sprite components no creado en memory

    template<MemoryType Memory>
    requires MemoryType<Memory, Sprite>
    SpriteAnimationComponent(Memory* mem,Sprite*** input);  //Crear a travez de un arreglo de sprite components ya creado en memory

    template<typename Memory>
    requires MemoryType<Memory, Sprite>
    SpriteAnimationComponent(Memory*, std::initializer_list<Sprite**>&& );  //Crear a travez de un arreglo de Sprite ya creado en memory

    ~SpriteAnimationComponent() = default;                                // Destructor
    SpriteAnimationComponent(const SpriteAnimationComponent& other) = default; // Constructor de copia
    SpriteAnimationComponent(SpriteAnimationComponent&& other) noexcept = default; // Constructor de movimiento
    SpriteAnimationComponent& operator=(const SpriteAnimationComponent& other) = default; // Asignación copia
    SpriteAnimationComponent& operator=(SpriteAnimationComponent&& other) noexcept = default; // Asignación movimiento

public:

    FORCEINLINE void  updateSprite(std::size_t);
    FORCEINLINE Sprite** getSprite() const;

public:

};


}