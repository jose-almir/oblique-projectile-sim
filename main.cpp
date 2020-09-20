#include <GL/glut.h>
#include <sys/time.h>
#include <cmath>
#include <iostream>
#include <vector>
#include "graphics.h"
#include "physics.h"

#define MAX_BULLETS 5


struct Config {
    double st;
    double dt;
    double lt;
    double et;
};


void init(void);
void keyboardSpecial(int, int, int);
void keyboardActions(unsigned char, int, int);
void display(void);
double getTime(void);
void timer(int);
void animate();
Bullet createBullet(void);
void handleBullets(void);
void drawBulletsInfo(void);

Config config;
Grid grid(25, 15);
Cannon cannon(Vector2(-98,-58), 45);
StrokeText angleText("45", Vector2(-99.5,-58.5), Color(.0, .0, .0));
Border border(Color(1.0, 1.0, 1.0), 2);
vector<Bullet> bullets;

int main(int argc, const char *argv[]){
    glutInit(&argc, (char **)argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_MULTISAMPLE);
    glutInitWindowSize(W, H);
    glutCreateWindow("Cannon Interativity");
    glutDisplayFunc(display);
    glutSpecialFunc(keyboardSpecial);
    glutKeyboardFunc(keyboardActions);
    glutTimerFunc(DELTA_CALLBACK_MS, timer, 0);
    init();
    glutPostRedisplay();
    glutMainLoop();


    return 0;
}

void init() {
    glEnable(GL_MULTISAMPLE);
    glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
    glOrtho(-UX, UX, -UY, UY, -UZ, UZ);
    config.lt = getTime();
    config.st = config.lt;
}


void keyboardSpecial(int key, int x, int y) {
    int angle = cannon.angle;

    switch(key){
        case GLUT_KEY_UP:
            cannon.setAngle(angle + 5);
            break;
        case GLUT_KEY_DOWN:
            cannon.setAngle(angle - 5);
            break;
    }
    angleText.setText(to_string(cannon.angle));

}

void display(){
    glClear (GL_COLOR_BUFFER_BIT);
    grid.draw();
    glLineWidth(5.0);
    for(int i = 0; i < bullets.size(); ++i){
        bullets[i].draw();
        glPointSize(2.0);
        for(int j = 0; j < bullets[i].trajetory.size(); ++j){
            glBegin(GL_POINTS);
                glVertex2f(bullets[i].trajetory[j].x, bullets[i].trajetory[j].y);
            glEnd();
        }
    }
    border.draw();
    cannon.draw();
    angleText.draw();
    drawBulletsInfo();
    glutSwapBuffers();
}

double getTime() {
    struct timeval time;
    gettimeofday(&time, NULL);

    return time.tv_sec + 1e-6 * time.tv_usec;
}

void timer(int id){
    glutTimerFunc(DELTA_CALLBACK_MS, timer, 0);
    double now = getTime();
    double dt = now - config.lt;
    config.et = now - config.st;
    glutPostRedisplay();
    animate();
    config.lt = now;
}

void animate() {
    handleBullets();
}

Bullet createBullet(){
    Bullet newBullet;
    newBullet.cannonAngle = cannon.angle;
    newBullet.firstTime = config.et;
    newBullet.color = generateColor();
    newBullet.point = Vector2(-100, -60);
    newBullet.v0y = getV0y(V0, degreeToRadians(90 - cannon.angle));
    newBullet.vel = Vector2(getVx(V0, degreeToRadians(90 - cannon.angle)), newBullet.v0y);

    return newBullet;
}

void keyboardActions(unsigned char key, int x, int y) {
    if(key != 32 || bullets.size() > MAX_BULLETS) return;
    Bullet bullet = createBullet();
    bullets.push_back(bullet);
}

void handleBullets(){
    for(int i = 0; i < bullets.size(); ++i){
        bullets[i].vel.y = getVy(bullets[i].v0y, config.et - bullets[i].firstTime);
        if(!bullets[i].stop) bullets[i].point + bullets[i].vel;
        bullets[i].trajetory.push_back(bullets[i].point);

        if(bullets[i].vel.y < 0 && bullets[i].point.y <= -UY){
            bullets.erase(bullets.begin() + i);
        }
    }
}

void drawBulletsInfo() {
    GLfloat x0 = 30;
    for(int i = 0; i < bullets.size(); ++i){
       
        string text = "Vx = " + to_string(bullets[i].vel.x) + " | " + "Vy = " + to_string(bullets[i].vel.y);
        Circle(Vector2(x0, 50 - i * 8), 2.5, bullets[i].color).draw();
        StrokeText(to_string(i + 1), Vector2(x0 - 1, 50 - i * 8 - 1), Color(.0, .0, .0)).draw();
        StrokeText(text, Vector2(x0 + 3.5, 50 - i * 8 - 1), bullets[i].color).draw();
    }
}