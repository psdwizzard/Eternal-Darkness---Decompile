typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#pragma use_lmw_stmw on

typedef struct BufferGroup {
    void* first;
    void* second;
    void* third;
    void* fourth;
    u16* dimensions;
} BufferGroup;

extern u32 fn_8017FF98(void);
extern u32 fn_8017FFA0(void);
extern u32 fn_8017FFA8(void);
extern u32 fn_8017FFB0(void);
extern u32 fn_8017FFB8(void);
extern void* fn_801FEA8C(u32, u32, const char*, u32);
extern void* fn_8017CCD8(void*, u32, u32);
extern char lbl_802510F8[];

void fn_801807B0(BufferGroup* group, u32 count, u32 width, u32 scale)
{
    u32 first_stride;
    u32 second_stride;
    u32 third_stride;
    u32 fourth_stride;
    u32 first_size;
    u32 second_size;
    u32 third_size;
    u32 fourth_size;
    void* first;
    void* second;
    void* third;
    void* fourth;

    fn_8017FFA8();
    first_stride = fn_8017FFA0();
    second_stride = fn_8017FFB8();
    third_stride = fn_8017FF98();
    fourth_stride = fn_8017FFB0();
    {
        u16 doubled_width = (u16)((u16)width * (u16)((u8)scale << 1));
        first_size = first_stride * (u16)width;
        first = fn_801FEA8C((u16)count * first_size, 1, lbl_802510F8, 1654);
        second_size = second_stride * doubled_width;
        second = fn_801FEA8C((u16)count * second_size, 1, lbl_802510F8, 1657);
        third_size = third_stride * doubled_width;
        third = fn_801FEA8C((u16)count * third_size, 1, lbl_802510F8, 1660);
        fourth_size = fourth_stride * doubled_width;
        fourth = fn_801FEA8C((u16)count * fourth_size, 1, lbl_802510F8, 1663);
        group->first = fn_8017CCD8(first, first_size, count);
        group->second = fn_8017CCD8(second, second_size, count);
        group->third = fn_8017CCD8(third, third_size, count);
        group->fourth = fn_8017CCD8(fourth, fourth_size, count);
        {
            u16 half_width = doubled_width >> 1;
            group->dimensions[3] = 864;
            group->dimensions[4] = 1600;
            group->dimensions[0] = width;
            group->dimensions[1] = doubled_width >> 1;
            group->dimensions[2] = count;
            group->dimensions[5] = second_stride * half_width;
            group->dimensions[6] = third_stride * half_width;
            group->dimensions[7] = fourth_stride * half_width;
        }
    }
}
