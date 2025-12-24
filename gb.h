#pragma once

#include <string>
#include "cpu.h"
#include "mmu.h"

#ifndef _GB_H
#define _GB_H

class GB
{
public:
    void PowerOn(const std::string& _bootableRom, const std::string& _cartridgePath);
    const MMU& GetMmu() const { return mMmu; }

private:
    CPU mCpu;
    MMU mMmu;
};

#endif // _GB_H