#include "mmu.h"
#include "cpu.h"
#include "base.h"
#include "gb.h"

void GB::PowerOn(const string &_bootableRom, const string& _cartridgePath)
{
    try
    {
        mMmu.LoadRoms(_bootableRom, _cartridgePath);

        while (true)
        {
            mCpu.Step();
        }
    }
    catch (runtime_error &e)
    {
        cout << e.what() << '\n' << endl;
    }
}
