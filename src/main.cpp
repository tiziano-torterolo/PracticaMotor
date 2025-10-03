// Your First C++ Program
#include "./PrinteableComponent.hpp"
#include "./BackgroundComponent.hpp"
#include "./ASCIIPixelComponent.hpp"
#include "./Map1.hpp"
#include "./GraphicSystem.hpp"
#include "./SlotMap.cpp"
#include "./BackgroundComponent.cpp"
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
int main() {
    // // g++ -std=c++23 -I ./src/includes src/SlotMap.cpp src/PrintableComponent.cpp src/Memory.cpp src/Entity.cpp src/main.cpp src/BackgroundComponent.cpp src/ASCIIPixelComponent.cpp -o main
    // 192x36
    

    Engine::Memory<Engine::BackgroundComponent<100,30>,Engine::ASCIIPixelComponent> mem = Engine::Memory<Engine::BackgroundComponent<100,30>,Engine::ASCIIPixelComponent>(600,600,4000);
    std::array<Engine::ASCIIPixelComponent,3000> tmp;
    Map1 map;
    for (size_t i = 0; i < 3000; i++)
    {
        tmp[i]=  Engine::ASCIIPixelComponent(map.chars[i],static_cast<Engine::ASCIIPixelComponent::ColorBG>(map.BGcolors[i]),static_cast<Engine::ASCIIPixelComponent::ColorFG>(map.FGcolors[i]));
    }
    
    mem.emplace<Engine::BackgroundComponent<100,30>>(Engine::BackgroundComponent<100,30>(
        &mem,
        std::move(tmp)
    ));
    std::string text = "->"; int i=0;
    std::for_each(mem.begin<Engine::ASCIIPixelComponent>(),mem.end<Engine::ASCIIPixelComponent>(),[&]( auto n) {
            text+=n.str(); 
            i++;
            if(i==100){
                
                std::cout<<text<<std::endl;
                text = "->";
                i=0;
            }
        });

  



    return 0;  
    std::cout<<"\033[H"<<std::endl;
    #ifdef _WIN32 // For Windows
        system("cls");
    #else // For Unix-like systems
        system("clear");
    #endif

    

    
} 