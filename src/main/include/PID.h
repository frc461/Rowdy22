#pragma once

#include <string>

class PID {
public:
    PID(double p, double i, double d, std::string name);
    ~PID();

    double Get(double val, double ideal);

    void SetP(double p);
    void SetI(double i);
    void SetD(double d);
    
    void Reset();

private:
    double p, i, d;

    double error, errorSum, errorPrev;

    std::string name;
};