typedef unsigned int u32;

extern void inpFXCopyCtrl();

void synthFXCloneMidiSetup(u32 arg0, u32 arg1)
{
    inpFXCopyCtrl(7, arg0, arg1);
    inpFXCopyCtrl(10, arg0, arg1);
    inpFXCopyCtrl(0x5B, arg0, arg1);
    inpFXCopyCtrl(0x80, arg0, arg1);
    inpFXCopyCtrl(0x84, arg0, arg1);
}
