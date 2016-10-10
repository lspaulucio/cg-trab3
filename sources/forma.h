#ifndef FORMA_H
#define FORMA_H

#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include <iostream>
#include <stdlib.h>
#include "types.h"

class Forma
{
    private:
        float RGBColors[3];
        float xc, yc;
        std::string id;

    public:

        Forma();

        Forma(const Forma&);

        const float* getRGBColors() const;

        const float getRGBColors(COLOR_ID) const;

        int colorVerification(std::string);

        void setRGBColors(const float[3]);

        void setRGBColors(std::string);

        float getXc() const;

        void setXc(float);

        float getYc() const;

        void setYc(float);

        const std::string &getId() const;

        void setId(const std::string&);

        virtual void translate(float, float)=0;

        virtual void draw()=0;

        ~Forma();

};



#endif //FORMA_H
