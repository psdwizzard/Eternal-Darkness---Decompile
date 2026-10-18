typedef unsigned short u16;

typedef struct StreamResource8 {
    void* value;
    u16 id;
    u16 references;
} StreamResource8;

extern unsigned char lbl_8061C748[];
extern u16 dataCurveNum;
extern void hwDisableIrq(void);
extern void hwEnableIrq(void);

int dataRemoveCurve(u16 id)
{
    unsigned char* base = lbl_8061C748;
    int count;
    int index;
    int cursor;

    hwDisableIrq();
    count = dataCurveNum;
    index = 0;
    while (index < count && ((StreamResource8*)(base + 0x600))[index].id != id) {
        index++;
    }

    if (index == count) {
        goto not_removed;
    }

    if (--((StreamResource8*)(base + 0x600))[index].references != 0) {
        goto not_removed;
    }

    cursor = index + 1;
    for (; cursor < count; cursor++) {
        ((StreamResource8*)(base + 0x600))[cursor - 1] =
            ((StreamResource8*)(base + 0x600))[cursor];
    }
    dataCurveNum--;
    hwEnableIrq();
    return 1;

not_removed:
    hwEnableIrq();
    return 0;
}
