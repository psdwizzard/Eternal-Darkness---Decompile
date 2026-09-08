typedef signed short s16;
typedef signed long s32;
typedef unsigned char u8;
typedef unsigned long u32;

extern s32 lbl_8064D768;

void fn_801F0B24(u8* context)
{
    s32 count = *(s32*)(context + 0x4C);
    void** lists = (void**)(context + 0x138);
    void* mode = *(void**)(context + 0x8138);
    u8* records = *(u8**)(context + 0x0C);
    u8* item = *(u8**)(context + 0x50);

    while (count-- > 0) {
        s32 index = *(s32*)(item + 0x0C);
        u8* record = records + index * 0x20;
        s32 list_index = index;
        s32 value = *(s16*)(record + 0x00);

        if (value != -1) {
            list_index = value;
        }
        if (*(s16*)(record + 0x0A) != -1 || *(u8*)(record + 0x1F) != 0xFF) {
            list_index += 0x1000;
        }
        if (*(s16*)(record + 0x0E) != -1) {
            list_index += 0x800;
            lbl_8064D768 = 1;
        }

        value = *(u32*)(record + 0x18) & 0x1FFFFFFF;
        if (value != 0 && mode != 0) {
            *(void**)(item + 0x10) = lists[list_index];
            lists[list_index] = item;
        } else if (mode == 0 && value == 0) {
            *(void**)(item + 0x10) = lists[list_index];
            lists[list_index] = item;
        }
        item += 0x14;
    }
}
