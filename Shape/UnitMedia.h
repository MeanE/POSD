#ifndef UNITMEDIA_H_INCLUDED
#define UNITMEDIA_H_INCLUDED

#include "..\cppunitlite\TestHarness.h"
#include "Shapes.h"
#include "Medias.h"
#include "Visitors.h"
#include <iostream>
using namespace std;

const double EPSLION_IN_UNITMEDIA=0.000001;

TEST (Area, ShapeMedia) {
    Rectangle rect(0,0, 2,5);
    ShapeMedia sm(&rect);

    DOUBLES_EQUAL(10, sm.area(), EPSLION_IN_UNITMEDIA);
}

TEST (Add, ComboMedia) {
    Rectangle rect(0,0, 2,5);
    ShapeMedia sm(&rect);

    ComboMedia cm;
    cm.add(&sm);

    CHECK(cm.getMediaPieces()[0] == &sm);
}

TEST (AreaVisitor, ShapeMedia) {
    Rectangle rect(0,0, 2,5);
    ShapeMedia sm(&rect);

    AreaVisitor av;
    sm.accept(&av);

    DOUBLES_EQUAL(10, av.getArea(), EPSLION_IN_UNITMEDIA);
//    FAIL("123456");
}

TEST (AreaVisitor, ComboMedia) {
    /**total area:10.3923048454.....*/
    Rectangle rect(0,0, 2,2.*sqrt(3.));
    Triangle tri1(0,2*sqrt(3), -1.,sqrt(3), 0,0);
    Triangle tri2(2,0, 2,2.*sqrt(3), 3,sqrt(3));
    ShapeMedia r1(&rect);
    ShapeMedia t1(&tri1);
    ShapeMedia t2(&tri2);

    /**Combo(rectangle,triangle)*/
    ComboMedia cRT;
    cRT.add(&r1);
    cRT.add(&t1);
    /**Combo(Combo,triangle)*/
    ComboMedia cCT;
    cCT.add(&cRT);
    cCT.add(&t2);

    AreaVisitor av;
    cCT.accept(&av);

    DOUBLES_EQUAL(10.3923048454, av.getArea(), EPSLION_IN_UNITMEDIA);
}

TEST (PerimeterVisitor, ComboMedia) {
    /**total perimeter:25.8564064605.....*/
    Rectangle rect(0,0, 2,2.*sqrt(3.));
    Triangle tri1(0,2.*sqrt(3.), -1,sqrt(3.), 0,0);
    Triangle tri2(2,0, 2,2.*sqrt(3.), 3,sqrt(3.));
    ShapeMedia r1(&rect);
    ShapeMedia t1(&tri1);
    ShapeMedia t2(&tri2);

    /**Combo(rectangle,triangle)*/
    ComboMedia cRT;
    cRT.add(&r1);
    cRT.add(&t1);
    /**Combo(Combo,triangle)*/
    ComboMedia cCT;
    cCT.add(&cRT);
    cCT.add(&t2);

    PerimeterVisitor pv;
    cCT.accept(&pv);

    DOUBLES_EQUAL(25.8564064605, pv.getPerimeter(), EPSLION_IN_UNITMEDIA);
}

TEST (DescriptionVisitor, ShapeMedia) {
    Rectangle rect(0,0, 4,8);
    ShapeMedia r1(&rect);
    Circle cir(-2,1, 2);
    ShapeMedia c1(&cir);
    Triangle tri(1,-1, 4,-1, 4,3);
    ShapeMedia t1(&tri);

    DescriptionVisitor dv1;
    r1.accept(&dv1);
    DescriptionVisitor dv2;
    c1.accept(&dv2);
    DescriptionVisitor dv3;
    t1.accept(&dv3);

    string descriptions = dv1.getDescription() + dv2.getDescription() + dv3.getDescription();

    CHECK("r(0 0 4 8) c(-2 1 2) t(1 -1 4 -1 4 3) " == descriptions);
}
#endif // UNITMEDIA_H_INCLUDED
