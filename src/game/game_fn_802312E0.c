/* Clear the Vorbis floor type 0 setup, if present. */
extern void *memset(void *data, int value, unsigned long size);

void fn_802312E0(void *info) {
    if (info != 0) {
        memset(info, 0, 0x60);
    }
}
