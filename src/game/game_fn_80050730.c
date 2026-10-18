typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#pragma use_lmw_stmw on

extern int fn_801A9EF4(int low, int high);
extern unsigned int rand(void);
#define rand() ((int)rand())
extern u32 lbl_8064E4B4;
extern u16 lbl_8064E4B8;

u16 fn_80050730(int type, int mode, u8* out_level, u8* out_flags,
                u16* out_time, u32* out_value)
{
    u16 result = 0xFFFF;
    u16 time = 0;
    u8 level = 0;
    u8 flags = 0;

    switch (type) {
    case 85:
        fn_801A9EF4(0, 1);
        result = 728;
        level = 100;
        flags = 2;
        time = 600;
        break;
    case 40:
        result = (u16)fn_801A9EF4(46, 50);
        level = 30;
        flags = 2;
        time = 600;
        break;
    case 47:
        result = (u16)fn_801A9EF4(176, 180);
        level = (u8)((rand() & 31) + 50);
        flags = 2;
        time = 300;
        break;
    case 50:
        result = (u16)fn_801A9EF4(196, 199);
        level = (u8)((rand() & 31) + 40);
        flags = 2;
        time = 600;
        break;
    case 84:
    {
        u16 values[3];
        *(u32*)values = lbl_8064E4B4;
        values[2] = lbl_8064E4B8;
        result = values[fn_801A9EF4(0, 2)];
        level = (u8)((rand() & 31) + 40);
        flags = 2;
        time = 600;
        break;
    }
    case 58:
        result = 274;
        level = (u8)((rand() & 31) + 40);
        flags = 2;
        time = 600;
        break;
    case 83:
        result = (u16)fn_801A9EF4(570, 572);
        level = (u8)((rand() & 15) + 30);
        flags = 2;
        time = 600;
        break;
    case 65:
        if (mode == 0) {
            result = (u16)fn_801A9EF4(316, 320);
            level = 50;
            flags = 2;
            time = 1500;
        } else if (mode == 1) {
            result = 321;
            level = 70;
            flags = 2;
            time = 1500;
        }
        break;
    case 80:
        result = 56;
        level = 40;
        flags = 2;
        time = 600;
        break;
    }

    if (out_level != 0) {
        *out_level = level;
    }
    if (out_flags != 0) {
        *out_flags = flags;
    }
    if (out_time != 0) {
        *out_time = time;
    }
    if (out_value != 0) {
        *out_value = 0;
    }
    return result;
}
