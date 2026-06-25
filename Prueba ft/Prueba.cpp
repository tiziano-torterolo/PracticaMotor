#include <iostream>
#include <thread>
#include <chrono>
#include <csignal>
//#include <ft/ft.hpp>
#include "Motor.hpp"

using namespace std;
auto stop = false;
void signal_handler(int signal)
{
    stop = true;
}

int main() {
    std::signal(SIGINT, signal_handler);
    std::cout << "Comenzando programa" << endl;
    /*auto txt = ft::TXT{};
    std::cout << "txt = " << txt.getName() << endl;
    auto* M1_Encoder = txt.getEncoder(1);
    auto* M1_Counter = txt.getCounter(1);
    txt.update_config();


    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    std::cout << "Iniciando Motores" << endl;

    M1_Encoder->stop(0xFF);
    M1_Encoder->startSpeed(200);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    M1_Encoder->startSpeed(500);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    

    M1_Encoder->startSpeed(-500);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));


    M1_Encoder->stop(0xFF);
    std::cout << "Finalizando programa" << endl;

    delete M1_Encoder;
    delete M1_Counter;
*/
    Proyecto::Motor<int,int> motor(nullptr, nullptr);
    for (int i = 0; i < 15; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        motor.update(0.1);
    }
    
    std::cout << "prom =" << motor.getSpeed() << std::endl;
    std::cout << "Terminando programa" << endl;



    return 0;
}