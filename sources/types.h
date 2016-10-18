#ifndef TYPES_H
#define TYPES_H

const float DEFAULT_COLOR[3] = {0.0};  //BLACK
const float BLUE_COLOR[3] = {0.0, 0.0, 1.0};  //BLUE
const float GREEN_COLOR[3] = {0.0, 1.0, 0.0};  //GREEN
const float RED_COLOR[3] = {1.0, 0.0, 0.0};  //RED
const float GREY_COLOR[3] = {0.32, 0.32, 0.32}; // GREY
const float YELLOW_COLOR[3] = {1.0, 1.0, 0.0}; // YELLOW
typedef enum {RED, GREEN, BLUE, BLACK, WHITE} COLOR_ID;
typedef enum {X_AXIS, Y_AXIS, Z_AXIS} AXES;

#endif // TYPES_H
