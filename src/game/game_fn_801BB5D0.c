typedef unsigned short u16;
typedef unsigned int u32;

typedef struct StreamResource {
    void* value;
    u16 id;
    u16 references;
} StreamResource;

extern unsigned char lbl_8061C748[];
extern u16 dataKeymapNum;
extern void hwDisableIrq(void);
extern void hwEnableIrq(void);

int dataInsertKeymap(u16 id, void* value)
{
    unsigned char* base = lbl_8061C748;
    int count;
    int index;
    int cursor;
    unsigned char* selected;

    hwDisableIrq();
    count = dataKeymapNum;
    index = 0;
    while (index < count && ((StreamResource*)(base + 0x4600))[index].id < id) {
        index++;
    }

    if (index >= count) {
        goto append;
    }

        selected = base + index * sizeof(StreamResource);
    if (id == ((StreamResource*)(selected + 0x4600))->id) {
        goto existing;
    }
        if ((u32)count >= 0x100) {
        goto insert_full;
        }
        cursor = count - 1;
        for (; cursor >= index; cursor--) {
            ((StreamResource*)(base + 0x4600))[cursor + 1] =
                ((StreamResource*)(base + 0x4600))[cursor];
        }
        dataKeymapNum++;
    goto write;

insert_full:
    hwEnableIrq();
    return 0;

existing:
    ((StreamResource*)(selected + 0x4600))->references++;
    hwEnableIrq();
    return 0;

append:
    if ((u32)count < 0x100) {
        dataKeymapNum++;
        goto write;
    }
    hwEnableIrq();
    return 0;

write:
    ((StreamResource*)(base + 0x4600))[index].id = id;
    ((StreamResource*)(base + 0x4600))[index].value = value;
    ((StreamResource*)(base + 0x4600))[index].references = 1;
    hwEnableIrq();
    return 1;
}
