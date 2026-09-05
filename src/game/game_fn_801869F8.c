typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;

#pragma opt_common_subs off
void fn_801869F8(u8* self, int index, u16 limit)
{
    u8* selected;

    if ((s8)self[1] == 0) {
        return;
    }

    selected = self + index * 2;
    *(u16*)(selected + 0xE) += (s8)self[1];
    if ((s8)self[1] < 0) {
        if (*(u16*)(selected + 0xE) < limit) {
            *(u16*)(selected + 0xE) = limit;
        }
    } else if (*(u16*)(selected + 0xE) > limit) {
        *(u16*)(selected + 0xE) = limit;
    }
}
#pragma opt_common_subs reset
