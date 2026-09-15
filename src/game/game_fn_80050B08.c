typedef signed char s8;
typedef unsigned char u8;
typedef signed int s32;
typedef unsigned int u32;
typedef unsigned short u16;

#define NULL ((void *)0)
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

extern u16 fn_80049818(s32, u8 *);
extern u32 fn_80050A48(void);
extern u16 fn_80050A7C(s32, u8 *);
extern void fn_800EB458(const char *, ...);
extern int fn_8011EB04(void *);
#define fn_8011EB04(a) fn_8011EB04((void *)(a))
extern int fn_801A9EF4(int, int);
extern u16 fn_801A9F44(s32, s32 *);
extern u8 lbl_80238E60[];
extern const char lbl_8024104C[];
extern u8 lbl_803003C8[];

u16 fn_80050B08(s32 arg0, s32 arg1, s32 arg2, u8 *arg3, s8 *arg4, u16 *arg5, s32 *arg6) {
    s32 sp30[3];
    s32 sp24[3];
    s32 sp18[3];
    s32 spC[3];
    u8 sp8;
    s32 var_r28;
    s32 var_r29;
    s8 var_r31;
    u16 var_r21;
    u16 var_r22;
    u16 var_r3;
    u16 var_r3_2;
    u8 *var_r23 = lbl_80238E60;

    var_r29 = arg0;
    var_r22 = 0xFFFF;
    var_r21 = 0;
    var_r31 = 0;
    var_r28 = 0;
    sp8 = 0;
    if (arg1 != 0) {
        var_r29 = fn_8011EB04(arg1);
    }
    switch (var_r29) {                              /* switch 1; irregular */
    case 1:
    case 91:
    case 98:
    case 110:
    case 111:
    case 117:
    case 121:
    case 122:
    case 228:
    case 230:
    case 231:
        var_r28 = 2;
        switch (arg2) {                             /* switch 2; irregular */
        case 0x47:                                  /* switch 2 */
            var_r22 = 0x1CF;
            sp8 = 0x50;
            var_r31 = 2;
            var_r21 = 0x3E8;
            break;
        case 0x41:                                  /* switch 2 */
            var_r22 = fn_801A9EF4(0x33, 0x37);
            sp8 = 0x50;
            var_r31 = 2;
            var_r21 = 0x3E8;
            break;
        case 0x1C:                                  /* switch 2 */
            sp8 = 0x64;
            var_r31 = 2;
            var_r22 = fn_80049818(arg1, arg3);
            var_r21 = 0x5DC;
            break;
        case 0x1B:                                  /* switch 2 */
            sp30[0] = M2C_FIELD(var_r23, s32 *, 0xB0);
            sp30[1] = M2C_FIELD(var_r23, s32 *, 0xB4);
            sp30[2] = M2C_FIELD(var_r23, s32 *, 0xB8);
            var_r22 = fn_801A9F44(3, sp30);
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x3E8;
            break;
        case 0x2D:                                  /* switch 2 */
            var_r22 = 0xBA;
            sp8 = 0x5A;
            var_r31 = 2;
            var_r21 = 0x3E8;
            break;
        case 0x1D:                                  /* switch 2 */
            var_r22 = fn_801A9EF4(0x2E, 0x32);
            sp8 = 0x3C;
            var_r31 = 2;
            var_r21 = 0x7D0;
            break;
        case 0x4D:                                  /* switch 2 */
            var_r31 = 2;
            var_r22 = fn_80050A7C(arg1, &sp8);
            var_r21 = 0x3E8;
            break;
        case 0x56:                                  /* switch 2 */
            var_r22 = 0x287;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x3E8;
            break;
        }
        break;
    case 95:                                        /* switch 1 */
        var_r28 = 4;
        switch (arg2) {                             /* switch 3 */
        case 0x24:                                  /* switch 3 */
            var_r22 = 0x172;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x1388;
            break;
        case 0x25:                                  /* switch 3 */
            var_r22 = 0x14E;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x26:                                  /* switch 3 */
            var_r22 = 0x2CE;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x41:                                  /* switch 3 */
            var_r3 = 0x5E;
            if (fn_80050A48() == 0x40U) {
                var_r3 = 0x202;
            }
            var_r22 = var_r3;
            sp8 = 0x78;
            var_r31 = 2;
            var_r21 = 0x1388;
            break;
        case 0x2C:                                  /* switch 3 */
            var_r22 = 0x60;
            sp8 = 0x4B;
            var_r31 = 2;
            var_r21 = 0x1388;
            break;
        case 0x47:                                  /* switch 3 */
            var_r22 = 0x1CE;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x3E8;
            break;
        case 0x44:                                  /* switch 3 */
            var_r22 = fn_801A9EF4(0x1FE, 0x200);
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x258;
            break;
        }
        break;
    case 120:                                       /* switch 1 */
    case 48:                                        /* switch 1 */
        var_r28 = 4;
        switch (arg2) {                             /* switch 4 */
        case 0x24:                                  /* switch 4 */
            var_r22 = 0x5F;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x1388;
            break;
        case 0x25:                                  /* switch 4 */
            var_r22 = 0x14E;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x41:                                  /* switch 4 */
            var_r22 = 0x5E;
            sp8 = 0x78;
            var_r31 = 2;
            var_r21 = 0x1388;
            break;
        case 0x2C:                                  /* switch 4 */
            var_r22 = 0x60;
            sp8 = 0x4B;
            var_r31 = 2;
            var_r21 = 0x1388;
            break;
        case 0x47:                                  /* switch 4 */
            var_r22 = 0x1CE;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x3E8;
            break;
        case 0x44:                                  /* switch 4 */
            var_r22 = fn_801A9EF4(0x1FE, 0x200);
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x258;
            break;
        }
        break;
    case 61:                                        /* switch 1 */
        var_r28 = 2;
        switch (arg2) {                             /* switch 5; irregular */
        case 0x41:                                  /* switch 5 */
            var_r22 = 0xD2;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x3E8;
            break;
        case 0x4D:                                  /* switch 5 */
            var_r31 = 2;
            var_r22 = fn_80050A7C(arg1, &sp8);
            var_r21 = 0x3E8;
            break;
        case 0x1B:                                  /* switch 5 */
            var_r22 = fn_801A9EF4(0x1D7, 0x1DA);
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x7D0;
            break;
        case 0x2D:                                  /* switch 5 */
            var_r22 = 0xBA;
            sp8 = 0x5A;
            var_r31 = 2;
            var_r21 = 0x3E8;
            break;
        case 0x47:                                  /* switch 5 */
            var_r22 = 0x1CF;
            sp8 = 0x50;
            var_r31 = 2;
            var_r21 = 0x3E8;
            break;
        case 0x1C:                                  /* switch 5 */
            sp8 = 0x64;
            var_r31 = 2;
            var_r22 = fn_80049818(arg1, arg3);
            var_r21 = 0x5DC;
            break;
        }
        break;
    case 210:                                       /* switch 1 */
    case 62:                                        /* switch 1 */
        var_r28 = 2;
        switch (arg2) {                             /* switch 6; irregular */
        case 0x41:                                  /* switch 6 */
            var_r22 = 0x2A0;
            sp8 = 0x46;
            var_r31 = 2;
            var_r21 = 0x3E8;
            break;
        case 0x4D:                                  /* switch 6 */
            var_r31 = 2;
            var_r22 = fn_80050A7C(arg1, &sp8);
            var_r21 = 0x3E8;
            break;
        case 0x47:                                  /* switch 6 */
            var_r22 = 0x1CF;
            sp8 = 0x50;
            var_r31 = 2;
            var_r21 = 0x3E8;
            break;
        case 0x1B:                                  /* switch 6 */
            var_r22 = fn_801A9EF4(0x1D7, 0x1DA);
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x7D0;
            break;
        case 0x2D:                                  /* switch 6 */
            var_r22 = 0xBA;
            sp8 = 0x5A;
            var_r31 = 2;
            var_r21 = 0x3E8;
            break;
        case 0x1C:                                  /* switch 6 */
            sp8 = 0x64;
            var_r31 = 2;
            var_r22 = fn_80049818(arg1, arg3);
            var_r21 = 0x5DC;
            break;
        }
        break;
    case 99:                                        /* switch 1 */
        var_r28 = 2;
        switch (arg2) {                             /* switch 7; irregular */
        case 0x47:                                  /* switch 7 */
            break;
        case 0x41:                                  /* switch 7 */
            var_r22 = 0x19E;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0xBB8;
            break;
        case 0x1C:                                  /* switch 7 */
            var_r22 = fn_801A9EF4(0x19F, 0x1A0);
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0xBB8;
            break;
        case 0x4D:                                  /* switch 7 */
            var_r31 = 2;
            var_r22 = fn_80050A7C(arg1, &sp8);
            var_r21 = 0x3E8;
            break;
        }
        break;
    case 233:                                       /* switch 1 */
        var_r28 = 4;
        switch (arg2) {                             /* switch 8; irregular */
        case 0x24:                                  /* switch 8 */
        case 0x25:                                  /* switch 8 */
        case 0x26:                                  /* switch 8 */
            var_r22 = 0x10B;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x41:                                  /* switch 8 */
            var_r22 = 0x10A;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x1388;
            break;
        case 0x2C:                                  /* switch 8 */
            var_r22 = 0x18E;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x1388;
            break;
        case 0x1C:                                  /* switch 8 */
            sp8 = 0x64;
            var_r31 = 2;
            var_r22 = fn_80049818(arg1, arg3);
            var_r21 = 0x5DC;
            break;
        case 0x39:                                  /* switch 8 */
            var_r22 = 0x2A4;
            sp8 = 0x3C;
            var_r31 = 2;
            var_r21 = 0x1388;
            break;
        }
        break;
    case 256:                                       /* switch 1 */
    case 113:                                       /* switch 1 */
        var_r28 = 4;
        switch (arg2) {                             /* switch 9; irregular */
        case 0x1C:                                  /* switch 9 */
            var_r22 = 0x141;
            sp8 = 0x46;
            var_r31 = 2;
            var_r21 = 0x5DC;
            break;
        case 0x39:                                  /* switch 9 */
            var_r31 = 8;
            break;
        case 0x41:                                  /* switch 9 */
            var_r22 = 0x14B;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x1388;
            break;
        case 0x24:                                  /* switch 9 */
        case 0x25:                                  /* switch 9 */
        case 0x26:                                  /* switch 9 */
            var_r22 = 0x182;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x2C:                                  /* switch 9 */
            var_r22 = 0x183;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x1388;
            break;
        case 0x47:                                  /* switch 9 */
            var_r22 = 0x1D0;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x3E8;
            break;
        }
        break;
    case 116:                                       /* switch 1 */
        var_r28 = 4;
        switch (arg2) {                             /* switch 10 */
        case 0x41:                                  /* switch 10 */
            var_r22 = 0x174;
            sp8 = 0x78;
            var_r31 = 2;
            var_r21 = 0x1388;
            break;
        case 0x24:                                  /* switch 10 */
            var_r22 = 0x170;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x25:                                  /* switch 10 */
            var_r22 = 0x14D;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x49:                                  /* switch 10 */
            var_r22 = 0x171;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x26:                                  /* switch 10 */
            var_r22 = 0x171;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x47:                                  /* switch 10 */
            var_r22 = 0x1CD;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x3E8;
            break;
        case 0x2C:                                  /* switch 10 */
            var_r22 = 0x17F;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x1388;
            break;
        case 0x44:                                  /* switch 10 */
            var_r22 = fn_801A9EF4(0x148, 0x14A);
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x258;
            break;
        }
        break;
    case 118:                                       /* switch 1 */
        var_r28 = 4;
        switch (arg2) {                             /* switch 11 */
        case 0x41:                                  /* switch 11 */
            var_r22 = 0x180;
            sp8 = 0x78;
            var_r31 = 2;
            var_r21 = 0x1388;
            break;
        case 0x24:                                  /* switch 11 */
            var_r22 = 0x17C;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x25:                                  /* switch 11 */
            var_r22 = 0x17D;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x26:                                  /* switch 11 */
            var_r22 = 0x17E;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x2C:                                  /* switch 11 */
            var_r22 = 0x17F;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x1388;
            break;
        case 0x44:                                  /* switch 11 */
            var_r22 = fn_801A9EF4(0x148, 0x14A);
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x258;
            break;
        case 0x47:                                  /* switch 11 */
            var_r22 = 0x1CD;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x3E8;
            break;
        }
        break;
    case 126:                                       /* switch 1 */
        var_r28 = 4;
        switch (arg2) {                             /* switch 12 */
        case 0x41:                                  /* switch 12 */
            var_r22 = 0x17A;
            sp8 = 0x78;
            var_r31 = 2;
            var_r21 = 0x1388;
            break;
        case 0x24:                                  /* switch 12 */
            var_r22 = 0x177;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x25:                                  /* switch 12 */
            var_r22 = 0x178;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x26:                                  /* switch 12 */
            var_r22 = 0x179;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x2C:                                  /* switch 12 */
            var_r22 = 0x17B;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x1388;
            break;
        case 0x44:                                  /* switch 12 */
            var_r22 = fn_801A9EF4(0x148, 0x14A);
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x258;
            break;
        case 0x47:                                  /* switch 12 */
            var_r22 = 0x1CD;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x3E8;
            break;
        }
        break;
    case 92:                                        /* switch 1 */
        var_r28 = 4;
        switch (arg2) {                             /* switch 13 */
        case 0x41:                                  /* switch 13 */
            var_r22 = 0x14F;
            sp8 = 0x78;
            var_r31 = 2;
            var_r21 = 0x1388;
            break;
        case 0x24:                                  /* switch 13 */
            var_r22 = 0x170;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x25:                                  /* switch 13 */
            var_r22 = 0x14D;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x26:                                  /* switch 13 */
            var_r22 = 0x171;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x44:                                  /* switch 13 */
            var_r22 = fn_801A9EF4(0x148, 0x14A);
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x258;
            break;
        case 0x47:                                  /* switch 13 */
            var_r22 = 0x1CD;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x3E8;
            break;
        case 0x2C:                                  /* switch 13 */
            var_r22 = 0x17B;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x1388;
            break;
        }
        break;
    case 193:                                       /* switch 1 */
        var_r28 = 4;
        switch (arg2) {                             /* switch 14 */
        case 0x41:                                  /* switch 14 */
            var_r22 = 0x176;
            sp8 = 0x78;
            var_r31 = 2;
            var_r21 = 0x1388;
            break;
        case 0x24:                                  /* switch 14 */
            var_r22 = 0x190;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x25:                                  /* switch 14 */
            var_r22 = 0x191;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x26:                                  /* switch 14 */
            var_r22 = 0x192;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x49:                                  /* switch 14 */
            var_r22 = 0x18F;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x2C:                                  /* switch 14 */
            var_r22 = 0x175;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x1388;
            break;
        case 0x47:                                  /* switch 14 */
            var_r22 = 0x1CD;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x3E8;
            break;
        }
        break;
    case 97:                                        /* switch 1 */
        var_r28 = 4;
        switch (arg2) {                             /* switch 15 */
        case 0x41:                                  /* switch 15 */
            var_r22 = 0x176;
            sp8 = 0x78;
            var_r31 = 2;
            var_r21 = 0x1388;
            break;
        case 0x24:                                  /* switch 15 */
            var_r22 = 0x190;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x25:                                  /* switch 15 */
            var_r22 = 0x191;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x26:                                  /* switch 15 */
            var_r22 = 0x192;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x49:                                  /* switch 15 */
            var_r22 = 0x18F;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x2C:                                  /* switch 15 */
            var_r22 = 0x175;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x1388;
            break;
        case 0x47:                                  /* switch 15 */
            var_r22 = 0x1CD;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x3E8;
            break;
        }
        break;
    case 198:                                       /* switch 1 */
        var_r28 = 1;
        if (arg2 != 0x41) {

        } else {
            var_r22 = 0x269;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x3E8;
        }
        break;
    case 123:                                       /* switch 1 */
        var_r28 = 4;
        switch (arg2) {                             /* switch 16 */
        case 0x41:                                  /* switch 16 */
            var_r22 = 0x14F;
            sp8 = 0x78;
            var_r31 = 2;
            var_r21 = 0x1388;
            break;
        case 0x24:                                  /* switch 16 */
            var_r22 = 0x170;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x25:                                  /* switch 16 */
            var_r22 = 0x14D;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x26:                                  /* switch 16 */
            var_r22 = 0x171;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x47:                                  /* switch 16 */
            var_r22 = 0x1CD;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x3E8;
            break;
        case 0x44:                                  /* switch 16 */
            var_r22 = fn_801A9EF4(0x148, 0x14A);
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x258;
            break;
        case 0x2C:                                  /* switch 16 */
            var_r22 = 0x17F;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x1388;
            break;
        }
        break;
    case 124:                                       /* switch 1 */
        var_r28 = 4;
        switch (arg2) {                             /* switch 17 */
        case 0x41:                                  /* switch 17 */
            var_r22 = 0x186;
            sp8 = 0x78;
            var_r31 = 2;
            var_r21 = 0x1388;
            break;
        case 0x24:                                  /* switch 17 */
            var_r22 = 0x184;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x25:                                  /* switch 17 */
            var_r22 = 0x185;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x26:                                  /* switch 17 */
            var_r22 = 0x188;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x2C:                                  /* switch 17 */
            var_r22 = 0x187;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x1388;
            break;
        case 0x44:                                  /* switch 17 */
            var_r22 = fn_801A9EF4(0x148, 0x14A);
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x258;
            break;
        case 0x47:                                  /* switch 17 */
            var_r22 = 0x1CE;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x3E8;
            break;
        }
        break;
    case 96:                                        /* switch 1 */
        var_r28 = 4;
        switch (arg2) {                             /* switch 18 */
        case 0x41:                                  /* switch 18 */
            var_r3_2 = 0x186;
            if (fn_80050A48() == 0x80U) {
                var_r3_2 = 0x203;
            }
            var_r22 = var_r3_2;
            sp8 = 0x78;
            var_r31 = 2;
            var_r21 = 0x1388;
            break;
        case 0x24:                                  /* switch 18 */
            var_r22 = 0x184;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x25:                                  /* switch 18 */
            var_r22 = 0x185;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x26:                                  /* switch 18 */
            var_r22 = 0x188;
            sp8 = 0x78;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x2C:                                  /* switch 18 */
            var_r22 = 0x187;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x1388;
            break;
        case 0x44:                                  /* switch 18 */
            var_r22 = fn_801A9EF4(0x148, 0x14A);
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x258;
            break;
        case 0x47:                                  /* switch 18 */
            var_r22 = 0x1CE;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x3E8;
            break;
        }
        break;
    case 125:                                       /* switch 1 */
        var_r28 = 4;
        switch (arg2) {                             /* switch 19 */
        case 0x41:                                  /* switch 19 */
            var_r22 = 0x151;
            sp8 = 0x78;
            var_r31 = 2;
            var_r21 = 0x1388;
            break;
        case 0x42:                                  /* switch 19 */
            var_r22 = 0x150;
            sp8 = 0x78;
            var_r31 = 2;
            var_r21 = 0x1388;
            break;
        case 0x24:                                  /* switch 19 */
            var_r22 = 0x198;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x25:                                  /* switch 19 */
            var_r22 = 0x199;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x26:                                  /* switch 19 */
            var_r22 = 0x196;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x49:                                  /* switch 19 */
            var_r22 = 0x197;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x9C4;
            break;
        case 0x2C:                                  /* switch 19 */
            if (fn_80050A48() == 0x10U) {
                var_r22 = 0x194;
                sp8 = 0x64;
                var_r31 = 2;
                var_r21 = 0x1388;
            } else {
                var_r22 = 0x195;
                sp8 = 0x64;
                var_r31 = 2;
                var_r21 = 0x1388;
            }
            break;
        case 0x44:                                  /* switch 19 */
            var_r22 = fn_801A9EF4(0x148, 0x14A);
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x258;
            break;
        case 0x47:                                  /* switch 19 */
            var_r22 = 0x1CE;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x3E8;
            break;
        }
        break;
    case 229:                                       /* switch 1 */
        switch (arg2) {                             /* switch 20; irregular */
        case 0x47:                                  /* switch 20 */
            var_r22 = 0x1CF;
            sp8 = 0x50;
            var_r31 = 2;
            var_r21 = 0x3E8;
            break;
        case 0x41:                                  /* switch 20 */
            var_r22 = fn_801A9EF4(0x28C, 0x28E);
            sp8 = 0x50;
            var_r31 = 2;
            var_r21 = 0x3E8;
            break;
        case 0x1C:                                  /* switch 20 */
            sp8 = 0x64;
            var_r31 = 2;
            var_r22 = fn_80049818(arg1, arg3);
            var_r21 = 0x5DC;
            break;
        case 0x1B:                                  /* switch 20 */
            sp24[0] = M2C_FIELD(var_r23, s32 *, 0xBC);
            sp24[1] = M2C_FIELD(var_r23, s32 *, 0xC0);
            sp24[2] = M2C_FIELD(var_r23, s32 *, 0xC4);
            var_r22 = fn_801A9F44(3, sp24);
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x3E8;
            break;
        case 0x2D:                                  /* switch 20 */
            var_r22 = 0xBA;
            sp8 = 0x5A;
            var_r31 = 2;
            var_r21 = 0x3E8;
            break;
        case 0x1D:                                  /* switch 20 */
            var_r22 = fn_801A9EF4(0x2E, 0x32);
            sp8 = 0x3C;
            var_r31 = 2;
            var_r21 = 0x7D0;
            break;
        case 0x4D:                                  /* switch 20 */
            var_r31 = 2;
            var_r22 = fn_80050A7C(arg1, &sp8);
            var_r21 = 0x3E8;
            break;
        case 0x56:                                  /* switch 20 */
            var_r22 = 0x287;
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x3E8;
            break;
        }
        break;
    case 186:                                       /* switch 1 */
        var_r28 = 2;
        switch (arg2) {                             /* switch 21; irregular */
        case 0x47:                                  /* switch 21 */
            var_r22 = 0x1CF;
            sp8 = 0x50;
            var_r31 = 2;
            var_r21 = 0x3E8;
            break;
        case 0x41:                                  /* switch 21 */
            var_r22 = fn_801A9EF4(0x33, 0x37);
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x3E8;
            break;
        case 0x1C:                                  /* switch 21 */
            sp8 = 0x64;
            var_r31 = 2;
            var_r22 = fn_80049818(arg1, arg3);
            var_r21 = 0x5DC;
            break;
        case 0x1B:                                  /* switch 21 */
            sp18[0] = M2C_FIELD(var_r23, s32 *, 0xC8);
            sp18[1] = M2C_FIELD(var_r23, s32 *, 0xCC);
            sp18[2] = M2C_FIELD(var_r23, s32 *, 0xD0);
            var_r22 = fn_801A9F44(3, sp18);
            sp8 = 0x64;
            var_r31 = 2;
            var_r21 = 0x3E8;
            break;
        case 0x2D:                                  /* switch 21 */
            var_r22 = 0xBA;
            sp8 = 0x5A;
            var_r31 = 2;
            var_r21 = 0x3E8;
            break;
        case 0x1D:                                  /* switch 21 */
            var_r22 = fn_801A9EF4(0x2E, 0x32);
            sp8 = 0x3C;
            var_r31 = 2;
            var_r21 = 0x7D0;
            break;
        case 0x4D:                                  /* switch 21 */
            var_r31 = 2;
            var_r22 = fn_80050A7C(arg1, &sp8);
            var_r21 = 0x3E8;
            break;
        }
        break;
    case -2:                                        /* switch 1 */
        if (arg2 != 0x1C) {

        } else {
            sp8 = 0x46;
            var_r22 = fn_801A9EF4(0x2CC, 0x2CD);
            var_r31 = 2;
            var_r21 = 0x5DC;
        }
        break;
    case -1:                                        /* switch 1 */
        if ((s32) M2C_FIELD(&lbl_803003C8, s32 *, 8) == 0xD) {
            var_r28 = 2;
            switch (arg2) {                         /* switch 22; irregular */
            case 0x47:                              /* switch 22 */
                var_r22 = 0x1CF;
                sp8 = 0x50;
                var_r31 = 2;
                var_r21 = 0x3E8;
                break;
            case 0x41:                              /* switch 22 */
                var_r22 = fn_801A9EF4(0x33, 0x37);
                sp8 = 0x50;
                var_r31 = 2;
                var_r21 = 0x3E8;
                break;
            case 0x1C:                              /* switch 22 */
                sp8 = 0x64;
                var_r31 = 2;
                var_r22 = fn_80049818(arg1, arg3);
                var_r21 = 0x5DC;
                break;
            case 0x1B:                              /* switch 22 */
                spC[0] = M2C_FIELD(var_r23, s32 *, 0xD4);
                spC[1] = M2C_FIELD(var_r23, s32 *, 0xD8);
                spC[2] = M2C_FIELD(var_r23, s32 *, 0xDC);
                var_r22 = fn_801A9F44(3, spC);
                sp8 = 0x64;
                var_r31 = 2;
                var_r21 = 0x3E8;
                break;
            case 0x2D:                              /* switch 22 */
                var_r22 = 0xBA;
                sp8 = 0x5A;
                var_r31 = 2;
                var_r21 = 0x3E8;
                break;
            case 0x1D:                              /* switch 22 */
                var_r22 = fn_801A9EF4(0x2E, 0x32);
                sp8 = 0x3C;
                var_r31 = 2;
                var_r21 = 0x7D0;
                break;
            case 0x4D:                              /* switch 22 */
                var_r31 = 2;
                var_r22 = fn_80050A7C(arg1, &sp8);
                var_r21 = 0x3E8;
                break;
            case 0x56:                              /* switch 22 */
                var_r22 = 0x287;
                sp8 = 0x64;
                var_r31 = 2;
                var_r21 = 0x3E8;
                break;
            }
        }
        break;
    }
    if (arg3 != NULL) {
        *arg3 = sp8;
    }
    if (arg4 != NULL) {
        *arg4 = var_r31;
    }
    if (arg5 != NULL) {
        *arg5 = var_r21;
    }
    if (arg6 != NULL) {
        *arg6 |= var_r28;
    }
    fn_800EB458(lbl_8024104C, var_r29, var_r22, arg2, sp8, var_r31, var_r21);
    return var_r22;
}
