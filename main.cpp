#include <stdio.h>
#include "gb.h"

int main(int argn, char *argv[]) 
{
    GB gb;

    gb.PowerOn(argv[1], argv[2]);

    return 0;
}