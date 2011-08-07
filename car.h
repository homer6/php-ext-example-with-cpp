#ifndef VEHICLES_CAR_H
#define VEHICLES_CAR_H

// A very simple car class
class Car {
public:
    Car(int maxGear);
    void shift(int gear);
    void accelerate();
    void brake();
    int getCurrentSpeed();
    int getCurrentGear();
private:
    int maxGear;
    int currentGear;
    int speed;
};

#endif /* VEHICLES_CAR_H */

