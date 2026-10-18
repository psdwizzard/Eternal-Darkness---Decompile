extern void OSSendMessage(void*, int, int);

void fn_8015CDC0(int message, unsigned char* state)
{
    OSSendMessage(*(void**)(state + 0x2064), message, 1);
}
