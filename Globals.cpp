
#include "Globals.h"


bool running_in_matlab = false;

static bool (*pShouldAbortHook)(void) = 0;


