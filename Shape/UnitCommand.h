#ifndef UNITCOMMAND_H_INCLUDED
#define UNITCOMMAND_H_INCLUDED

#include "..\cppunitlite\TestHarness.h"
#include "Shapes.h"
#include "Medias.h"
#include "Visitors.h"
#include "Builders.h"
#include "Commands.h"
#include <iostream>
using namespace std;

const double EPSLION_IN_UNITCOMMAND=0.000001;

TEST (Test, Test) {
    FAIL("test");
}

#endif // UNITCOMMAND_H_INCLUDED
