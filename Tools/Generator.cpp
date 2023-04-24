#include "Generator.h"


Generator::Generator():rd(),gen(rd()), dist(INT32_MIN, INT32_MAX)
{
}

int Generator::getNumber() {
    return dist(gen);
}
int Generator::getNumber(int min, int max) {
    dist.param(uniform_int_distribution<>::param_type(min,max));
    int valReturn = dist(gen);
    dist.param(uniform_int_distribution<>::param_type(INT32_MIN,INT32_MAX));
    return valReturn;
}
