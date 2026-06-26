#pragma once
#include <array>
#include <math.h>
#include "Motor.hpp"
#include "Defines.cpp"
#include <memory>

template <typename Encoder, typename Counter>
class MultipleMotorController {
private:
    std::array<std::shared_ptr<Proyecto::Motor<Encoder, Counter>>, 4> motors;
    std::array<long long, 4> initialDistances;
    std::array<long long, 4> actualDistances;
    std::array<long long, 4> predictedDistances;
    std::array<double, 4> actualSpeeds;
    std::array<double, 4> speedModifers;
    long long timestampMovementInit = 0;
    const double percentageErrorMax = 0.05; // 5% error allowed
    const double speedBoost = 0.25; // 25% speed boost allowed

public:
    
    MultipleMotorController(std::shared_ptr<Proyecto::Motor<Encoder, Counter>> m1,
        std::shared_ptr<Proyecto::Motor<Encoder, Counter>> m2,
        std::shared_ptr<Proyecto::Motor<Encoder, Counter>> m3,
        std::shared_ptr<Proyecto::Motor<Encoder, Counter>> m4)
    : motors{m1, m2, m3, m4} {
        updateinitDistances();
    }

    void initMovement(double speed_m1,double speed_m2,double speed_m3,double speed_m4, auto timestamp) noexcept {
        updateinitDistances();
        timestampMovementInit = timestamp;
        if (motors[0]) {
            motors[0]->setSpeed(speed_m1);
            actualSpeeds[0] = speed_m1;
        }
        if (motors[1]) {
            motors[1]->setSpeed(speed_m2);
            actualSpeeds[1] = speed_m2;
        }
        if (motors[2]) {
            motors[2]->setSpeed(speed_m3);
            actualSpeeds[2] = speed_m3;
        }
        if (motors[3]) {
            motors[3]->setSpeed(speed_m4);
            actualSpeeds[3] = speed_m4;
        }

    }

    void update(double dt, auto timestamp) noexcept {
        updateActualDistances();
        calculatePredictedDistances(dt, timestamp);
        calculateSpeedModifiers();
        sendUpdateToMotors();

        for (auto& motor : motors) {
            if (motor) {
                motor->update(dt, timestamp);
            }
        }
    }

    
private:
    inline void updateinitDistances() noexcept {
        for (size_t i = 0; i < motors.size(); ++i) {
            if (motors[i]) {
                initialDistances[i] = motors[i]->getDistance();
            }
        }
    }
    inline void updateActualDistances() noexcept {
        for (size_t i = 0; i < motors.size(); ++i) {
            if (motors[i]) {
                actualDistances[i] = motors[i]->getDistance();
            }
        }
    }
    inline void sendUpdateToMotors() noexcept {
        for (size_t i = 0; i < motors.size(); ++i) {
            if (motors[i]) {
                motors[i]->setSpeed(actualSpeeds[i] * speedModifers[i]);
            }
        }
    }
    
    inline void calculatePredictedDistances(double dt, auto timestamp) noexcept {
        const double elapsedSeconds = (timestamp - timestampMovementInit) / 1000.0;

        for (std::size_t i = 0; i < predictedDistances.size(); ++i) {
            predictedDistances[i] = static_cast<long long>(initialDistances[i] + abs(actualSpeeds[i] * elapsedSeconds));
        }
    }


    inline void calculateSpeedModifiers() noexcept {
        for (std::size_t i = 0; i < speedModifers.size(); ++i) {

            speedModifers[i] = 1.0;

            if (predictedDistances[i] == 0) {
                continue;
            }
            
            const double error =
                static_cast<double>(
                    predictedDistances[i] - actualDistances[i]
                ) / predictedDistances[i];

            if (error > percentageErrorMax) {
                speedModifers[i] += speedBoost;
            }
            else if (error < -percentageErrorMax) {
                speedModifers[i] -= speedBoost;
            }
        }
    }
};