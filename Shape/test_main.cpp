#include "..\cppunitlite\TestHarness.h"
#include "UnitShapes.h"
#include "UnitMedia.h"
#include "UnitCommand.h"
using namespace std;

int main()
{
    TestResult tr;
    TestRegistry::runAllTests(tr);
}
