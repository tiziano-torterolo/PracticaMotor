#pragma once
#include <vector>
#include <iostream>
#include <type_traits>
#include "Macros.hpp"
namespace Engine{

class ASCIIPixelComponent{

public:

    enum class ColorFG {
        Default = 39,
        Black = 30, Red = 31, Green = 32, Yellow = 33,
        Blue = 34, Magenta = 35, Cyan = 36, White = 37,
        BrightBlack = 90, BrightRed = 91, BrightGreen = 92, BrightYellow = 93,
        BrightBlue = 94, BrightMagenta = 95, BrightCyan = 96, BrightWhite = 97
    };


    enum class ColorBG {
        Default = 49,
        Black = 40, Red = 41, Green = 42, Yellow = 43,
        Blue = 44, Magenta = 45, Cyan = 46, White = 47,
        BrightBlack = 100, BrightRed = 101, BrightGreen = 102, BrightYellow = 103,
        BrightBlue = 104, BrightMagenta = 105, BrightCyan = 106, BrightWhite = 107
    };

private:

    char info[15] = "\033[49;30mX\033[0m";
    unsigned char text='X';
    ColorBG bg = ASCIIPixelComponent::ColorBG::Default;
    ColorFG fg = ASCIIPixelComponent::ColorFG::Default;
public:
    ASCIIPixelComponent() = default;
    ASCIIPixelComponent(unsigned char ,ASCIIPixelComponent::ColorBG, ASCIIPixelComponent::ColorFG);
    ~ASCIIPixelComponent() = default;                                // Destructor
    ASCIIPixelComponent(const ASCIIPixelComponent& other) = default; // Constructor de copia
    ASCIIPixelComponent(ASCIIPixelComponent&& other) noexcept = default; // Constructor de movimiento
    ASCIIPixelComponent& operator=(const ASCIIPixelComponent& other) = default; // Asignación copia
    ASCIIPixelComponent& operator=(ASCIIPixelComponent&& other) noexcept = default; // Asignación movimiento


public:

    FORCEINLINE void setBackground(ASCIIPixelComponent::ColorBG bg);
    FORCEINLINE void setForeground(ASCIIPixelComponent::ColorFG fg);
    FORCEINLINE void setChar(char text);

    FORCEINLINE const ASCIIPixelComponent::ColorBG getBackground();
    FORCEINLINE const ASCIIPixelComponent::ColorFG getForeground();
    FORCEINLINE const unsigned char getChar();

    const char* str();

    friend std::ostream& operator<<(std::ostream& os, const ASCIIPixelComponent& pc);

};


}