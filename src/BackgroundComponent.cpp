#include "./includes/BackgroundComponent.hpp"

namespace Engine{



template<std::size_t width,std::size_t height>
template<class T>
requires MemoryType<T, ASCIIPixelComponent>
BackgroundComponent<width,height>::BackgroundComponent(T* mem,std::array<ASCIIPixelComponent,width*height>&& input)
    : pixels(), Enabled(true){
    std::transform(
        input.begin(), input.end(), pixels.begin(),
        [&](ASCIIPixelComponent& comp) {
            return mem->template emplace<ASCIIPixelComponent>(std::move(comp));
        }
    );  
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

}
