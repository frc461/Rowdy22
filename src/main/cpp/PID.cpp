#include "PID.h"

PID::PID(double p, double i, double d, std::string name) {
    this->p = p;
    this->i = i;
    this->d = d;
    this->name = name;

    error = errorSum = errorPrev = 0;
}

double PID::Get(double val, double ideal) {
    error = ideal - val;
    errorSum += error;
    double errorRate = error - errorPrev;

    errorPrev = error;

    return (p*error + i*errorSum + d*errorRate);
}

void PID::Reset() { errorSum = 0; }

void PID::SetP(double p) { this->p = p; }
void PID::SetI(double i) { this->i = i; }
void PID::SetD(double d) { this->d = d; }