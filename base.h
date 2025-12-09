#pragma once

#ifndef __BASE_H
#define __BASE_H

#include <string>
#include <stdio.h>
#include <iostream>

using namespace std;

#define S8KB (1024 * 8)

typedef unsigned char  u8;
typedef unsigned short u16;
typedef char i8;
typedef short i16;

inline void Panic(const string& message)
{
    cout << "Panic: " << message << std::endl;
    exit(1);
}

#endif // __BASE_H
