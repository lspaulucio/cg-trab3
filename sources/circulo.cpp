#include "circulo.h"

Circulo::Circulo()
{
    radius = 0;
    drawResolution = 100;
}

Circulo::Circulo(const Circulo &c): Forma(c)
{
    this->radius = c.radius;
    this->drawResolution = c.drawResolution;
}

float Circulo::getRadius() const
{
    return this->radius;
}

void Circulo::setDrawResolution(int new_resolution)
{
    this->drawResolution = new_resolution;
}

int Circulo::getDrawResolution() const
{
    return this->drawResolution;
}

void Circulo::setRadius(float radius)
{
    this->radius = radius;
}

void Circulo::translate(float dx, float dy)
{
    this->setXc(this->getXc() + dx);
    this->setYc(this->getYc() + dy);
}

bool Circulo::insideCircle(float x, float y) const
{
    float dx, dy, dist;

    dx = this->getXc() - x;
    dy = this->getYc() - y;

    dist = sqrt((dx*dx) + (dy*dy));

    if(dist <= this->radius) {
        return true;
    }
    else {
        return false;
    }
}

bool Circulo::insideCircle(Circulo &circ) const
{
    float dx, dy, dist;

    dx = this->getXc() - circ.getXc();
    dy = this->getYc() - circ.getYc();

    dist = sqrt((dx*dx) + (dy*dy));
    if(dist <= abs(this->radius - circ.getRadius()))
    {
        return true;
    }
    else return false;
}

bool Circulo::outsideCircle(Circulo &circ) const
{
    float dx, dy, dist;

    dx = this->getXc() - circ.getXc();
    dy = this->getYc() - circ.getYc();

    dist = sqrt((dx*dx) + (dy*dy));
    if(dist >= (this->radius + circ.getRadius()))
    {
        return true;
    }
    else return false;

}

void Circulo::draw()
{
    float dx, dy;
    glColor3fv((GLfloat*)(this->getRGBColors()));
    glBegin(GL_TRIANGLE_FAN);
		glVertex2f(this->getXc(), this->getYc());
		for(int i = 0; i <= this->getDrawResolution(); i++)
        {
            dx = this->getXc() + (this->getRadius() * cos(i * 2.0*M_PI / this->getDrawResolution()));
            dy = this->getYc() + (this->getRadius() * sin(i * 2.0*M_PI / this->getDrawResolution()));
			glVertex2f(dx, dy);
		}
    glEnd();
}

Circulo::~Circulo(){};
