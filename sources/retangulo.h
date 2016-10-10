#ifndef RETANGULO_H
#define RETANGULO_H

#include "forma.h"
#include <iostream>

class Retangulo: public Forma
{
private:
    float width, height;
    float vertices[4][3];

public:

    Retangulo();

    Retangulo(const Retangulo&);

    float getWidth() const;

    void setWidth(float);

    float getHeight() const;

    void setHeight(float);

    const float* getVertices(int n) const;

    const float getVertices(int, AXES) const;

    void translate(float, float);

    void updateVertices();

    bool insideSquare(float, float) const;

    void draw();

    ~Retangulo();

};


#endif //RETANGULO_H
