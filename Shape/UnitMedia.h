#ifndef UNITMEDIA_H_INCLUDED
#define UNITMEDIA_H_INCLUDED

#include "..\cppunitlite\TestHarness.h"
#include "Shapes.h"
#include "Medias.h"
#include "Visitors.h"
#include "Builders.h"
#include <iostream>
#include <stack>
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

TEST (visitShapeMedia, DescriptionVisitor) {
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

TEST (visitComboMedia, DescriptionVisitor) {
    Rectangle rect(0,0, 4,8);
    ShapeMedia r1(&rect);
    Circle cir(-2,1, 2);
    ShapeMedia c1(&cir);
    Triangle tri(1,-1, 4,-1, 4,3);
    ShapeMedia t1(&tri);

    ComboMedia cm1;
    cm1.add(&r1);
    ComboMedia cm2;
    cm2.add(&c1);
    cm2.add(&t1);

    cm1.add(&cm2);

    DescriptionVisitor dv;
    cm1.accept(&dv);
//    cout<<dv.getDescription()<<endl;
    CHECK("combo(r(0 0 4 8) combo(c(-2 1 2) t(1 -1 4 -1 4 3) ))" == dv.getDescription());
}

TEST (buildShapeMedia, ShapeMediaBuilder) {
    ShapeMediaBuilder smb;
    Circle cir(0,0 ,5);
    smb.buildShapeMedia(&cir);

    Media* sm = smb.getMedia();
    DescriptionVisitor dv;
    sm->accept(&dv);

    CHECK("c(0 0 5) " == dv.getDescription());
}

TEST (buildComboMedia, ShapeMediaBuilder) {
    try{
        ShapeMediaBuilder smb;
        smb.buildComboMedia();

        FAIL("Should not be here!!!");
    }catch(string exc){
        CHECK("ShapeMediaBuilder CAN'T Build ComboMedia!!!" == exc);
    }
}

TEST (buildComboMedia, ComboMediaBuilder) {
    ComboMediaBuilder cmb;
    cmb.buildComboMedia();
    Circle cir(0,0 ,5);
    cmb.buildShapeMedia(&cir);

    Media* cmbMedia=cmb.getMedia();
    DescriptionVisitor dv;
    cmbMedia->accept(&dv);

    CHECK("combo(c(0 0 5) )" == dv.getDescription());
}

TEST (buildShapeMedia, ComboMediaBuilder) {
    try{
        ComboMediaBuilder cmb;
        Circle cir(0,0 ,5);
        cmb.buildShapeMedia(&cir);

        FAIL("Should not be here!!!");
    }catch(string exc){
        CHECK("Should Call buildComboMedia() first!!!" == exc);
    }
}

TEST (buildComboMedia2, ComboMediaBuilder) {
    /**combo(combo(combo(r(10 0 15 5) c(12 5 2) )r(0 0 25 20) )t(0 20 16 32 25 20) )*/
    stack<MediaBuilder*> sMb;
    sMb.push(new ComboMediaBuilder());
    sMb.top()->buildComboMedia();
    sMb.push(new ComboMediaBuilder());
    sMb.top()->buildComboMedia();
    sMb.push(new ComboMediaBuilder());
    sMb.top()->buildComboMedia();

    Rectangle rect1(10,0, 15,5);
    sMb.top()->buildShapeMedia(&rect1);
    Circle cir(12,5 ,2);
    sMb.top()->buildShapeMedia(&cir);
    ComboMedia* cm=(ComboMedia*) sMb.top()->getMedia();
    sMb.pop();
    ((ComboMediaBuilder*)sMb.top())->addMedia(cm);

    Rectangle rect2(0,0, 25,20);
    sMb.top()->buildShapeMedia(&rect2);
    cm=(ComboMedia*) sMb.top()->getMedia();
    sMb.pop();
    ((ComboMediaBuilder*)sMb.top())->addMedia(cm);

    Triangle tri(0,20, 16,32, 25,20);
    sMb.top()->buildShapeMedia(&tri);

    DescriptionVisitor dv;
    sMb.top()->getMedia()->accept(&dv);
    //cout<<dv.getDescription()<<endl;
    CHECK("combo(combo(combo(r(10 0 15 5) c(12 5 2) )r(0 0 25 20) )t(0 20 16 32 25 20) )" == dv.getDescription());
}

TEST (getText, TextMedia) {
    Text text(new Rectangle(0,0, 4,3), "HW4-3");
    TextMedia tm(&text);

    DescriptionVisitor dv;
    tm.accept(&dv);

    CHECK("text(r(0 0 4 3) content(HW4-3)) " == dv.getDescription());
}
#endif // UNITMEDIA_H_INCLUDED
