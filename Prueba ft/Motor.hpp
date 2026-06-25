#pragma once
#include <iostream>
#include <memory>
#include <concepts>
#include <deque>
#include <utility>
#include "PID.hpp"
namespace Proyecto{
template <typename Encoder, typename Counter>
class Motor {
private:
    std::shared_ptr<Encoder> encoder;
    std::shared_ptr<Counter> counter;
    PID pid{0.1, 0.01, 0.05}; 
    double speed = 0.0;
    double SP_speed = 0.0;
    std::deque<std::pair<std::chrono::system_clock::time_point, int>> muestras;
//    auto lastUpdateTime = std::chrono::steady_clock::now();
//    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    int lastCounterProbeRead = 0;

public:
    Motor(std::shared_ptr<Encoder> enc = nullptr, std::shared_ptr<Counter> cnt = nullptr) : encoder(enc), counter(cnt){    }

    double getSpeed() {
        return speed;
    }
    int getPower() {
        if constexpr (requires { encoder->getSpeed(); }) {
            if (!encoder) return 0;
            return static_cast<int>(encoder->getSpeed());
        }
        return 0;
    }

    void setSpeed(double speed) {
        SP_speed = speed;
    }

    void setPower(std::size_t power) {
        if (!encoder) return;
        if constexpr (requires { encoder->startSpeed(power); }) {
            encoder->startSpeed(power);
        }
    }

    void update(double dt) {
        auto timestamp = std::chrono::system_clock::now();
        updateSpeedRead(dt, timestamp);
        updateSpeedPID(dt);
    }


    int getDistance() {
        if constexpr (requires { counter->getDistance(); }) {
            if (!counter) return 0;
            return static_cast<int>(counter->getDistance());
        } 
        return -1;    
    }

    

private:
    void CounterProbe(auto timestamp){
        auto distance = getDistance();
        if (distance == -1) {
            muestras.emplace_back(timestamp, 1);
        }
        if (distance-lastCounterProbeRead != 0) {
            muestras.emplace_back(timestamp, distance);
            lastCounterProbeRead = distance;    
        }
        if (muestras.size() > 10) {
            muestras.pop_front();
        }
    }
    void updateSpeedRead(double dt, auto timestamp) {
        CounterProbe(timestamp);
        calculateSpeed();
    }

    void updateSpeedPID(double dt) {}

    void calculateSpeed() {
        auto sum = 0.0;
        auto cantMSE = 0;
        auto cant = 0;
        auto it = muestras.begin();
        auto next = std::next(it);
        /
        for (; it != muestras.end(); ++it, ++next) {

            auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(next->first - it->first).count();
            // t1,c1 = actual
            // t2,c2 = siguiente
            auto speed1 = 0.0;
            auto speed2 = 0.0;
            
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
