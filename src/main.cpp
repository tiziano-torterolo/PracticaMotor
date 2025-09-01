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
    ColorFG fg;
    ColorBG bg;
    // Constructor
    Printable(char txt,
              ColorFG fgColor = ColorFG::Default,
              ColorBG bgColor = ColorBG::Default)
        : text(std::move(txt)), fg(fgColor), bg(bgColor) {}

    Printable() = default;
    // Genera el string coloreado con escape ANSI
    std::string str() const {
        return "\033[" + std::to_string(static_cast<int>(fg)) + ";" +
               std::to_string(static_cast<int>(bg)) + "m" +
               text + "\033[0m";
    }

    // Sobrecarga de operador de impresión
    friend std::ostream& operator<<(std::ostream& os, const Printable& p) {
        return os << p.str();
    }
};


int main() {
    // // g++ -std=c++23 -I ./src/includes src/SlotMap.cpp src/PrinteableComponent.cpp src/Memory.cpp src/Entity.cpp src/main.cpp -o main
    // 192x36
    


    // for (size_t i = 0; i < 500; i++){
    //     mem.emplace<PrinteableComponent>('a');
    // }
    

    // using namespace std::chrono_literals;
    // std::this_thread::sleep_for(1230ms);



    //std::for_each(mem.begin<PrinteableComponent>(),mem.end<PrinteableComponent>(),[]( auto& n) {  n.setText('b') ; });
    //std::for_each(mem.begin<PrinteableComponent>(),mem.end<PrinteableComponent>(),[]( auto& n) {  std::cout << n ; });
    // Engine::Memory<PrinteableComponent> mem = Engine::Memory<PrinteableComponent>(60000000);

    // //for (size_t i = 0; i < 50; i++){
    // //    mem.createEntity<Printable>("Error!",
    // //                Printable::ColorFG::BrightWhite,
    // //                Printable::ColorBG::Red);
    // //}
    // 
    // Engine::SlotMap<PrinteableComponent> mem = Engine::SlotMap<PrinteableComponent>(600);

    // Engine::Memory<Printable,PrinteableComponent> mem = Engine::Memory<Printable,PrinteableComponent>(6000);
    // for (size_t i = 0; i < 4000; i++){
    //     mem.createEntity<Printable>(Printable( "He",Printable::ColorFG::White, Printable::ColorBG::BrightCyan));
    // }************
    //     mem.createEntity<Printable>(Printable( "Hello world!",Printable::ColorFG::White, Printable::ColorBG::Black));

    for (size_t k = 1; k < 6; k++)    {
        int ancho = (16 * k*3) -4;
        int alto = 9 * k ;
        std::cout <<std::endl<<std::endl<< ancho <<"x"<<alto <<std::endl;
        for (int i = 0; i < alto ; i++) {
            for (int j = 0; j < ancho; j++) {
                std::cout << "*";
            }
            std::cout << "\n";
        }   /* code */
    }
    
    
    Engine::Memory<Printable,PrintableComponent> mem = Engine::Memory<Printable,PrintableComponent>(60000);

    

    for (size_t i = 0; i < 192*46; i++){
        mem.createEntity<Printable>(Printable( 176,Printable::ColorFG::White, Printable::ColorBG::Cyan));
    }
    
    std::string text = "->";
    for (size_t i = 0; i < 300; i++)
    {
        for (size_t i = 0; i < 1; i++){
            text = "->";
            bool setswitch = false;
            std::for_each(mem.begin<Printable>(),mem.end<Printable>(),[&]( auto& n) {  
                if(setswitch){
                    return;
                }
                if(n.bg != Printable::ColorBG::BrightMagenta){
                    n.bg = Printable::ColorBG::BrightMagenta;
                    setswitch = true;
                    return;
                } ; });
            std::for_each(mem.begin<Printable>(),mem.end<Printable>(),[&]( auto n) {  text+= n.str() ; });

            #ifdef _WIN32 // For Windows
                system("cls");
            #else // For Unix-like systems
                system("clear");
            #endif
            
            std::cout << text <<std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }/* code */
    }
    
    

    

    return 0;
} 