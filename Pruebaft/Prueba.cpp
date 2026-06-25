#include <iostream>
#include <thread>
#include <chrono>
#include <csignal>
#include <future>
#include <ctime>
#include <cstdint>
//#include <ft/ft.hpp>
#include "Motor.hpp"

using namespace std;
auto stop = false;
void signal_handler(int signal)
{
    stop = true;
}
inline uint64_t now_ms();
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
    std::thread t( [&motor](){
        auto lastms = now_ms();
        for (int i = 0; i < 115 && !stop; i++) {
            auto now = now_ms();
            double dt = static_cast<double>(now - lastms);
            lastms = now;
            (void)std::async(std::launch::async, [&motor, dt,now]() { motor.update(dt, now); });
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    });
    t.detach();
    while (!stop) {
        auto sp = 0.0;
        std::cin >> sp;
        motor.setSpeed(sp);
    }

    
    std::cout << "prom =" << motor.getSpeed() << std::endl;
    std::cout << "Terminando programa" << endl;



    return 0;
}

inline uint64_t now_ms() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000ULL + ts.tv_nsec / 1000000ULL;
}