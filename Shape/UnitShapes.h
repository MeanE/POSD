#ifndef UNITSHAPES_H_INCLUDED
#define UNITSHAPES_H_INCLUDED

#include "..\cppunitlite\TestHarness.h"
#include "Shapes.h"
#include "Compute.h"
//#include <iostream>
using namespace std;

const double EPSLION_IN_UNITSHAPES=0.000001;

TEST (Circle_first, Circle) {
    Circle cir(0,0, 10);

    DOUBLES_EQUAL(314.15926, cir.area(), EPSLION_IN_UNITSHAPES);
    DOUBLES_EQUAL(62.831852, cir.perimeter(), EPSLION_IN_UNITSHAPES);
    //FAIL("123456");
}

TEST (Circle_Name, Circle) {
    Circle cir(0,0, 10, "cirTest");
    string cirName=cir.getName(); //default value: unknown

    CHECK("cirTest"==cirName);
    //FAIL("123456");
}

TEST (Rectangle_first, Rectangle) {
    Rectangle rect(0,0, 2,5);

    DOUBLES_EQUAL(10, rect.area(), EPSLION_IN_UNITSHAPES);
    DOUBLES_EQUAL(14, rect.perimeter(), EPSLION_IN_UNITSHAPES);
    //FAIL("123456");
}

TEST (Triangle_first, Triangle) {
    Triangle tri(1,-1, 4,-1, 4,3);

    DOUBLES_EQUAL(6, tri.area(), EPSLION_IN_UNITSHAPES);
    DOUBLES_EQUAL(12, tri.perimeter(), EPSLION_IN_UNITSHAPES);
    //FAIL("123456");
}

TEST (Triangle_isTriangle, Triangle) {
    Triangle tri(1,-1, 4,-1, 4,3); //trueTriangle
    Triangle tri2(1,-1, 1,-1, 1,3); //falseTriangle
    Triangle tri3(0,0, 1,1, 3,3); //falseTriangle

    CHECK_EQUAL(true, tri.getIsTriangle());
    CHECK_EQUAL(false, tri2.getIsTriangle());
    CHECK_EQUAL(false, tri3.getIsTriangle());
    //FAIL("123456");
}

TEST (Compute_sumOfPerimeter, Compute) {
    Compute cpt;

    Triangle tri(1,-1, 4,-1, 4,3); //12
    Rectangle rect(0,0, 2,5); //14
    Circle cir(0,0, 10); //62.831852
    vector<Shape*> shp{&tri, &rect, &cir};

    DOUBLES_EQUAL(88.831852, cpt.sumOfPerimeter(shp), EPSLION_IN_UNITSHAPES);
    //FAIL("123456");
}

TEST (Compute_sumOfArea, Compute) {
    Compute cpt;

    Triangle tri(1,-1, 4,-1, 4,3); //6
    Rectangle rect(0,0, 2,5); //10
    Circle cir(0,0, 10); //314.15926
    vector<Shape*> shp{&tri, &rect, &cir};

    DOUBLES_EQUAL(330.15926, cpt.sumOfArea(shp), EPSLION_IN_UNITSHAPES);
    //FAIL("123456");
}

TEST (Compute_maxArea, Compute) {
    Compute cpt;

    Triangle tri(1,-1, 4,-1, 4,3, "tri1"); //6
    Rectangle rect(0,0, 2,5, "rect1"); //10
    Circle cir(0,0, 10, "cir1"); //314.15926
    vector<Shape*> shp{&tri, &rect, &cir};

    Shape* maxAreaShape = cpt.maxArea(shp);

    CHECK("cir1" == maxAreaShape->getName());
    DOUBLES_EQUAL(314.15926, maxAreaShape->area(), EPSLION_IN_UNITSHAPES);
    CHECK(&cir == maxAreaShape);
    //FAIL("123456");
}

TEST (Compute_sortByDecreasingPerimeter, Compute) {
    Compute cpt;

    Triangle tri(1,-1, 4,-1, 4,3, "tri1"); //12
    Rectangle rect(0,0, 2,5, "rect1"); //14
    Rectangle rect2(0,0, 20,20, "rect2"); //80
    Circle cir(0,0, 10, "cir1"); //62.831852
    vector<Shape*> shp{&tri, &rect, &rect2, &cir};

    cpt.sortByDecreasingPerimeter(shp);

    CHECK("rect2" == shp[0]->getName());
    DOUBLES_EQUAL(80, shp[0]->perimeter(), EPSLION_IN_UNITSHAPES);
    CHECK(&rect2 == shp[0]);

    CHECK("cir1" == shp[1]->getName());
    DOUBLES_EQUAL(62.831852, shp[1]->perimeter(), EPSLION_IN_UNITSHAPES);
    CHECK(&cir == shp[1]);

    CHECK("rect1" == shp[2]->getName());
    DOUBLES_EQUAL(14, shp[2]->perimeter(), EPSLION_IN_UNITSHAPES);
    CHECK(&rect == shp[2]);

    CHECK("tri1" == shp[3]->getName());
    DOUBLES_EQUAL(12, shp[3]->perimeter(), EPSLION_IN_UNITSHAPES);
    CHECK(&tri == shp[3]);
    //FAIL("123456");
}


#endif // UNITSHAPES_H_INCLUDED
