#pragma once

class PID {
private:
    double kp;
    double ki;
    double kd;

    double integral;
    double errorAnterior;

public:
    PID(double kp, double ki, double kd)
        : kp(kp), ki(ki), kd(kd),
          integral(0.0), errorAnterior(0.0) {}

    double calcular(double setpoint, double valorActual, double dt) {
        double error = setpoint - valorActual;

        integral += error * dt;

        double derivada = (error - errorAnterior) / dt;

        errorAnterior = error;

        return kp * error
             + ki * integral
             + kd * derivada;
    }

    void reset() {
        integral = 0.0;
        errorAnterior = 0.0;
    }

    void setKp(double valor) {
        kp = valor;
    }

    void setKi(double valor) {
        ki = valor;
    }

    void setKd(double valor) {
        kd = valor;
    }
};