#include <iostream>
#include <thread>
#include <chrono>
#include <csignal>
#include <future>
#include <memory>
#include "Motor.hpp"
#include "Defines.cpp"
#include "MultipleMotorController.cpp"


using namespace std;

int main() {
    ConnectExitSignalHandler;
    std::cout << "Comenzando programa" << endl;
    TxtType txt = createTXT();

    #if (EXIST_VEHICLE) 
        std::cout << "txt = " << txt.getName() << endl;
    #else 
        std::cout << "txt is nullptr" << endl;
    #endif

    auto M1_Encoder = createEncoder_shared_ptr(txt, 1);
    auto M1_Counter = createCounter_shared_ptr(txt, 1);
    
    auto M2_Encoder = createEncoder_shared_ptr(txt, 2);
    auto M2_Counter = createCounter_shared_ptr(txt, 2);

    updateTXT_config(txt);
    
    auto motor1 = std::make_shared<Proyecto::Motor<EncoderType, CounterType>>(
        M1_Encoder,
        M1_Counter
    );

    auto motor2 = std::make_shared<Proyecto::Motor<EncoderType, CounterType>>(
        M2_Encoder,
        M2_Counter
    );

    MultipleMotorController<EncoderType, CounterType> controller(
        motor1,
        motor2,
        nullptr,
        nullptr
    );

    std::thread t( [&controller](){
        auto lastms = now_ms();
        for (int i = 0; i < 40*1000 && !stop; i++) {
            auto now = now_ms();
            double dt = static_cast<double>(now - lastms);
            lastms = now;
            controller.update(dt, now);
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    });
    t.detach();
    
    controller.initMovement(40, 100, 0, 0, now_ms());
    std::this_thread::sleep_for(std::chrono::seconds(4));
    
    controller.initMovement(70, 70, 0, 0, now_ms());
    std::this_thread::sleep_for(std::chrono::seconds(4));
    
    controller.initMovement(20, 20, 0, 0, now_ms());
    std::this_thread::sleep_for(std::chrono::seconds(4));
    
    
    controller.initMovement(-100, -100, 0, 0, now_ms());
    std::this_thread::sleep_for(std::chrono::seconds(5));
    
    
    controller.initMovement(-150, -150, 0, 0, now_ms());
    std::this_thread::sleep_for(std::chrono::seconds(5));
    
    // 2. Traversal loop (using auto for cleaner code)
    /*for (auto it = motor.muestrassyn.begin(); it != motor.muestrassyn.end(); ++it) {
        std::cout << it->first << "," << it->second << std::endl; // Dereferencing to read data
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
     scp Motor.hpp Prueba.cpp PID.hpp MultipleMotorController.cpp Defines.cpp ft@192.168.1.18:workspaces/testFolder/ ; ssh ft@192.168.1.18 ; powershell.exe -c "[console]::beep(1000,500)"
     cd workspaces/testFolder ; ls ; echo "\n comenzando compilacion \n";  g++ -std=c++17 Prueba.cpp -o prueba -lTxtControlLib -pthread -fconcepts ; rm Motor.hpp Prueba.cpp PID.hpp MultipleMotorController.cpp Defines.cpp ; ls 
*/
    stop = true;
    motor1->setPower(0);
    motor2->setPower(0);

    std::cout << "Terminando programa" << endl;
    //comprueba que t siga vivo y la mata
    


    return 0;
}

