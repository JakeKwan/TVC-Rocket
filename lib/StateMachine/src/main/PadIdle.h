#include "StateCommon.h"

class PadIdle {
    public:
    PadIdle();
    static void run(); 
    static void onEntry(State prevState); 
}; 