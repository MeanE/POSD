#include "..\cppunitlite\TestHarness.h"
#include "UnitShapes.h"
using namespace std;

int main()
{
    TestResult tr;
    TestRegistry::runAllTests(tr);

    return 0;
}
