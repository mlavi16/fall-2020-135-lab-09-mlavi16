#include <iostream>
#include "3d-space.h"
#include "coord3d.h"

int main()
{
    //length() test
    Coord3D pointP = {10, 20, 30};
    std::cout << length(&pointP) << std::endl << std::endl; // would print 37.4166


    //fartherFromOrigin() test
    pointP = {10, 20, 30};
    Coord3D pointQ = {-20, 21, -22};

    std::cout << "Address of P: " << &pointP << std::endl;
    std::cout << "Address of Q: " << &pointQ << std::endl;

    Coord3D * ans = fartherFromOrigin(&pointP, &pointQ);
   
    std::cout << "ans = " << ans << std::endl << std::endl; // P > Q


    //move() test
    Coord3D pos = {0, 0, 100.0};
    Coord3D vel = {1, -5, 0.2};

    move(&pos, &vel, 2.0); // object pos gets changed
    std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl << std::endl;
    // prints: 2 -10 100.4


    //createCoord3D() tests
    double x, y, z;
    std::cout << "Enter position x y z: ";
    std::cin >> x >> y >> z;
    Coord3D *ppos = createCoord3D(x,y,z);
    
    std::cout << "Enter velocity vx vy vz: ";
    std::cin >> x >> y >> z;
    Coord3D *pvel = createCoord3D(x,y,z);

    move(ppos, pvel, 10.0);

    std::cout << "Coordinates after 10 seconds: " 
         << (*ppos).x << " " << (*ppos).y << " " << (*ppos).z << std::endl << std::endl;

    deleteCoord3D(ppos); // release memory
    deleteCoord3D(pvel);

    
    // particle tests

    // make new particle
    Particle *p = createParticle(1.0, 1.5, 2.0, 0.1, 0.2, 0.3);
    double time = 0.0;
    double dt = 0.1;
    while(time < 3.0) {
        // update its velocity
        setVelocity(p, 10.0 * time, 0.3, 0.1);

        // move the particle
        move(p, dt);
        time += dt;

        // reporting its coordinates
        std::cout << "Time: " << time << " \t";
        std::cout << "Position: "
             << getPosition(p).x << ", "
             << getPosition(p).y << ", "
             << getPosition(p).z << std::endl;
    }
    // remove the particle, deallocating its memory
    deleteParticle(p);
    return 0;
}