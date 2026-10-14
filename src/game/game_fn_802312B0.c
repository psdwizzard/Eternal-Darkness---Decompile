/* fn_802312B0 (0x802312B0, 48 bytes) */

extern void* memset(void* dest, int value, unsigned long size);

void fn_802312B0(void* data) {
    if (data != 0) {
        memset(data, 0, 0x20);
    }
}
