int f2(int x) {return 0;} // ODR violation in c.h
#include "c.h"

S g() {return {};}