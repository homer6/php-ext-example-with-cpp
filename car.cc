#include "car.h"

Car::Car(int maxGear) {
    this->maxGear = maxGear;
    this->currentGear = 1;
    this->speed = 0;
}

void Car::shift(int gear) {
    if (gear < 1 || gear > maxGear) {
        return;
    }
    currentGear = gear;
}

void Car::accelerate() {
    speed += (5 * this->getCurrentGear());
}

void Car::brake() {
    speed -= (5 * this->getCurrentGear());
}

int Car::getCurrentSpeed() {
    return speed;
}

int Car::getCurrentGear() {
    return currentGear;
}

