typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TextSlots {
    void* fonts[10];
    u32 indices[10];
    u8* strings[10];
} TextSlots;

extern TextSlots lbl_806333C8;
extern void* lbl_8064D568;
extern u32 lbl_8064D584;

int fn_801E5BD8(u8* string)
{
    u32 index = lbl_8064D584;
    TextSlots* slots = &lbl_806333C8;

    if (index < 10) {
        if (string != 0) {
            slots->strings[index] = string;
            slots->indices[index] = index;
            slots->fonts[index] = lbl_8064D568;
            if (index == 2) {
                u8* p = slots->strings[2];
                p[0x46] -= 5;
                p = slots->strings[2];
                p[0x48] -= 2;
                p = slots->strings[2];
                p[0x4A] -= 3;
                p = slots->strings[2];
                p[0x4D] -= 6;
                p = slots->strings[2];
                p[0x50] -= 6;
                p = slots->strings[2];
                p[0x51] -= 8;
                p = slots->strings[2];
                p[0x52] -= 6;
                p = slots->strings[2];
                p[0x55] -= 7;
                p = slots->strings[2];
                p[0x56] -= 5;
                p = slots->strings[2];
                p[0x57] -= 6;
                p = slots->strings[2];
                p[0x59] -= 7;
                p = slots->strings[2];
                p[0x5C] -= 4;
                p = slots->strings[2];
                p[0x5E] -= 8;
            }
        }
        lbl_8064D584++;
        return 1;
    }
    return 0;
}
