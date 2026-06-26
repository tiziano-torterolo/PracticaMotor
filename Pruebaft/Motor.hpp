#pragma once
#include <iostream>
#include <memory>
#include <deque>
#include <utility>
#include <vector>
#include <cmath>
#include <algorithm>
#include "PID.hpp"
#include "Defines.cpp"

namespace Proyecto{
template <typename Encoder, typename Counter>
class Motor {
private:
    std::shared_ptr<Encoder> encoder;
    std::shared_ptr<Counter> counter;
    PID pid{3.4, 0.00236, 21.25}; 
    double speed = 0.0;
    double SP_speed = 170;
    std::deque<std::pair<uint64_t, int>> muestras;
//    auto lastUpdateTime = std::chrono::steady_clock::now();
//    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    int lastCounterProbeRead = 0;
    bool positiveDirection = false;
    int lastDistance = 0;
    int startDistance = 0;
    long long motorSteps = 0;

public:
    //std::vector<std::pair<uint64_t, double>> muestrassyn;
    Motor(std::shared_ptr<Encoder> enc = nullptr, std::shared_ptr<Counter> cnt = nullptr) : encoder(enc), counter(cnt){   
        //muestrassyn.reserve(5000);
        startDistance = getDistance();
    }

    inline double getSpeed() const noexcept {
        return speed;
    }

    inline int getPower() const noexcept{
        if constexpr (EXIST_VEHICLE) {
            if (!encoder) return 0;
            return static_cast<int>(encoder->getSpeed());
        }
        return 0;
    }

    inline void setSpeed(double speed) noexcept{
        SP_speed = speed;
        this->positiveDirection = (speed>=0.0);
    }

    inline void setPower(int power) noexcept{
        if constexpr (EXIST_VEHICLE) {
        if (!encoder) return;
            encoder->startSpeed(std::clamp(power, -512, 512));
        }
    }

    inline long long getDistance() noexcept{
        if constexpr (EXIST_VEHICLE) {
            if (!counter) return 0;
            auto temp = static_cast<int>(counter->getDistance());
            if (lastDistance > 0 && temp < 0) {
                motorSteps += lastDistance-startDistance;
                startDistance = temp;
                lastDistance = temp;
            }
            return motorSteps + (temp-startDistance);
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
        if constexpr (!EXIST_VEHICLE) {
            muestras.emplace_back(timestamp, 10);
            return;
        } else {
            muestras.emplace_back(timestamp, distance==0 ? 0 : distance-lastCounterProbeRead);
            lastCounterProbeRead = distance;  
        }
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
        //std::cout << speed << std::endl;

    }

    void calculateSpeed() noexcept{
        auto sum = 0.0;
        auto cantMSE = 0;
        auto cant = 0;
        auto it = muestras.begin();
        auto next = std::next(it);
        
        for (; next != muestras.end(); ++it, ++next) {

            auto duration1 = next->first - it->first;

            if (duration1 > 0) {
                cant++;
                sum += static_cast<double>(cant*(next->second) / (duration1 / 1000.0));
                cantMSE+=cant;
            }
        }
        speed = this->positiveDirection ? sum / cantMSE : - (sum / cantMSE);
        //muestrassyn.push_back({muestras.begin()->first,speed});

    }



    
};




}
