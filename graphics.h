#ifndef GRAPHICS_H
#define GRAPHICS_H
#pragma once

#define W 1000
#define H 600

#define FONT_SMALL 0.02
#define FONT_MEDIUM 0.04
#define FONT_LARGE 0.06
#define FONT_XLARGE 0.08

#define DELTA_CALLBACK_MS 33

#include "geometry.h"
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

class Color {
public:
    GLfloat red;
    GLfloat green;
    GLfloat blue;
    GLfloat alpha;
    Color();
    Color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha = 1.0);
};


class Object {
public:
    virtual void draw() = 0;
};

class Rectangle : public Object {
public:
    Vector2 point;
    GLfloat width;
    GLfloat height;
    Color color;
    Rectangle();
    Rectangle(Vector2 point, GLfloat width, GLfloat height, Color color);
    void draw();
};

class Circle : public Object {
public:
    Vector2 center;
    GLfloat radius;
    Color color;
    bool hasFill;
    Circle(Vector2 center, GLfloat radius, Color color, bool hasFill = true);
    void draw();
};

class StrokeText : public Object {
public:
    string text;
    Vector2 point;
    GLfloat size;
    Color color;
    StrokeText(string text, Vector2 point, Color color, GLfloat size = FONT_SMALL);
    void setText(string text);
    void draw();
};

class Cannon : public Object {
public:
    Vector2 point;
    int angle;
    Cannon(Vector2 point, int angle);
    void setAngle(int angle);
    void draw();
};

class Bullet : public Object {
public:
    Vector2 point;
    Vector2 vel;
    GLfloat v0y;
    GLfloat cannonAngle;
    GLfloat firstTime;
    Color color;
    bool stop;
    vector<Vector2> trajetory;
    Bullet();
    void draw();
};

class Border : public Object {
public:
    Rectangle rect1;
    Rectangle rect2;
    Rectangle rect3;
    Rectangle rect4;

    Border(Color color, int width);
    void draw();
};

class Grid : public Object {
public:
    int verticalAxis;
    int horizontalAxis;
    Grid(int verticalAxis, int horizontalAxis);
    void draw();
};

Color generateColor();

#endif // GRAPHICS_H
