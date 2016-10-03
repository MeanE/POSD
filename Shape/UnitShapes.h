#ifndef UNITSHAPES_H_INCLUDED
#define UNITSHAPES_H_INCLUDED

#include "..\cppunitlite\TestHarness.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Compute.h"
using namespace std;

const double EPSLION=0.000001;

TEST (Circle_first, Circle) {
    Circle cir(0,0, 10);

    DOUBLES_EQUAL(314.15926, cir.area(), EPSLION);
    DOUBLES_EQUAL(62.831852, cir.perimeter(), EPSLION);
    //FAIL("123456");
}

TEST (Rectangle_first, Rectangle) {
    Rectangle rect(0,0, 2,5);

    DOUBLES_EQUAL(10, rect.area(), EPSLION);
    DOUBLES_EQUAL(14, rect.perimeter(), EPSLION);
    //FAIL("123456");
}

TEST (Triangle_first, Triangle) {
    Triangle tri(1,-1, 4,-1, 4,3);

    DOUBLES_EQUAL(6, tri.area(), EPSLION);
    DOUBLES_EQUAL(12, tri.perimeter(), EPSLION);
    //FAIL("123456");
}
TEST (isTriangle, Triangle) {
    Triangle tri(1,-1, 4,-1, 4,3); //trueTriangle
    Triangle tri2(1,-1, 1,-1, 1,3); //falseTriangle

    CHECK_EQUAL(true, tri.getIsTriangle());
    CHECK_EQUAL(false, tri2.getIsTriangle());
    //FAIL("123456");
}

TEST (sumOfPerimeter, Compute) {
    Compute cpt;

    Triangle tri(1,-1, 4,-1, 4,3);
    Rectangle rect(0,0, 2,5);
    Circle cir(0,0, 10);
    vector<Shape*> shp{&tri, &rect, &cir};

    DOUBLES_EQUAL(330.15926, cpt.sumOfPerimeter(shp), EPSLION);
    //FAIL("123456");
}

#endif // UNITSHAPES_H_INCLUDED
