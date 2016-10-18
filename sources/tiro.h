#ifndef TIRO_H
#define TIRO_H

#include "funcoes.h"
#include "circulo.h"

const float DEFAULT_SHOOT_LENGHT = 5;
const float SHOOT_COLOR[3] = {0.32, 0.32, 0.32};

class Tiro : public Circulo
{

private:
    float shootSpeed;
    float shootDirection[3];
    float shootRotation;

public:

    Tiro();

    Tiro(const Tiro& s);

    float getShootSpeed() const;

    void setShootSpeed(float shootSpeed);

    const float *getShootDirection() const;

    void setShootDirection(AXES axis, float direction);

    float getShootRotation() const;

    void setShootRotation(float shootRotation);

    void draw();

    void move(double time);

    ~Tiro();

};

#endif //TIRO_H
