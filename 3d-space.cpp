#include <iostream>
#include <cmath>
#include "3d-space.h"
#include "coord3d.h"
#include "Particle.h"

double length(Coord3D *p){
    /*
    Function receives the coordinates of a point P passed as a pointer, 
    and computes the distance from the origin to the point P.
    */
    
    return sqrt(pow((*p).x, 2) + pow((*p).y, 2) + pow((*p).z, 2));
}    

Coord3D * fartherFromOrigin(Coord3D *p1, Coord3D *p2) {
    /*
    Function receives the coordinates of two points (passed as pointers), 
    and returns the pointer of the point that is farther away from the origin.
    */

   if (length(p1) >= length(p2)) {
       return p1;
   } else {
       return p2;
   }
}

void move(Coord3D *ppos, Coord3D *pvel, double dt) {
    //x' = x + vel.x * dt;
    /*
    Function gets the position and the velocity of an object
    and has to compute object’s new coordinates after the time interval dt.
    */
   (*ppos).x += (*pvel).x * dt;
   (*ppos).y += (*pvel).y * dt;
   (*ppos).z += (*pvel).z * dt;
}

Coord3D* createCoord3D(double x, double y, double z) {
    Coord3D *p = new Coord3D;
    (*p).x = x;
    (*p).y = y;
    (*p).z = z;
    return p;
}

void deleteCoord3D(Coord3D *p) {
    delete p;
}

//particle
Particle* createParticle(double x, double y, double z, double vx, double vy, double vz) {
    // dynamically allocates memory for a particle and initialize it
    Particle *p = new Particle;
    p->pos = new Coord3D;
    p->vel = new Coord3D;
    
    p->pos->x = x;
    p->pos->y = y;
    p->pos->z = z;

    p->vel->x = vx;
    p->vel->y = vy;
    p->vel->z = vz;

    return p;
}

void setVelocity(Particle *p, double vx, double vy, double vz) {
    // sets a particle's velocity to (vx, vy, vz)
    p->vel->x = vx;
    p->vel->y = vy;
    p->vel->z = vz;
}

Coord3D getPosition(Particle *p) {
    // gets a particle's current position
    return *(p->pos);
}

void move(Particle *p, double dt) {
    // updates a particle's position after elapsed time dt
    move((*p).pos, (*p).vel, dt);
}

void deleteParticle(Particle *p) {
    // deletes all memory allocated for the particle passed by pointer
    delete p->vel;
    delete p->pos;
    delete p;
}
