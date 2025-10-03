#include "./includes/ASCIIPixelComponent.hpp"
namespace Engine{

ASCIIPixelComponent::ASCIIPixelComponent(unsigned char text,ASCIIPixelComponent::ColorBG bg, ASCIIPixelComponent::ColorFG fg)
    : bg(bg) , fg(fg){
std::snprintf(this->info, 15, "\033[%d;%dm%c\033[0m", static_cast<int>(fg), static_cast<int>(bg), text);
}

FORCEINLINE void ASCIIPixelComponent::setBackground(ASCIIPixelComponent::ColorBG bg){
    this->bg = bg;
std::snprintf(this->info, 15, "\033[%d;%dm%c\033[0m", static_cast<int>(this->fg), static_cast<int>(this->bg), this->text);
}

FORCEINLINE void ASCIIPixelComponent::setForeground(ASCIIPixelComponent::ColorFG fg){
    this->fg = fg;
std::snprintf(this->info, 15, "\033[%d;%dm%c\033[0m", static_cast<int>(this->fg), static_cast<int>(this->bg), this->text);
}

FORCEINLINE void ASCIIPixelComponent::setChar(char text){
    this->text = text;
    std::snprintf(this->info, 15, "\033[%d;%dm%c\033[0m", static_cast<int>(this->fg), static_cast<int>(this->bg), this->text);
}


FORCEINLINE const ASCIIPixelComponent::ColorBG ASCIIPixelComponent::getBackground(){
    return this->bg;
}

FORCEINLINE const ASCIIPixelComponent::ColorFG ASCIIPixelComponent::getForeground(){
    return this->fg;
}

FORCEINLINE const unsigned char ASCIIPixelComponent::getChar(){
    return this->text;
}


const char* ASCIIPixelComponent::str(){
    return this->info;
}


std::ostream& operator<<(std::ostream& os, const ASCIIPixelComponent& pc) {
    os << pc.info;
    return os;
}

}
