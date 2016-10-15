#include "carro.h"
#include "funcoes.h"

Carro::Carro()
{
    this->moving = false;
    this->speedCar = this->speedShoot = 0;
    this->carRotation = this->gunRotation = this->wheelRotation = 0;
    this->setCarDirection(X_AXIS, 0);
    this->setCarDirection(Y_AXIS, 1);
    this->setCarDirection(Z_AXIS, 0);
}

void Carro::copyInfo(Circulo& circle)
{
    this->setXc(circle.getXc());
    this->setYc(circle.getYc());
    this->setRadius(circle.getRadius());
    this->setId(circle.getId());
    this->setRGBColors(circle.getRGBColors());
}

bool Carro::isMoving() const
{
    return moving;
}

void Carro::setMoving(bool moving)
{
    this->moving = moving;
}

float Carro::getSpeedCar() const
{
    return speedCar;
}

void Carro::setSpeedCar(float speedCar)
{
    this->speedCar = speedCar;
}

float Carro::getSpeedShoot() const
{
    return speedShoot;
}

void Carro::setSpeedShoot(float speedShoot)
{
    this->speedShoot = speedShoot;
}

const float *Carro::getCarDirection() const
{
    return carDirection;
}

void Carro::setCarDirection(AXES axis, float direction)
{
    this->carDirection[axis] = direction;
}

const float *Carro::getGunDirection() const
{
    return gunDirection;
}

void Carro::setGunDirection(AXES axis, float direction)
{
    this->carDirection[axis] = direction;
}

const float *Carro::getWheelDirection() const
{
    return wheelDirection;
}

void Carro::setWheelDirection(AXES axis, float direction)
{
    this->wheelDirection[axis] = direction;
}

float Carro::getCarRotation() const
{
    return carRotation;
}

void Carro::setCarRotation(float rotation)
{
    this->carRotation = rotation;
}

float Carro::getGunRotation() const
{
    return gunRotation;
}

void Carro::setGunRotation(float rotation)
{
    this->gunRotation = rotation;
}

float Carro::getWheelRotation() const
{
    return wheelRotation;
}

void Carro::setWheelRotation(float rotation)
{
    this->wheelRotation = rotation;
}

void Carro::draw()
{
    //Car parameters
    float carWidth = 140;
    float carHeight = 300;
    float ellipseBigAxis = 80;
    float ellipseSmallAxis = 40;
    float gunWidth = 20;
    float gunHeight = 90;
    float wheelShaftLength = 30;
    float wheelShaftWidth = 70;
    float wheelLength = 125;
    float wheelWidth = 65;
    float wheelAxisDistance = 45;
    float CORRECTION_FACTOR = 5;
    //float color colocar cores aki
    float scale_factor = (this->getRadius()*2) / (carWidth + 2*wheelShaftWidth + 2*wheelLength);

    glPushMatrix();
        //car body
        glTranslatef(this->getXc(), this->getYc(), 0);
        glScalef(scale_factor, scale_factor, 1);
            drawRectangle(-carWidth/2, carHeight/2, carWidth/2, -carHeight/2, BODY_COLOR);
            drawEllipse(0.0, 0.0, ellipseSmallAxis, ellipseBigAxis, ELLIPSE_COLOR);
//            drawCircle(0.0, 0.0, this->getRadius()/scale_factor);

        glPushMatrix();
            //move to gun position (body upper)
            glTranslatef(0.0, carHeight/2, 0.0);
            glPushMatrix();
                //drawing gun
                glRotated(this->gunRotation, 0.0, 0.0, 1);
                drawRectangle(-gunWidth/2, gunHeight, gunWidth/2, 0.0, GUN_COLOR);
            glPopMatrix();

            //drawing wheels and axis

            //////////////////////////////////// UPPER WHEELS /////////////////////////////////////////////////
            glPushMatrix();
                //drawing wheelshaft upper left
                glTranslatef(-carWidth/2 - wheelShaftWidth/2, -wheelAxisDistance - wheelShaftLength/2, 0);
                    drawRectangle(-wheelShaftWidth/2, wheelShaftLength/2, wheelShaftWidth/2, -wheelShaftLength/2, AXIS_COLOR);
                //drawing wheel upper left
                glTranslatef(-wheelShaftWidth/2 - wheelWidth/2 + CORRECTION_FACTOR, 0, 0);
                    glRotated(this->wheelRotation, 0.0, 0.0, 1);
                    drawRectangle(-wheelWidth/2, wheelLength/2, wheelWidth/2, -wheelLength/2, WHEEL_COLOR);
            glPopMatrix();

            glPushMatrix();
                //drawing wheelshaft upper right
                glTranslatef(carWidth/2 + wheelShaftWidth/2, -wheelAxisDistance - wheelShaftLength/2, 0);
                    drawRectangle(-wheelShaftWidth/2, wheelShaftLength/2, wheelShaftWidth/2, -wheelShaftLength/2, AXIS_COLOR);
                //drawing wheel upper right
                glTranslatef(wheelShaftWidth/2 + wheelWidth/2 - CORRECTION_FACTOR, 0, 0);
                    glRotated(wheelRotation, 0.0, 0.0, 1);
                    drawRectangle(-wheelWidth/2, wheelLength/2, wheelWidth/2, -wheelLength/2, WHEEL_COLOR);
            glPopMatrix();

            //////////////////////////////////// BOTTOM WHEELS /////////////////////////////////////////////////

            //moving to body bottom
            glTranslatef(0.0, -carHeight, 0.0);

            glPushMatrix();
                //drawing wheelshaft bottom left
                glTranslatef(-carWidth/2 - wheelShaftWidth/2, wheelAxisDistance + wheelShaftLength/2, 0);
                    drawRectangle(-wheelShaftWidth/2, wheelShaftLength/2, wheelShaftWidth/2, -wheelShaftLength/2, AXIS_COLOR);
                //drawing wheel bottom left
                glTranslatef(-wheelShaftWidth/2 - wheelWidth/2, 0, 0);
                    drawRectangle(-wheelWidth/2, wheelLength/2, wheelWidth/2, -wheelLength/2, WHEEL_COLOR);
            glPopMatrix();

            glPushMatrix();
                //drawing wheelshaft bottom right
                glTranslatef(carWidth/2 + wheelShaftWidth/2, wheelAxisDistance + wheelShaftLength/2, 0);
                    drawRectangle(-wheelShaftWidth/2, wheelShaftLength/2, wheelShaftWidth/2, -wheelShaftLength/2, AXIS_COLOR);
                //drawing wheel bottom right
                glTranslatef(wheelShaftWidth/2 + wheelWidth/2, 0, 0);
                    drawRectangle(-wheelWidth/2, wheelLength/2, wheelWidth/2, -wheelLength/2, WHEEL_COLOR);
            glPopMatrix();

        glPopMatrix();//Back to central position of car

    glPopMatrix();

}// End draw

Carro::~Carro(){};