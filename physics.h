#ifndef PHYSICS_H
#define PHYSICS_H
#pragma once

#define GRAVITY -10.0
#define V0 8.2

double getVx(double v0, double angle);

double getV0y(double v0, double angle);

double getVy(double v0y, double t);

double getTrajetoryTime(double v0y);



#endif // PHYSICS_H
