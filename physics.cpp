#include "physics.h"
#include <cmath>


double getVx(double v0, double angle) {
    return v0 * sin(angle);
}

double getV0y(double v0, double angle) {
    return v0 * cos(angle);
}

double getVy(double v0y, double t) {
    return v0y + GRAVITY * t;
}

double getTrajetoryTime(double v0y) {
    return -2 * v0y / GRAVITY;
}