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



int main() {
    // // g++ -std=c++20 -I ./src/includes src/SlotMap.cpp src/PrinteableComponent.cpp src/Memory.cpp src/main.cpp -o main
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

    slotmap.removeByIndex(7);
    slotmap.removeByIndex(3);
    slotmap.forEach([]( auto& n) {  std::cout << n ; });
    slotmap.removeIf([&slotmap]( auto n) {  slotmap.forEach([]( auto& n) {  std::cout << n ; });std::cout << std::endl ; return true ; });
    delete[] a;
    return 0;
    //abcdefghij
    //aicdjfgh
}