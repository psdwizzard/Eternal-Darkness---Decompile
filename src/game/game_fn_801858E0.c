typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Words3 {
    u32 x;
    u32 y;
    u32 z;
} Words3;

extern const Words3 lbl_8023B050;
extern const Words3 lbl_8023B05C;
extern const volatile u32 lbl_806509F4;
extern void fn_801859FC(u8*, u8);

void fn_801858E0(u8* self)
{
    u32 first_x = lbl_8023B050.x;
    u32 first_y = lbl_8023B050.y;
    u32 first_z = lbl_8023B050.z;
    u32 second_x = lbl_8023B05C.x;
    u32 second_y = lbl_8023B05C.y;
    u32 second_z = lbl_8023B05C.z;
    u32 value = lbl_806509F4;

    self[0] = 31;
    self[1] = 64;
    self[2] = 250;
    self[3] = 254;
    *(u16*)(self + 4) = 5;
    *(u16*)(self + 6) = 130;
    *(u16*)(self + 8) = 5;
    *(u16*)(self + 0x1C) = 100;
    *(u16*)(self + 0x1E) = 0x800;
    *(u16*)(self + 0x20) = 4;
    fn_801859FC(self, self[0]);
    self[0x14] = 20;
    self[0x15] = 3;
    self[0x18] = 20;
    self[0x19] = 31;
    *(u32*)(self + 0x78) = value;
    *(u32*)(self + 0x3C) = first_x;
    *(u32*)(self + 0x40) = first_y;
    *(u32*)(self + 0x44) = first_z;
    *(u32*)(self + 0x48) = first_x;
    *(u32*)(self + 0x4C) = first_y;
    *(u32*)(self + 0x50) = first_z;
    *(u32*)(self + 0x30) = second_x;
    *(u32*)(self + 0x34) = second_y;
    *(u32*)(self + 0x38) = second_z;
}
