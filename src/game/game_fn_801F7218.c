void fn_801F7218(unsigned char* state, float value)
{
    float current = *(float*)(state + 0x34);
    *(float*)(state + 0x34) = current - (current - value) / *(float*)(state + 0x30);
}
