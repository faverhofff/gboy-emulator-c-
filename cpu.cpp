#include "base.h"
#include "mmu.h"
#include "cpu.h"
#include <iostream>

void CPU::Step()
{
	u8 opcode = mMmu->ReadU8(mRegPC++);

	switch(opcode)
	{
		case 0x31: // LD SP, nn
			mRegSP = mMmu->ReadU16(mRegSP);
			mRegPC += 2;
			cout << "LD SP, " << Int2Hex(mRegSP) << "\n";
			break;

		case 0xAF: // XOR A
			mRegA ^= mRegA;
			mFlagZ = (mRegA == 0);
			mFlagN = false;
			mFlagH = false;
			mFlagC = false;
			cout << "XOR A\n";
			break;

		default:
			throw std::runtime_error("opcode unknow " + Int2Hex(opcode));
	}
}