#include "./includes/SpriteComponent.hpp"
#include "./includes/ASCIIPixelComponent.hpp"

namespace Engine{

template<std::size_t width,std::size_t height,Positionable Position>
template<typename Memory>
requires MemoryType<Memory, ASCIIPixelComponent>
SpriteComponent<width,height,Position>::SpriteComponent(Memory* mem,std::array<ASCIIPixelComponent, width*height>&& input)
    : pixels(), Enabled(true), pos(nullptr), PositionOwned(false){
    std::transform(
        input.begin(), input.end(), pixels.begin(),
        [&](ASCIIPixelComponent& comp) {
            return mem->template emplace<ASCIIPixelComponent>(std::move(comp));
        }
    );  
}

template<std::size_t width,std::size_t height,Positionable Position>
template<typename Memory>
requires MemoryType<Memory, ASCIIPixelComponent>
SpriteComponent<width,height,Position>::SpriteComponent(Memory* mem,ASCIIPixelComponent*&& input)
    : pixels(), Enabled(true), pos(nullptr), PositionOwned(false){
    for(std::size_t i=0;i<width*height;++i){
        pixels[i] = mem->template emplace<ASCIIPixelComponent>(std::move(input[i]));
    }
}

template<std::size_t width,std::size_t height,Positionable Position>
template<typename Memory>
requires MemoryType<Memory, ASCIIPixelComponent>
SpriteComponent<width,height,Position>::SpriteComponent(Memory* mem,unsigned char* chars,ASCIIPixelComponent::ColorBG* cbg, ASCIIPixelComponent::ColorFG* fbg)
    : pixels(), Enabled(true), pos(nullptr), PositionOwned(false){
    for (std::size_t i = 0; i < width * height; ++i) {
        pixels[i] = mem->template emplace<ASCIIPixelComponent>(chars[i], cbg[i], fbg[i]);
    }
}

template<std::size_t width, std::size_t height,Positionable Position>
template<typename Memory>
requires MemoryType<Memory, ASCIIPixelComponent>
SpriteComponent<width, height,Position>::SpriteComponent(Memory* mem,std::initializer_list<unsigned char>&& chars_list,std::initializer_list<ASCIIPixelComponent::ColorBG>&& cbg_list, std::initializer_list<ASCIIPixelComponent::ColorFG>&& fbg_list)
    : pixels(), Enabled(true), pos(nullptr), PositionOwned(false)
{
    auto it_char = chars_list.begin();
    auto it_cbg  = cbg_list.begin();
    auto it_fbg  = fbg_list.begin();

    std::size_t pixel_index = 0;

    for (; it_char != chars_list.end() &&
           it_cbg  != cbg_list.end()  &&
           it_fbg  != fbg_list.end();
         ++it_char, ++it_cbg, ++it_fbg)
    {
        pixels[pixel_index++] = mem->template emplace<ASCIIPixelComponent>(
            *it_char, *it_cbg, *it_fbg
        );

        if (pixel_index >= width * height)
            break;
    }
}

template<std::size_t width,std::size_t height,Positionable Position>
template<typename Memory>
requires MemoryType<Memory, ASCIIPixelComponent>
SpriteComponent<width,height,Position>::SpriteComponent(Memory* /*mem*/, ASCIIPixelComponent*** input)
    : pixels(), Enabled(true), pos(nullptr), PositionOwned(false)
{
    for (std::size_t i = 0; i < width * height; ++i) {
        // input proporciona punteros a ASCIIPixelComponent** ya emplaced en Memory
        pixels[i] = input[i];
    }
}


// -----------------------------------------------------------------------------
// Variantes que reciben Position
// -----------------------------------------------------------------------------

// array + Position&&
template<std::size_t width,std::size_t height,Positionable Position>
template<typename Memory>
requires MemoryType<Memory, ASCIIPixelComponent>
SpriteComponent<width,height,Position>::SpriteComponent(Memory* mem,std::array<ASCIIPixelComponent, width*height>&& input, Position&& position)
    : pixels(), Enabled(true), pos(nullptr), PositionOwned(true)
{
    std::transform(
        input.begin(), input.end(), pixels.begin(),
        [&](ASCIIPixelComponent& comp) {
            return mem->template emplace<ASCIIPixelComponent>(std::move(comp));
        }
    );

    // emplace Position into Memory and store pointer
    this->pos = mem->template emplace<Position>(std::forward<Position>(position));
}

// ASCIIPixelComponent*&& + Position&&
template<std::size_t width,std::size_t height,Positionable Position>
template<typename Memory>
requires MemoryType<Memory, ASCIIPixelComponent>
SpriteComponent<width,height,Position>::SpriteComponent(Memory* mem,ASCIIPixelComponent*&& input, Position&& position)
    : pixels(), Enabled(true), pos(nullptr), PositionOwned(true)
{
    for (std::size_t i = 0; i < width * height; ++i) {
        pixels[i] = mem->template emplace<ASCIIPixelComponent>(std::move(input[i]));
    }
    this->pos = mem->template emplace<Position>(std::forward<Position>(position));
}

// ASCIIPixelComponent*** + Position** (position ya creado en Memory)
template<std::size_t width,std::size_t height,Positionable Position>
template<typename Memory>
requires MemoryType<Memory, ASCIIPixelComponent>
SpriteComponent<width,height,Position>::SpriteComponent(Memory* /*mem*/,ASCIIPixelComponent*** input, Position** position)
    : pixels(), Enabled(true), pos(position), PositionOwned(false)
{
    for (std::size_t i = 0; i < width * height; ++i) {
        pixels[i] = input[i];
    }
}

// chars + colors + x,y -> emplace pixels y emplace Position(x,y)
template<std::size_t width,std::size_t height,Positionable Position>
template<typename Memory>
requires MemoryType<Memory, ASCIIPixelComponent>
SpriteComponent<width,height,Position>::SpriteComponent(Memory* mem,unsigned char* chars,ASCIIPixelComponent::ColorBG* cbg, ASCIIPixelComponent::ColorFG* fbg, std::size_t x, std::size_t y)
    : pixels(), Enabled(true), pos(nullptr), PositionOwned(true)
{
    for (std::size_t i = 0; i < width * height; ++i) {
        pixels[i] = mem->template emplace<ASCIIPixelComponent>(chars[i], cbg[i], fbg[i]);
    }
    this->pos = mem->template emplace<Position>(x, y);
}

// initializer_list + x,y
template<std::size_t width, std::size_t height,Positionable Position>
template<typename Memory>
requires MemoryType<Memory, ASCIIPixelComponent>
SpriteComponent<width, height,Position>::SpriteComponent(Memory* mem,std::initializer_list<unsigned char>&& chars_list,std::initializer_list<ASCIIPixelComponent::ColorBG>&& cbg_list, std::initializer_list<ASCIIPixelComponent::ColorFG>&& fbg_list, std::size_t x, std::size_t y)
    : pixels(), Enabled(true), pos(nullptr), PositionOwned(true)
{
    auto it_char = chars_list.begin();
    auto it_cbg  = cbg_list.begin();
    auto it_fbg  = fbg_list.begin();

    std::size_t pixel_index = 0;

    for (; it_char != chars_list.end() &&
           it_cbg  != cbg_list.end()  &&
           it_fbg  != fbg_list.end() &&
           pixel_index < width*height;
         ++it_char, ++it_cbg, ++it_fbg)
    {
        pixels[pixel_index++] = mem->template emplace<ASCIIPixelComponent>(*it_char, *it_cbg, *it_fbg);
    }
    for (; pixel_index < width*height; ++pixel_index) pixels[pixel_index] = nullptr;

    this->pos = mem->template emplace<Position>(x, y);
}


// destroy: si el componente interno es MemoryDestruible, llamamos a su destroy(mem),
// luego pedimos a mem->remove(comp) y ponemos el slot a nullptr.
template<std::size_t width,std::size_t height,Positionable Position>
template<typename Memory>
requires MemoryType<Memory, ASCIIPixelComponent>
void SpriteComponent<width,height,Position>::destroy(Memory* mem)
{
    for (std::size_t i = 0; i < width * height; ++i) {
        ASCIIPixelComponent** comp = pixels[i];
        if (!comp) continue;

        if constexpr (MemoryDestruible<ASCIIPixelComponent, Memory, ASCIIPixelComponent>) {
            call_destroy_if<ASCIIPixelComponent, Memory>(*comp, mem);
        }

        mem->remove(comp);
        pixels[i] = nullptr;
    }

    // manejar el componente pos (Position**)
    if (this->pos && this->PositionOwned) {

        Position** p = this->pos;
        if (*p) {
            if constexpr (MemoryDestruible<Position, Memory, Position>) {
                call_destroy_if<Position, Memory>(*p, mem);
            }
            mem->remove(p);
        }
        this->pos = nullptr;
    }
}



template<std::size_t width,std::size_t height,Positionable Position>
FORCEINLINE  std::size_t SpriteComponent<width,height,Position>::getWidth() const{
    return width;
}

template<std::size_t width,std::size_t height,Positionable Position>
FORCEINLINE  std::size_t SpriteComponent<width,height,Position>::getHeight() const{
    return height;
}

template<std::size_t width,std::size_t height,Positionable Position>
FORCEINLINE  bool SpriteComponent<width,height,Position>::getEnabled() const{
    return this->Enabled;
}

template<std::size_t width,std::size_t height,Positionable Position>
FORCEINLINE  char SpriteComponent<width,height,Position>::getMask() const{
    return this->Mask;
}

template<std::size_t width,std::size_t height,Positionable Position>
FORCEINLINE  auto SpriteComponent<width,height,Position>::begin() const{
    return this->pixels.begin();
}

template<std::size_t width,std::size_t height,Positionable Position>
FORCEINLINE  auto SpriteComponent<width,height,Position>::end() const{
    return this->pixels.end();
}

template<std::size_t width,std::size_t height,Positionable Position>
template<typename Memory>
requires MemoryType<Memory, Position>
void SpriteComponent<width,height,Position>::setPosition(Memory* mem, Position&& position)
{
    this->pos = mem->template emplace<Position>(std::forward<Position>(position));
    this->PositionOwned = true;
}

template<std::size_t width,std::size_t height,Positionable Position>
void SpriteComponent<width,height,Position>::setPosition(Position** position)
{
    this->pos = position;
    this->PositionOwned = false;
}




}

