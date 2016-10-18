#include "tiro.h"

Tiro::Tiro()
{
    shootSpeed = shootRotation = 0;
    shootDirection[X_AXIS] = shootDirection[Y_AXIS] = shootDirection[Z_AXIS] = 0;
    this->setRadius(DEFAULT_SHOOT_LENGHT);
}

Tiro::Tiro(const Tiro &s) : Circulo(s)
{
    this->shootSpeed = s.shootSpeed;
    this->shootDirection[X_AXIS] = s.shootDirection[X_AXIS];
    this->shootDirection[Y_AXIS] = s.shootDirection[Y_AXIS];
    this->shootRotation = s.shootRotation;
}

float Tiro::getShootSpeed() const
{
    return shootSpeed;
}

void Tiro::setShootSpeed(float shootSpeed)
{
    Tiro::shootSpeed = shootSpeed;
}

const float *Tiro::getShootDirection() const
{
    return shootDirection;
}

void Tiro::setShootDirection(AXES axis, float direction)
{
    this->shootDirection[axis] = direction;
}

float Tiro::getShootRotation() const
{
    return shootRotation;
}

void Tiro::setShootRotation(float shootRotation)
{
    Tiro::shootRotation = shootRotation;
}

void Tiro::draw()
{
    drawCircle(getXc(), getYc(), getRadius(), SHOOT_COLOR);
}

void Tiro::move(double time)
{
    shootDirection[X_AXIS] = (this->getShootSpeed() * time * cos(this->getShootRotation() * M_PI / 180.0));
    shootDirection[Y_AXIS] = (this->getShootSpeed() * time * sin(this->getShootRotation() * M_PI / 180.0));

}

Tiro::~Tiro()
{}