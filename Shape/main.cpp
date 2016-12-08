#include "..\cppunitlite\TestHarness.h"
#include "UnitShapes.h"
#include "UnitMedia.h"
#include "TextUI.h"
using namespace std;

int main()
{
    TestResult tr;
    TestRegistry::runAllTests(tr);
    cout<<endl;

    TextUI textUI;
    textUI.run();
    return 0;
}
