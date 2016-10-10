#ifndef FUNCOES_H
#define FUNCOES_H

#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include <vector>
#include <math.h>
#include "types.h"
#include "../tinyxml2/tinyxml2.h"
#include "forma.h"
#include "janela.h"
#include "circulo.h"
#include "retangulo.h"

using namespace std;
using namespace tinyxml2;

void readXMLFile(const char*);

//OpenGL functions
void init(void);
void display(void);
void idle(void);
void mouse(int, int, int, int);
void mouseMotion(int, int);
void keypress (unsigned char, int, int);
void keyUp (unsigned char, int, int);

//Drawing functions
void drawRectangle(float, float, float, float, const float colors[3] = DEFAULT_COLOR);
void drawCircle(float, float, float, const float colors[3] = DEFAULT_COLOR, int resolution=100);



#endif //FUNCOES_H
