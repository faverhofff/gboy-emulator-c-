#include "mmu.h"
#include "cpu.h"
#include "base.h"
#include "gb.h"

void GB::PowerOn(const string &_bootableRom, const string& _cartridgePath)
{
    try
    {
        mMmu.LoadRoms(_bootableRom, _cartridgePath);
        mCpu.SetMmu(&mMmu);

        while (true)
        {
            mCpu.Step();
        }
    }
    catch (std::runtime_error &e)
    {
        cout << e.what() << '\n' << endl;
    }
}
