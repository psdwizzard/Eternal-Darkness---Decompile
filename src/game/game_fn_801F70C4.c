extern void* lbl_8064C4E4;

void fn_801F70C4(unsigned char* state, float value)
{
    if (lbl_8064C4E4 != 0) {
        *(float*)(state + 0x28) = value;
    }
}
