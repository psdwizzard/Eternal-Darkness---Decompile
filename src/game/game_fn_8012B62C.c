typedef unsigned char u8;
typedef unsigned short u16;

void fn_8012B62C(u8* owner, int slot, int id)
{
    u8* header = *(u8**)(owner + 0x284);
    u8* entry = *(u8**)(owner + 0x28C);
    u8** output = *(u8***)(owner + 0x288);
    int count;

    if (header == 0) {
        return;
    }
    if (entry == 0) {
        return;
    }
    if (output == 0) {
        return;
    }
    if (slot < *(u16*)(owner + 0x2D6)) {
        count = *(u16*)(header + 0x14);
        while (count-- > 0) {
            if (*(int*)entry == id) {
                output[slot] = entry;
                return;
            }
            entry += 0x10;
        }
    }
}
