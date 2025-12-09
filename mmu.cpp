#include <memory.h>
#include <fstream> 
#include "base.h"
#include "mmu.h"

MMU::MMU()
{
    mRom = nullptr;
    memset(mRam, 0, S8KB);
    memset(mVRam, 0, S8KB);
    memset(mBootableRom, 0, 256);
}

bool MMU::LoadRoms(const string &_bootableRom, const string &_cartridge)
{
    ifstream bootable(_bootableRom, std::ios::binary);
    if (!bootable)
    {
        cout << "Failed to open bootable ROM: " << _bootableRom << std::endl;
        return false;
    }

    bootable.read((char*)mBootableRom, 256);

    bootable.close();

    return true;
}

u8* MMU::VirtualToPhysicalAddr(u16 _virtualAddress) 
{
    if (mBootRomEnabled && (_virtualAddress >= 0x000) && (_virtualAddress <= 0x00FF)) // Boot ROM area
    {
        return &mBootableRom[_virtualAddress];
    }

    if ((_virtualAddress > 0x000) && (_virtualAddress <= 0x3FFF)) // ROM area
    {
        return &mRom[_virtualAddress];
    }

    if ((_virtualAddress >= 0x8000) && (_virtualAddress <= 0x9FFF)) // VRAM area
    {
        return &mVRam[_virtualAddress - 0x8000];
    }

    if ((_virtualAddress >= 0xC000) && (_virtualAddress <= 0xDFFF)) // RAM area
    {
        return &mRam[_virtualAddress - 0xC000];
    } 

    throw runtime_error("Invalid memory access at address: " + Int2Hex(_virtualAddress));
}