// Your First C++ Program
#include "./PrinteableComponent.hpp"
#include "./BackgroundComponent.hpp"
#include "./ASCIIPixelComponent.hpp"
#include "./SpriteAnimationComponent.hpp"
#include "./Map1.hpp"
#include "./GraphicSystem.hpp"
#include "./Component.hpp"
#include "./Component.cpp"
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
    // // g++ -std=c++23 -I ./src/includes src/SlotMap.cpp src/PrintableComponent.cpp src/Memory.cpp src/Entity.cpp src/main.cpp src/BackgroundComponent.cpp src/ASCIIPixelComponent.cpp src/SpriteAnimationComponent.cpp src/SpriteComponent.cpp src/Component.cpp -o main
    // 192x36
    // VM 1234 
    

    auto mem = 
    Engine::Memory<
    Point,
    Engine::SpriteComponent<3,3,Point>,
    Engine::BackgroundComponent<100,30>,
    Engine::BackgroundComponent<192,36>,
    Engine::ASCIIPixelComponent
    >(10,10,10,10,10,192*36*4);


    for (size_t i = 0; i < 30; i++)
    {
        std::cout << " -> " << i << std::endl;

        std::array<Engine::ASCIIPixelComponent,3000> tmp;
        Map1 map;
        for (size_t i = 0; i < 3000; i++)
        {
            tmp[i]=  Engine::ASCIIPixelComponent(map.chars[i],static_cast<Engine::ASCIIPixelComponent::ColorBG>(map.BGcolors[i]),static_cast<Engine::ASCIIPixelComponent::ColorFG>(map.FGcolors[i]));
        }
        std::array<Engine::ASCIIPixelComponent,192*36> tmp2;
        Map2 map2;
        for (size_t i = 0; i < 192*36; i++)
        {
            tmp2[i]=  Engine::ASCIIPixelComponent(map2.chars[i],static_cast<Engine::ASCIIPixelComponent::ColorBG>(map2.BGcolors[i]),static_cast<Engine::ASCIIPixelComponent::ColorFG>(map2.FGcolors[i]));
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
        auto bg2 = mem.emplace<Engine::BackgroundComponent<192,36>>(Engine::BackgroundComponent<192,36>(
            &mem,
            std::move(tmp2)
        ));

        mem.remove(sprite);
        mem.remove(bg);
        mem.remove(bg2);
        
    }
    


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