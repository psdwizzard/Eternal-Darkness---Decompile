typedef unsigned int u32;

extern void* dspHrtfHistoryBuffer;
extern void* memset(void*, int, u32);
extern void DCFlushRangeNoSync(void*, u32);

void salInitHRTFBuffer(void)
{
    memset(dspHrtfHistoryBuffer, 0, 0x100);
    DCFlushRangeNoSync(dspHrtfHistoryBuffer, 0x100);
}
