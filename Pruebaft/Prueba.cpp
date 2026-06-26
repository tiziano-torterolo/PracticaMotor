#include <iostream>
#include <thread>
#include <chrono>
#include <csignal>
#include <future>
#include <ctime>
#include <cstdint>
#include <memory>
#include <ft/ft.hpp>
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
    auto txt = ft::TXT{};
    std::cout << "txt = " << txt.getName() << endl;
    auto M1_Encoder = std::shared_ptr<ft::Encoder>(txt.getEncoder(1));
    auto M1_Counter = std::shared_ptr<ft::Counter>(txt.getCounter(1));
    
    auto M2_Encoder = std::shared_ptr<ft::Encoder>(txt.getEncoder(2));
    auto M2_Counter = std::shared_ptr<ft::Counter>(txt.getCounter(2));
    
    auto M3_Encoder = std::shared_ptr<ft::Encoder>(txt.getEncoder(3));
    auto M3_Counter = std::shared_ptr<ft::Counter>(txt.getCounter(3));
    
    auto M4_Encoder = std::shared_ptr<ft::Encoder>(txt.getEncoder(4));
    auto M4_Counter = std::shared_ptr<ft::Counter>(txt.getCounter(4));
    txt.update_config();
    

    Proyecto::Motor<ft::Encoder,ft::Counter> motor1(M1_Encoder, M1_Counter);
    Proyecto::Motor<ft::Encoder,ft::Counter> motor2(M2_Encoder, M2_Counter);
    Proyecto::Motor<ft::Encoder,ft::Counter> motor3(M3_Encoder, M3_Counter);
    Proyecto::Motor<ft::Encoder,ft::Counter> motor4(M4_Encoder, M4_Counter);
    
    std::thread t( [&motor1,&motor2,&motor3,&motor4](){
        auto lastms = now_ms();
        for (int i = 0; i < 150 && !stop; i++) {
            auto now = now_ms();
            double dt = static_cast<double>(now - lastms);
            lastms = now;
            motor1.update(dt, now);
            motor2.update(dt, now);
            motor3.update(dt, now);
            motor4.update(dt, now);
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    });
    t.detach();
    

    motor1.setSpeed(100);
    motor2.setSpeed(-100);
    motor3.setSpeed(-100);
    motor4.setSpeed(100);
    std::this_thread::sleep_for(std::chrono::seconds(14));

    
    motor1.setSpeed(-100);
    motor2.setSpeed(100);
    motor3.setSpeed(100);
    motor4.setSpeed(-100);
    std::this_thread::sleep_for(std::chrono::seconds(14));

    
    motor1.setSpeed(100);
    motor2.setSpeed(-100);
    motor3.setSpeed(-100);
    motor4.setSpeed(100);
    std::this_thread::sleep_for(std::chrono::seconds(14));

    
    // 2. Traversal loop (using auto for cleaner code)
    /*for (auto it = motor.muestrassyn.begin(); it != motor.muestrassyn.end(); ++it) {
        std::cout << it->first << "," << it->second << std::endl; // Dereferencing to read data
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
*/
    motor1.setPower(0);
    motor2.setPower(0);
    motor3.setPower(0);
    motor4.setPower(0);

    std::cout << "Terminando programa" << endl;



    return 0;
}

inline uint64_t now_ms() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000ULL + ts.tv_nsec / 1000000ULL;
}