#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "3d-space.h"
#include "coord3d.h"
#include "Particle.h"

bool is_equal_coord(Coord3D p1, Coord3D p2) {
    double epsilon = 0.0005;
    return abs(p1.x - p2.x) < epsilon && abs(p1.y - p2.y) < epsilon && abs(p1.z - p2.z) < epsilon;
}

bool is_equal_particle(Particle p1, Particle p2) {
    return is_equal_coord(*p1.pos, *p2.pos) && is_equal_coord(*p1.vel, *p2.vel);
}


TEST_CASE("Task A: length(Coord3D *p)") {
    Coord3D pointP = {10.0, 20.0, 30.0};
    CHECK(length(&pointP) == doctest::Approx(37.4166).epsilon(0.05));
    pointP = {0, 0, 0};
    CHECK(length(&pointP) == doctest::Approx(0).epsilon(0.05));
    pointP = {0, 1, 0};
    CHECK(length(&pointP) == 1);
    pointP = {1, 0, 0};
    CHECK(length(&pointP) == 1);
    pointP = {0, 0, 1};
    CHECK(length(&pointP) == 1);
    pointP = {1, 1, 1};
    CHECK(length(&pointP) == doctest::Approx(1.7321).epsilon(0.05));
    pointP = {-10, -20, -30};
    CHECK(length(&pointP) == doctest::Approx(37.4166).epsilon(0.05));
    pointP = {0.5, 0.05, -0.30};
    CHECK(length(&pointP) == doctest::Approx(0.58523).epsilon(0.05));
}

TEST_CASE("Task B: fartherFromOrigin(Coord3D *p1, Coord3D *p2)") {
    Coord3D p1 = {2, 3, 4};
    Coord3D p2 = {5, 6, 7};
    CHECK(fartherFromOrigin(&p1, &p2) == &p2);
    p1 = {0, 0, 0};
    p2 = {0, 0, 0};
    CHECK(fartherFromOrigin(&p1, &p2) == &p1); //func should return p1 if the two points are equal
    p1 = {0, 1, 0};
    p2 = {0, 0, 1};
    CHECK(fartherFromOrigin(&p1, &p2) == &p1);
    p1 = {-30.5, 11, 10};
    p2 = {-20, 10.5, -7};
    CHECK(fartherFromOrigin(&p1, &p2) == &p1);
}

TEST_CASE("Task C: move(Coord3D *ppos, Coord3D *pvel, double dt)") {
    Coord3D pos = {0, 0, 100.0};
    Coord3D vel = {1, -5, 0.2};

    move(&pos, &vel, 2.0);
    Coord3D new_pos = {2, -10, 100.4};
    CHECK(is_equal_coord(pos, new_pos));

    pos = {0, 0, 100.0};
    vel = {0, 13, 10};
    move(&pos, &vel, 2.0);
    new_pos = {0, 26, 120.0};
    CHECK(is_equal_coord(pos, new_pos));

    pos = {0, 0, 100.0};
    vel = {0, 13, 10};
    move(&pos, &vel, 0);
    new_pos = {0, 0, 100.0};
    CHECK(is_equal_coord(pos, new_pos));

    pos = {-10, 8.3, 200.0};
    vel = {0, 13, 10};
    move(&pos, &vel, 2.0);
    vel = {0, -13, -10};
    move(&pos, &vel, 2.0);
    new_pos = {-10, 8.3, 200.0};
    CHECK(is_equal_coord(pos, new_pos));

    pos = {0, 0, 100.0};
    vel = {0, 13, 10};
    move(&pos, &vel, -3); // negative time acts the same as negative velocity, moving the points backwards
    new_pos = {0, -39, 70.0};
    CHECK(is_equal_coord(pos, new_pos));
}

TEST_CASE("Task E: createCoord3D(double x, double y, double z)") {
    Coord3D p1 = {2, 4.0, -2.7};
    Coord3D *p2 = createCoord3D(2, 4.0, -2.7);
    CHECK(is_equal_coord(p1, *p2));

    p2 = createCoord3D(p1.x, p1.y, p1.z);
    CHECK(is_equal_coord(p1, *p2));
}

TEST_CASE("Task F: createParticle()") {
    Particle *p = createParticle(1.0, 1.5, 2.0, 0.1, 0.2, 0.3);
    CHECK(p->pos->x == 1.0);
    CHECK(p->pos->y == 1.5);
    CHECK(p->pos->z == 2.0);
    CHECK(p->vel->x == 0.1);
    CHECK(p->vel->y == 0.2);
    CHECK(p->vel->z == 0.3);
}

TEST_CASE("Task F: setVelocity()") {
    Particle *p = createParticle(1.0, 1.5, 2.0, 0.1, 0.2, 0.3);
    setVelocity(p, 4, -9, 0.3);
    CHECK(p->vel->x == 4);
    CHECK(p->vel->y == -9);
    CHECK(p->vel->z == 0.3);
}

TEST_CASE("Task F: getPosition") {
    Particle *p = createParticle(1.0, 1.5, 2.0, 0.1, 0.2, 0.3);
    Coord3D pos = {1.0, 1.5, 2.0};
    CHECK(is_equal_coord(getPosition(p), pos));

}

TEST_CASE("Task F: move()") {
    Particle *p1 = createParticle(1.0, 1.5, 2.0, 0.1, 0.2, 0.3);
    Particle *p2 = createParticle(1.2, 1.9, 2.6, 0.1, 0.2, 0.3);
    move(p1, 2.0);
    CHECK(is_equal_particle(*p1, *p2));

    p1 = createParticle(1.0, 1.5, 2, 0.1, 0, 0.3);
    p2 = createParticle(0.8, 1.5, 1.4, 0.1, 0, 0.3);
    move(p1, -2.0);
    CHECK(is_equal_particle(*p1, *p2));

    p1 = createParticle(1, 3.1, -10, -2, 1, 1.1);
    p2 = createParticle(-7, 7.1, -5.6, -2, 1, 1.1);
    move(p1, 4);
    CHECK(is_equal_particle(*p1, *p2));

}