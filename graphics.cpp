#include <GL/glut.h>
#include <cmath>
#include "graphics.h"

Cannon::Cannon(Vector2 point, int angle){
    this->point = point;
    this->angle = angle;
}

void Cannon::setAngle(int angle){
    if(angle <= 75 && angle >= 15)
        this->angle = angle;
}

void Cannon::draw() {
    Rectangle rect(point, 25.0, 10.0, Color(.5, .5, .5));
    glPushMatrix();
    glTranslatef(rect.point.x, rect.point.y, .0);
    glRotatef(angle, 0, 0, 1);
    glTranslatef(-rect.point.x, -rect.point.y, .0);
    rect.draw();
    glPopMatrix();
}

Rectangle::Rectangle(){}
Rectangle::Rectangle(Vector2 point, GLfloat width, GLfloat height, Color color){
    this->point = point;
    this->width = width;
    this->height = height;
    this->color = color;
}


void Rectangle::draw(){
    glColor3f(color.red, color.green, color.blue);
    glBegin(GL_QUADS);
        glVertex2f(point.x - width/2.0, point.y - height/2.0);
        glVertex2f(point.x + width/2.0, point.y - height/2.0);
        glVertex2f(point.x + width/2.0, point.y + height/2.0);
        glVertex2f(point.x - width/2.0, point.y + height/2.0);
    glEnd();
}

Circle::Circle(Vector2 center, GLfloat radius, Color color, bool hasFill){
    this->center = center;
    this->radius = radius;
    this->color = color;
    this->hasFill = hasFill;
}
void Circle::draw(){
    double angle = (2.0 * M_PI) / 360;
    glLineWidth(10.0);
    glColor3f(color.red, color.green, color.blue);
    glBegin(hasFill? GL_POLYGON : GL_LINE_LOOP);
    for (double i = 0.0; i < 2.0 * M_PI; i += angle){
        glVertex2f(center.x + radius * cos(i), center.y + radius * sin(i));
    }
    glEnd();
}

Color::Color(){}
Color::Color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha){
    this->red = red;
    this->green = green;
    this->blue = blue;
    this->alpha = alpha;
}


StrokeText::StrokeText(string text, Vector2 point, Color color, GLfloat size){
    this->text = text;
    this->point = point;
    this->color = color;
    this->size = size;
}

void StrokeText::draw(){
    double factor = 1.0/ size;

    glColor3f(color.red, color.green, color.blue);
    glLineWidth(1.5);
    
    glPushMatrix();
    glScalef(size, size, 0.0);
    glTranslatef(point.x * factor, point.y * factor, .0);
    for(int i = 0; i < text.size(); ++i){
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, text[i]);
    }

    glPopMatrix();
}

void StrokeText::setText(string text){
    this->text = text;
}

Border::Border(Color color, int width){
    rect1 = Rectangle(Vector2(-UX, -UY), 4*UX, width, color);
    rect2 = Rectangle(Vector2(-UX, UY), 4*UX, width, color);
    rect3 = Rectangle(Vector2(-UX, UY), width, 4*UX, color);
    rect4 = Rectangle(Vector2(UX, -UY), width, 4*UX, color);
    
}

void Border::draw(){
    rect1.draw();
    rect2.draw();
    rect3.draw();
    rect4.draw();
}

Bullet::Bullet() {}

void Bullet::draw() {
    Circle circle(point, 2.5, color);
    circle.draw();
}

Grid::Grid(int verticalAxis, int horizontalAxis) {
    this->verticalAxis = verticalAxis;
    this->horizontalAxis = horizontalAxis;
}

void Grid::draw() {
    double horizontalGap = 2.0 * UX / verticalAxis;
    double verticalGap = 2.0 * UY / horizontalAxis;
    double y1 = -60, y2 = 60;
    double x1 = -100, x2 = 100;

    glLineWidth(.5);
    glColor3f(.15, .15, .15);
    for(int i = 0; i < verticalAxis; ++i){
        glBegin(GL_LINES);
            double x = -100 + horizontalGap * i;
            glVertex2f(x, y1);
            glVertex2f(x, y2);
        glEnd();

        glBegin(GL_LINES);
            double y = -60 + verticalGap * i;
            glVertex2f(x1, y);
            glVertex2f(x2, y);
        glEnd();
    }
}

Color generateColor() {
    double r = rand() % 255 / 255.0;
    double g = rand() % 255 / 255.0;
    double b = rand() % 255 / 255.0;

    return Color(r, g, b);
}