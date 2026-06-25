#pragma once
#include <iostream>
#include <memory>
#include <concepts>
#include <deque>
#include <utility>
#include <cmath>
#include <algorithm>
#include "PID.hpp"
namespace Proyecto{
template <typename Encoder, typename Counter>
class Motor {
private:
    std::shared_ptr<Encoder> encoder;
    std::shared_ptr<Counter> counter;
    PID pid{69, 0.019, 1.95}; 
    double speed = 0.0;
    double SP_speed = 170;
    std::deque<std::pair<uint64_t, int>> muestras;
//    auto lastUpdateTime = std::chrono::steady_clock::now();
//    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    int lastCounterProbeRead = 0;

public:
    Motor(std::shared_ptr<Encoder> enc = nullptr, std::shared_ptr<Counter> cnt = nullptr) : encoder(enc), counter(cnt){    }

    inline double getSpeed() const noexcept {
        return speed;
    }
    inline int getPower() const noexcept{
        if constexpr (requires { encoder->getSpeed(); }) {
            if (!encoder) return 0;
            return static_cast<int>(encoder->getSpeed());
        }
        return 0;
    }

    inline void setSpeed(double speed) noexcept{
        SP_speed = speed;
    }

    inline void setPower(int power) noexcept{
        if (!encoder) return;
        if constexpr (requires { encoder->startSpeed(power); }) {
            encoder->startSpeed(std::clamp(power, -520, 520));
        }
    }

    inline int getDistance() const noexcept{
        if constexpr (requires { counter->getDistance(); }) {
            if (!counter) return 0;
            return static_cast<int>(counter->getDistance());
        } 
        return -1;    
    }

    void update(double dt ,auto timestamp) noexcept{
        updateSpeedRead(dt, timestamp);
        updateSpeedPID(dt);
    }

    void printMuestras() {
        for (const auto& [t, c] : this->muestras) {
            std::cout << t << " ms - " << c << std::endl;
        }
    }
   

    

private:
    void CounterProbe(auto timestamp) noexcept{
        auto distance = getDistance();
        if (muestras.size() > 4) {
            muestras.pop_front();
        }
        if (distance == -1) {
            muestras.emplace_back(timestamp, 10);
            return;
        }
        muestras.emplace_back(timestamp, distance);
        lastCounterProbeRead = distance;    
        
    }
    void updateSpeedRead(double dt, auto timestamp) noexcept{
        CounterProbe(timestamp);
        calculateSpeed();
        //printMuestras();
    }

    void updateSpeedPID(double dt) noexcept{
        if (muestras.size() < 4) {
            return;
        }
        double power = this->pid.calcular(SP_speed, speed, dt);
        setPower(static_cast<int>(std::round(power)));
        //std::cout << "SP_speed: " << SP_speed << ", speed: " << speed << ", power: " << static_cast<int>(std::round(std::clamp(power, -520.0, 520.0))) << std::endl;

    }

    void calculateSpeed() noexcept{
        auto sum = 0.0;
        auto cantMSE = 0;
        auto cant = 0;
        auto it = muestras.begin();
        auto next = std::next(it);
        
        for (; next != muestras.end(); ++it, ++next) {

            auto duration1 = next->first - it->first;
            // t1,c1 = actual
            // t2,c2 = siguiente
            
            if (duration1 > 0) {
                cant++;
                sum += static_cast<double>(cant*(next->second) / (duration1 / 1000.0));
                cantMSE+=cant;
            }
                
            
        }
        speed = sum / cantMSE;
    }



    
};




}
