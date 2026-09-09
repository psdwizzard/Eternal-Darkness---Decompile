extern void* memset(void*, int, unsigned long);
extern void* lbl_8064C4E4;
extern float lbl_80651458;
extern float lbl_8065145C;
extern float lbl_80651460;
extern float lbl_80651464;
extern float lbl_80651468;

void fn_801F7034(unsigned char* state, int clear)
{
    if (clear != 0) {
        memset(state, 0, 0x88);
        *(void**)(state + 0x68) = lbl_8064C4E4;
    }

    *(unsigned int*)(state + 0x24) = 0;
    *(float*)(state + 0x28) = lbl_80651458;
    *(float*)(state + 0x2C) = lbl_8065145C;
    *(float*)(state + 0x30) = lbl_80651460;
    *(unsigned int*)(state + 0x3C) = 0;
    *(float*)(state + 0x38) = lbl_80651464;
    *(float*)(state + 0x34) = lbl_80651468;
    *(unsigned int*)(state + 0x44) = 0;
}
