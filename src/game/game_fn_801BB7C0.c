typedef unsigned short u16;

typedef struct StreamResource {
    void* value;
    u16 id;
    u16 references;
} StreamResource;

extern unsigned char lbl_8061C748[];
extern u16 dataKeymapNum;
extern void hwDisableIrq(void);
extern void hwEnableIrq(void);

int dataRemoveKeymap(u16 id)
{
    unsigned char* base = lbl_8061C748;
    int count;
    int index;
    int cursor;

    hwDisableIrq();
    count = dataKeymapNum;
    index = 0;
    while (index < count && ((StreamResource*)(base + 0x4600))[index].id != id) {
        index++;
    }

    if (index == count) {
        goto not_removed;
    }

    if (--((StreamResource*)(base + 0x4600))[index].references != 0) {
        goto not_removed;
    }

    cursor = index + 1;
    for (; cursor < count; cursor++) {
        ((StreamResource*)(base + 0x4600))[cursor - 1] =
            ((StreamResource*)(base + 0x4600))[cursor];
    }
    dataKeymapNum--;
    hwEnableIrq();
    return 1;

not_removed:
    hwEnableIrq();
    return 0;
}
