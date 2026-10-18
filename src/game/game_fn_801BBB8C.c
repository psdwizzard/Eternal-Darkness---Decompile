typedef unsigned short u16;

typedef struct StreamResource12 {
    void* value;
    u16 id;
    u16 parameter;
    u16 references;
    u16 padding;
} StreamResource12;

extern unsigned char lbl_8061C748[];
extern u16 dataLayerNum;
extern void hwDisableIrq(void);
extern void hwEnableIrq(void);

int dataRemoveLayer(u16 id)
{
    unsigned char* base = lbl_8061C748;
    int count;
    int index;
    int cursor;

    hwDisableIrq();
    count = dataLayerNum;
    index = 0;
    while (index < count && ((StreamResource12*)(base + 0x4E00))[index].id != id) {
        index++;
    }

    if (index == count) {
        goto not_removed;
    }

    if (--((StreamResource12*)(base + 0x4E00))[index].references != 0) {
        goto not_removed;
    }

    cursor = index + 1;
    for (; cursor < count; cursor++) {
        ((StreamResource12*)(base + 0x4E00))[cursor - 1] =
            ((StreamResource12*)(base + 0x4E00))[cursor];
    }
    dataLayerNum--;
    hwEnableIrq();
    return 1;

not_removed:
    hwEnableIrq();
    return 0;
}
