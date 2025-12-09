#pragma once

#ifndef _MMU_H
#define _MMU_H

#include "base.h"

class MMU
{
public:
    MMU();

    inline void WriteU8(u16 _address, u8 _value)
    {
        u8 *memory = nullptr;
        u16 physicalAddress = 0;

        VirtualToPhysicalAddr(_address, memory, physicalAddress);
        memory[physicalAddress] = _value;
    }

    inline u8 ReadU8(u16 _address) 
    {
        u8 *memory = nullptr;
        u16 physicalAddress = 0;

        VirtualToPhysicalAddr(_address, memory, physicalAddress);
        return memory[physicalAddress];
    }

    void WriteU16(u16 _address, u16 _value)
    {
        u8 *memory = nullptr;
        u16 physicalAddress = 0;

        VirtualToPhysicalAddr(_address, memory, physicalAddress);
        memory[physicalAddress] = _value & 0x00FF;
        memory[physicalAddress + 1] = (_value & 8) >> 0xFF00;

        //WriteU8(_address, static_cast<u8>(_value & 0x00FF));
        //WriteU8(_address + 1, static_cast<u8>((_value & 0xFF00) >> 8));
    }

    inline u16 ReadU16(u16 _address)
    {
        u8 *memory = nullptr;
        u16 physicalAddress = 0;

        VirtualToPhysicalAddr(_address, memory, physicalAddress);
        return (memory[physicalAddress + 1] << 8) | memory[physicalAddress];
        // return static_cast<u16>(memory[physicalAddress]) | (static_cast<u16>(memory[physicalAddress + 1]) << 8);
    }

    bool LoadRoms(const string& _bootableRom, const string& filepath);

private:
    void VirtualToPhysicalAddr(u16 _virtualAddress, u8*& _memory, u16& _physicalAddress);

    u8 mRam[S8KB]; // 8KB RAM
    u8 mVRam[S8KB]; // 8KB VRAM
    u8* mRom;
    u8 mBootableRom[256]; // 256B Bootable ROM  
    bool mBootRomEnabled = true;
};

#endif // _MMU_H