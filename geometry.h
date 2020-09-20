#ifndef GEOMETRY_H
#define GEOMETRY_H
#pragma once

#define UX 100
#define UY 60
#define UZ 100

#include <cmath>


class Vector2 {
    public:
    GLfloat x, y;
    Vector2();
    Vector2(GLfloat x, GLfloat y);
    void operator+(Vector2 &other);
};

double degreeToRadians(double degree);

#endif // GEOMETRY_H
