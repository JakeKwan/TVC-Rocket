#include "StateCommon.h"

class PadArmed
{
    PadArmed();
    public:
    static void onEntry(State prevState);
    static void run();
};