#include <stdio.h>
#include "meliorate/meliorate.h"


int main()
{
    meliorate_stop_on_error = false;
    return meliorate_run<std::exception>();
}