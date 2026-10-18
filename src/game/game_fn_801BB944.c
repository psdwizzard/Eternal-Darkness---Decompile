typedef unsigned short u16;
typedef unsigned int u32;

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

int dataInsertLayer(u16 id, void* value, u16 parameter)
{
    unsigned char* base = lbl_8061C748;
    int count;
    int index;
    int cursor;
    unsigned char* selected;

    hwDisableIrq();
    count = dataLayerNum;
    index = 0;
    while (index < count && ((StreamResource12*)(base + 0x4E00))[index].id < id) {
        index++;
    }

    if (index >= count) {
        goto append;
    }

    selected = base + index * sizeof(StreamResource12);
    if (id == ((StreamResource12*)(selected + 0x4E00))->id) {
        goto existing;
    }
    if ((u32)count >= 0x100) {
        goto insert_full;
    }
    cursor = count - 1;
    for (; cursor >= index; cursor--) {
        ((StreamResource12*)(base + 0x4E00))[cursor + 1] =
            ((StreamResource12*)(base + 0x4E00))[cursor];
    }
    dataLayerNum++;
    goto write;

insert_full:
    hwEnableIrq();
    return 0;

existing:
    ((StreamResource12*)(selected + 0x4E00))->references++;
    hwEnableIrq();
    return 0;

append:
    if ((u32)count < 0x100) {
        dataLayerNum++;
        goto write;
    }
    hwEnableIrq();
    return 0;

write:
    ((StreamResource12*)(base + 0x4E00))[index].id = id;
    ((StreamResource12*)(base + 0x4E00))[index].value = value;
    ((StreamResource12*)(base + 0x4E00))[index].parameter = parameter;
    ((StreamResource12*)(base + 0x4E00))[index].references = 1;
    hwEnableIrq();
    return 1;
}
