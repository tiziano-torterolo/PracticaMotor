// Your First C++ Program
#include "./PrinteableComponent.hpp"
#include "./BackgroundComponent.hpp"
#include "./ASCIIPixelComponent.hpp"
#include "./SpriteAnimationComponent.hpp"
#include "./Map1.hpp"
#include "./GraphicSystem.hpp"
#include "./SlotMap.cpp"
#include "./BackgroundComponent.cpp"
#include "./SpriteComponent.cpp"
#include "./SpriteAnimationComponent.cpp"
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
#include <fstream>
#include <iostream>
#include <string>
class Point {
    std::size_t x, y;
public:
    Point(std::size_t x_, std::size_t y_) : x(x_), y(y_) {}
    Point() : x(0), y(0) {}
    std::size_t getX() const { return x; }
    std::size_t getY() const { return y; }
};

int main() {
    // // g++ -std=c++23 -I ./src/includes src/SlotMap.cpp src/PrintableComponent.cpp src/Memory.cpp src/Entity.cpp src/main.cpp src/BackgroundComponent.cpp src/ASCIIPixelComponent.cpp src/SpriteAnimationComponent.cpp src/SpriteComponent.cpp -o main
    // 192x36
    

    auto mem = 
    Engine::Memory<
    Point,
    Engine::SpriteComponent<3,3,Point>,
    Engine::BackgroundComponent<100,30>,
    Engine::ASCIIPixelComponent
    >(4000);

    std::array<Engine::ASCIIPixelComponent,3000> tmp;
    Map1 map;
    for (size_t i = 0; i < 3000; i++)
    {
        tmp[i]=  Engine::ASCIIPixelComponent(map.chars[i],static_cast<Engine::ASCIIPixelComponent::ColorBG>(map.BGcolors[i]),static_cast<Engine::ASCIIPixelComponent::ColorFG>(map.FGcolors[i]));
    }
    auto sprite = mem.emplace<Engine::SpriteComponent<3,3,Point>>(Engine::SpriteComponent<3,3,Point>(
        &mem,
        {'X','X','X','X','X','X','X','X','X'},
        {Engine::ASCIIPixelComponent::ColorBG::Red,Engine::ASCIIPixelComponent::ColorBG::Red,Engine::ASCIIPixelComponent::ColorBG::Red,
         Engine::ASCIIPixelComponent::ColorBG::Red,Engine::ASCIIPixelComponent::ColorBG::White,Engine::ASCIIPixelComponent::ColorBG::Red,
         Engine::ASCIIPixelComponent::ColorBG::Red,Engine::ASCIIPixelComponent::ColorBG::Red,Engine::ASCIIPixelComponent::ColorBG::Red},
        {Engine::ASCIIPixelComponent::ColorFG::White,Engine::ASCIIPixelComponent::ColorFG::White,Engine::ASCIIPixelComponent::ColorFG::White,
         Engine::ASCIIPixelComponent::ColorFG::White,Engine::ASCIIPixelComponent::ColorFG::Black,Engine::ASCIIPixelComponent::ColorFG::White,
         Engine::ASCIIPixelComponent::ColorFG::White,Engine::ASCIIPixelComponent::ColorFG::White,Engine::ASCIIPixelComponent::ColorFG::White},
        10,5
    ));
    auto bg = mem.emplace<Engine::BackgroundComponent<100,30>>(Engine::BackgroundComponent<100,30>(
        &mem,
        std::move(tmp)
    ));

    std::string text = "->"; int i=0;
    std::for_each((*bg)->begin(),(*bg)->end(),[&]( auto n) {
            text+=(*n)->str(); 
            i++;
            if(i==100){
                std::cout<<text<<std::endl;
                text = "->";
                i=0;
            }
        });
    std::for_each((*sprite)->begin(),(*sprite)->end(),[&]( auto n) {
            text+=(*n)->str(); 
            i++;
            if(i==3){
                std::cout<<text<<std::endl;
                text = "->";
                i=0;
            }
        });




        
    return 0;    
    std::cout << "\033[2J";        // Limpia la pantalla
    std::cout << "\033[20;100H";   // Mueve el cursor a (fila 20, columna 100)
    std::cout << "Hola desde (20,100)" << std::endl;



    std::cout<<"\033[H"<<std::endl;
    #ifdef _WIN32 // For Windows
        system("cls");
    #else // For Unix-like systems
        system("clear");
    #endif

    

    
} 