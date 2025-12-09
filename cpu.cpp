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
			cout << mRegSP << "\n";
			mRegSP = mMmu->ReadU16(mRegSP);
			mRegPC += 2;
			cout << "LD SP, " << mRegSP << "\n";
			break;

		default:
			throw std::runtime_error("opcode unknow " + opcode);
	}
}