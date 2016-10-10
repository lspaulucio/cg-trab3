#ifndef CIRCULO_H
#define CIRCULO_H

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "forma.h"
#include "types.h"

class Circulo: public Forma
{
    private:
        float radius;
        int drawResolution;

    public:

        Circulo();

        Circulo(const Circulo&);

        float getRadius() const;

        void setRadius(float);

        int getDrawResolution() const;

        void setDrawResolution(int);

        void translate(float, float);

        bool insideCircle(float, float) const;

        bool insideCircle(Circulo&) const;

        bool outsideCircle(Circulo&) const;

        void draw();

        ~Circulo();

};



#endif //CIRCULO_H
