// Your First C++ Program
#include "./PrinteableComponent.hpp"
#include "./SlotMap.cpp"
#include "./Memory.cpp"
#include "./Entity.cpp"
#include <iostream>
#include <algorithm>
#include <array>
#include <chrono>
#include <thread>
#include <cstdlib> 
#include <memory>
#include <stdio.h>

#include <iostream>
#include <string>

class Printable {
public:
    // 🎨 Enum para colores de texto (foreground)
    enum class ColorFG {
        Default = 39,
        Black = 30, Red = 31, Green = 32, Yellow = 33,
        Blue = 34, Magenta = 35, Cyan = 36, White = 37,
        BrightBlack = 90, BrightRed = 91, BrightGreen = 92, BrightYellow = 93,
        BrightBlue = 94, BrightMagenta = 95, BrightCyan = 96, BrightWhite = 97
    };

    // 🎨 Enum para colores de fondo (background)
    enum class ColorBG {
        Default = 49,
        Black = 40, Red = 41, Green = 42, Yellow = 43,
        Blue = 44, Magenta = 45, Cyan = 46, White = 47,
        BrightBlack = 100, BrightRed = 101, BrightGreen = 102, BrightYellow = 103,
        BrightBlue = 104, BrightMagenta = 105, BrightCyan = 106, BrightWhite = 107
    };

private:
    
    


public:
    char text;
    char* out;
    ColorFG fg;
    ColorBG bg;
    // Constructor
    Printable(char txt,
              ColorFG fgColor = ColorFG::Default,
              ColorBG bgColor = ColorBG::Default)
        : text(std::move(txt)), fg(fgColor), bg(bgColor) {
            out = new char[2+3+1+3+1+1+4];
            std::snprintf(out, 2+3+1+3+1+1+4, "\033[%d;%dm%c\033[0m",
                  static_cast<int>(fg),
                  static_cast<int>(bg),
                  text);
        }

    Printable() {
        delete[] out;
    };
    // Genera el string coloreado con escape ANSI
    std::string str() const {
        return "\033[" + std::to_string(static_cast<int>(fg)) + ";" +
               std::to_string(static_cast<int>(bg)) + "m" +
               text + "\033[0m";
    }
    
    char* chars() const {
        return out;
    }

    inline void setBG(ColorBG bg){
        this->bg=bg;
        std::snprintf(out, 2+3+1+3+1+1+4, "\033[%d;%dm%c\033[0m",
                  static_cast<int>(this->fg),
                  static_cast<int>(this->bg),
                  this->text);
    }

    inline char* getChars(){
        return nullptr;
    }

    // Sobrecarga de operador de impresión
    friend std::ostream& operator<<(std::ostream& os, const Printable& p) {
        return os << p.str();
    }
};


int main() {
    // // g++ -std=c++23 -I ./src/includes src/SlotMap.cpp src/PrinteableComponent.cpp src/Memory.cpp src/Entity.cpp src/main.cpp -o main
    // 192x36
    
    
    Engine::Memory<Printable,PrintableComponent> mem = Engine::Memory<Printable,PrintableComponent>(60000,10000,10000);

    return 0;

    for (size_t i = 0; i < 192*46; i++){
        mem.createEntity<Printable>(Printable( 176,Printable::ColorFG::White, Printable::ColorBG::BrightBlack));
    }

    
    std::string text = "->";
    for (size_t i = 0; i < 192*46; i++){
        text = "->";
        bool chosen = false;
        std::for_each(mem.begin<Printable>(),mem.end<Printable>(),[&]( auto& n) {  
            if(chosen){
                return;
            }
            if(n.bg!=Printable::ColorBG::BrightGreen){
                n.setBG(Printable::ColorBG::BrightGreen);
                chosen=true;
            }
        
        });
        std::for_each(mem.begin<Printable>(),mem.end<Printable>(),[&]( auto n) {  text+= n.chars() ; });
        std::cout<<"\033[H"<<text<<std::endl;
    }
    
    

    return 0;
    #ifdef _WIN32 // For Windows
        system("cls");
    #else // For Unix-like systems
        system("clear");
    #endif

    

    
} 