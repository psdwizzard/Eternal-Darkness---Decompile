typedef unsigned char u8;
typedef unsigned short u16;

extern void* fn_8015C28C(int);

int fn_801FB118(void* record, int alternate)
{
    u8* state = (u8*)fn_8015C28C(2);
    u8* records;
    u16 count;
    int index;

    if (state != 0 && (signed char)state[0x8142] != 0 &&
        (signed char)state[0x8143] != 0) {
        if (alternate) {
            records = *(u8**)(state + 0xAC);
        } else {
            records = *(u8**)(state + 0xA4);
        }
        if (alternate) {
            count = *(u16*)(state + 0xA8);
        } else {
            count = *(u16*)(state + 0xA2);
        }
        for (index = 0; index < count; index++) {
            if (records == record) {
                return index;
            }
            records += 120;
        }
    }
    return -1;
}
