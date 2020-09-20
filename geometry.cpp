#include <GL/glut.h>
#include "geometry.h"

Vector2::Vector2(){}
Vector2::Vector2(GLfloat x, GLfloat y){
    this->x = x;
    this->y = y;
}

void Vector2::operator+(Vector2 &other){
    this->x += other.x;
    this->y += other.y;
}

double degreeToRadians(double degree){
    return (M_PI * degree) / 180;
}
