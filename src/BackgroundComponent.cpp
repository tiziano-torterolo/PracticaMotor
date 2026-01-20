#include "./includes/BackgroundComponent.hpp"

namespace Engine{



template<std::size_t width,std::size_t height>
template<class T>
requires MemoryType<T, ASCIIPixelComponent>
BackgroundComponent<width,height>::BackgroundComponent(T* mem,std::array<ASCIIPixelComponent,width*height>&& input)
    : pixels(), Enabled(true), ASCIIPixelComponentOwned(true){
    std::transform(
        input.begin(), input.end(), pixels.begin(),
        [&](ASCIIPixelComponent& comp) {
            return mem->template emplace<ASCIIPixelComponent>(std::move(comp));
        }
    );  
}

// Implementación del constructor que usa ASCIIPixelComponent*&&
template<std::size_t width,std::size_t height>
template<MemoryType Memory>
BackgroundComponent<width,height>::BackgroundComponent(Memory* mem,ASCIIPixelComponent*&& input)
    : pixels(), Enabled(true), ASCIIPixelComponentOwned(true){
    for(std::size_t i=0;i<width*height;++i){
        pixels[i] = mem->template emplace<ASCIIPixelComponent>(std::move(input[i]));
    }
}

// Crear desde arrays de caracteres y colores
template<std::size_t width,std::size_t height>
template<typename Memory>
requires MemoryType<Memory, ASCIIPixelComponent>
BackgroundComponent<width,height>::BackgroundComponent(Memory* mem,unsigned char* chars,ASCIIPixelComponent::ColorBG* cbg, ASCIIPixelComponent::ColorFG* fbg)
    : pixels(), Enabled(true), ASCIIPixelComponentOwned(true){
    for (std::size_t i = 0; i < width * height; ++i) {
        pixels[i] = mem->template emplace<ASCIIPixelComponent>(chars[i], cbg[i], fbg[i]);
    }
}

// Crear desde initializer_list
template<std::size_t width, std::size_t height>
template<typename Memory>
requires MemoryType<Memory, ASCIIPixelComponent>
BackgroundComponent<width, height>::BackgroundComponent(Memory* mem,std::initializer_list<unsigned char>&& chars_list,std::initializer_list<ASCIIPixelComponent::ColorBG>&& cbg_list, std::initializer_list<ASCIIPixelComponent::ColorFG>&& fbg_list)
    : pixels(), Enabled(true), ASCIIPixelComponentOwned(true)
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

// destroy: primero, si el componente interno es MemoryDestruible, llamamos a su destroy(mem)
// luego solicitamos a mem que lo remueva (mem->remove(comp)), y ponemos el slot a nullptr.
template<std::size_t width,std::size_t height>
template<typename Memory>
requires MemoryType<Memory, ASCIIPixelComponent>
void BackgroundComponent<width,height>::destroy(Memory* mem)
{
    if (this->ASCIIPixelComponentOwned)    {
        for (std::size_t i = 0; i < width * height; ++i) {
            ASCIIPixelComponent** comp = pixels[i];
            if (!comp) continue;

            // Si ASCIIPixelComponent define destroy(Memory*), lo invocamos
            if constexpr (MemoryDestruible<ASCIIPixelComponent, Memory, ASCIIPixelComponent>) {
                call_component_destroy<ASCIIPixelComponent, Memory>(*comp, mem);
            }

            // Pedimos a Memory que remueva la entrada (comp es T** según convención)
            mem->remove(comp);

            // limpiamos la referencia local
            pixels[i] = nullptr;
        }
    }
}

template<std::size_t width,std::size_t height>
FORCEINLINE  std::size_t BackgroundComponent<width,height>::getWidth() const{
    return width;
}

template<std::size_t width,std::size_t height>
FORCEINLINE  std::size_t BackgroundComponent<width,height>::getHeight() const{
    return height;
}

template<std::size_t width,std::size_t height>
FORCEINLINE  bool BackgroundComponent<width,height>::getEnabled() const{
    return this->Enabled;
}

template<std::size_t width,std::size_t height>
FORCEINLINE  char BackgroundComponent<width,height>::getMask() const{
    return this->Mask;
}

template<std::size_t width,std::size_t height>
FORCEINLINE  auto BackgroundComponent<width,height>::begin() const{
    return this->pixels.begin();
}

template<std::size_t width,std::size_t height>
FORCEINLINE  auto BackgroundComponent<width,height>::end() const{
    return this->pixels.end();
}

}
