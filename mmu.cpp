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
    std::ifstream bootable(_bootableRom, std::ios::binary);
    if (!bootable)
    {
        std::cout << "Failed to open bootable ROM: " << _bootableRom << std::endl;
        return false;
    }

    bootable.read((char*)mBootableRom, 256);

    bootable.close();

    return true;
}

void MMU::VirtualToPhysicalAddr(u16 _virtualAddress, u8*& _memory, u16& _physicalAddress) 
{
    if (mBootRomEnabled && (_virtualAddress >= 0x0000) && (_virtualAddress <= 0x0100)) // Boot ROM area
    {
        _memory = &mBootableRom[0];
        _physicalAddress = _virtualAddress;
        return;
    }

    if ((_virtualAddress > 0x000) && (_virtualAddress <= 0x3FFF)) // ROM area
    {
        _memory = mRom;
        _physicalAddress = _virtualAddress;
        return;
    }

    if ((_virtualAddress >= 0x8000) && (_virtualAddress <= 0x9FFF)) // VRAM area
    {
        _memory = &mVRam[0];
        _physicalAddress = _virtualAddress - 0x8000;
        return;
    }

    if ((_virtualAddress >= 0xC000) && (_virtualAddress <= 0xDFFF)) // RAM area
    {
        _memory = &mRam[0];
        _physicalAddress = _virtualAddress - 0xC000;
        return;
    } 

    throw std::runtime_error("Invalid memory access at address: " + _virtualAddress);
}