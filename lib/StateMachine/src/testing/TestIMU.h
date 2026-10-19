#include "main/StateCommon.h"

class TestIMU
{
public:
    TestIMU();
    static void onEntry(State prevState);
    static void run();
};
