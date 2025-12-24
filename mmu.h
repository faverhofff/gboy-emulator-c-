#pragma once

#ifndef _MMU_H
#define _MMU_H

#include "base.h"

class MMU
{
public:
    MMU();
    ~MMU();

    static const int RamSize = 1024 * 8;
    static const int VRamSize = 1024 * 8;
    static const int BootRomSize = 256;

    inline void WriteU8(u16 _address, u8 _value)
    {
        *VirtualToPhysicalAddr(_address) = _value;
    }

    inline u8 ReadU8(u16 _address) 
    {
        return *VirtualToPhysicalAddr(_address);
    }

    inline void WriteU16(u16 _address, u16 _value)
    {
        (*(u16*)VirtualToPhysicalAddr(_address)) = _value;
    }

    inline u16 ReadU16(u16 _address)
    {
        return *(u16*)VirtualToPhysicalAddr(_address);
    }

    const u8* GetBootableRom() const { return mBootableRom; }
    const u8* GetRom() const { return mRom; }

    bool LoadRoms(const string& _bootableRom, const string& filepath);

    int GetRomSize() const { return mRomSize; }

private:
    u8* VirtualToPhysicalAddr(u16 _virtualAddress);

    u8 mRam[RamSize]; // 8KB RAM
    u8 mVRam[VRamSize]; // 8KB VRAM
    u8* mRom{ nullptr };
    u8 mBootableRom[BootRomSize]; // 256B Bootable ROM  
    int mRomSize{ 0 };
    bool mBootRomEnabled = true;
};

#endif // _MMU_H