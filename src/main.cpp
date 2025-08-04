// Your First C++ Program
#include "./includes/PrinteableComponent.hpp"
#include "./SlotMap.cpp"
#include "./Memory.cpp"
#include <iostream>
#include <algorithm>
#include <array>
#include <chrono>
#include <thread>
#include <cstdlib> 
#include <memory>
#include <print>

int main() {
    // // g++ -o programa src/main.cpp src/Memory.cpp src/PrinteableComponent.cpp
    // Engine::Memory<PrinteableComponent> mem = Engine::Memory<PrinteableComponent>(60000000);
    


    // for (size_t i = 0; i < 500; i++){
    //     mem.emplace<PrinteableComponent>('a');
    // }
    

    // using namespace std::chrono_literals;
    // std::this_thread::sleep_for(1230ms);



    //std::for_each(mem.begin<PrinteableComponent>(),mem.end<PrinteableComponent>(),[]( auto& n) {  n.setText('b') ; });
    //std::for_each(mem.begin<PrinteableComponent>(),mem.end<PrinteableComponent>(),[]( auto& n) {  std::cout << n ; });
    
    Engine::SlotMap<PrinteableComponent> slotmap = Engine::SlotMap<PrinteableComponent>(10);
    PrinteableComponent*** a = new PrinteableComponent**[10];
    for (size_t i = 0; i < 10; i++)    {
        a[i] = slotmap.create('a'+i);
    }
    for (size_t i = 0; i < 10; i++)    {
        std::cout << (*(*a[i])) <<std::endl;
    }
    slotmap.removeByIndex(4);
    slotmap.create('z');
    for (size_t i = 0; i < 10; i++)    {
        std::cout << (*(*a[i])) <<std::endl;
    }
    delete[] a;
    return 0;
}