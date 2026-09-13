typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Owner {
    unsigned char data[1];
} Owner;

typedef struct SlotView {
    u8 pad_0[0x40];
    u32 first[4];
    u32 second[4];
    u16 third[4];
    u8 count;
} SlotView;

extern void *fn_8006ED3C();

void fn_8006DEF8(Owner *owner, u32 value, u32 first, u32 second, u16 third)
{
    u32 index;
    u8 *base = owner->data;
    u32 first_value = first;
    u8 slot;
    u8 *entry;
    u32 offset;

    fn_8006ED3C(owner, value, &index);
    entry = base + index * 0x2C;
    slot = (u8)(((SlotView *)entry)->count + 1) < 4 ? ((SlotView *)entry)->count + 1 : 0;
    offset = slot * 4;
    entry = base + index * 0x2C;
    entry += offset;
    *(u32 *)(entry + 0x40) = first_value;
    entry = base + index * 0x2C;
    entry += offset;
    *(u32 *)(entry + 0x50) = second;
    entry = base + index * 0x2C;
    entry += slot * 2;
    *(u16 *)(entry + 0x60) = third;
}
