#ifndef UNITSHAPES_H_INCLUDED
#define UNITSHAPES_H_INCLUDED

#include "..\cppunitlite\TestHarness.h"
#include "Shapes.h"

const double EPSLION=0.000001;
TEST (first, Circle) {
    Circle cir(0,0, 10);

    DOUBLES_EQUAL(314.15926, cir.area(), EPSLION);
    DOUBLES_EQUAL(62.831852, cir.perimeter(), EPSLION);
    //FAIL("123456");
}

TEST (second, Rectangle) {
    Rectangle rect(0,0, 2,5);

    DOUBLES_EQUAL(10, rect.area(), EPSLION);
    DOUBLES_EQUAL(14, rect.perimeter(), EPSLION);
    //FAIL("123456");
}

TEST (thrid, Triangle) {
    Triangle tri(1,-1, 4,-1, 4,3);

    DOUBLES_EQUAL(6, tri.area(), EPSLION);
    DOUBLES_EQUAL(12, tri.perimeter(), EPSLION);
    //FAIL("123456");
}

TEST (fourth, sumOfPerimeter) {
    Triangle tri(1,-1, 4,-1, 4,3);
    Rectangle rect(0,0, 2,5);
    Circle cir(0,0, 10);
    vector<Shape*> shp{&tri, &rect, &cir};

    DOUBLES_EQUAL(330.15926, sumOfPerimeter(shp), EPSLION);
    //FAIL("123456");
}

#endif // UNITSHAPES_H_INCLUDED
