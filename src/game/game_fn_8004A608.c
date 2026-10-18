typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

extern const s32 lbl_8064E498;
extern const s32 lbl_8064E49C;
extern float lbl_8063D400[];
extern int fn_8006BE44(void);
extern int lbl_8064C840;
extern int lbl_8064D5A8;
extern s32 lbl_8064C83C;
extern s32 lbl_8064D5A8;
extern s32 lbl_8064E4A8;
extern s32 lbl_8064E4AC;
extern u16 lbl_8064E43C;
extern u16 lbl_8064E448;
extern u16 lbl_8064E45C;
extern u16 lbl_8064E468;
extern u16 lbl_8064E470;
extern u16 lbl_8064E494;
extern u32 lbl_8064E3DC;
extern u32 lbl_8064E3E0;
extern u32 lbl_8064E3E4;
extern u32 lbl_8064E3E8;
extern u32 lbl_8064E3EC;
extern u32 lbl_8064E3F0;
extern u32 lbl_8064E3F4;
extern u32 lbl_8064E3F8;
extern u32 lbl_8064E3FC;
extern u32 lbl_8064E400;
extern u32 lbl_8064E404;
extern u32 lbl_8064E408;
extern u32 lbl_8064E40C;
extern u32 lbl_8064E410;
extern u32 lbl_8064E414;
extern u32 lbl_8064E418;
extern u32 lbl_8064E41C;
extern u32 lbl_8064E420;
extern u32 lbl_8064E424;
extern u32 lbl_8064E428;
extern u32 lbl_8064E42C;
extern u32 lbl_8064E430;
extern u32 lbl_8064E434;
extern u32 lbl_8064E438;
extern u32 lbl_8064E440;
extern u32 lbl_8064E444;
extern u32 lbl_8064E44C;
extern u32 lbl_8064E450;
extern u32 lbl_8064E454;
extern u32 lbl_8064E458;
extern u32 lbl_8064E460;
extern u32 lbl_8064E464;
extern u32 lbl_8064E46C;
extern u32 lbl_8064E474;
extern u32 lbl_8064E478;
extern u32 lbl_8064E47C;
extern u32 lbl_8064E480;
extern u32 lbl_8064E484;
extern u32 lbl_8064E488;
extern u32 lbl_8064E48C;
extern u32 lbl_8064E490;
extern u32 lbl_8064E4A0;
extern u32 lbl_8064E4A4;
extern u8 rand(void);

extern int fn_8011EB04(void *);
extern int fn_8011EB14(void *);
extern int fn_8011EB1C(void *);
extern int fn_8006D3E4(unsigned int, int);
extern int fn_8012FA54(void *, u32);
extern int fn_8005099C(void);
extern u16 fn_8004998C(int value, u8 *intensity, u32 *flags);
extern u16 fn_80049E74(u32 object, int mode, u8 *out_level, u8 *out_flags,
                       u16 *out_time);
extern u16 fn_80050B08(s32 arg0, s32 arg1, s32 arg2, u8 *arg3, s8 *arg4,
                       u16 *arg5, s32 *arg6);
extern int fn_801A9EF4(int low, int high);
extern int fn_801A9F44(s32 count, s32 *ids);
extern u8 rand(void);
extern void *fn_80201B9C(void);
extern void *fn_80204844(void *, int);
extern void *fn_8006D444(void *);
extern int fn_8006D2C8(void *, int);
extern int fn_80066BB8(void *, int);
extern void *fn_80201BD0(void *object);
extern int fn_800CAF7C(void *object);

extern s32 lbl_8064D5A8;
extern s32 lbl_8064C83C;
extern const s32 lbl_8064E498;
extern const s32 lbl_8064E49C;
extern float lbl_8063D400[];
extern const float lbl_8064E4B0;
extern u32 lbl_8064E4A0;

extern u8 lbl_80238E60[];
extern u32 lbl_8064E3D8;

u16 fn_8004A608(u32 object, int level, u8 *out_intensity, u8 *out_kind,
                u16 *out_time, u32 *out_flags)
{
    const s32 *pool;
    int type;
    int state;
    int handled;
    u16 result;
    u8 intensity;
    u8 kind;
    u16 time;
    u32 flags;

    pool = (const s32 *)lbl_80238E60;
    result = 0xFFFF;
    handled = 0;
    time = 0;
    intensity = 0;
    kind = 0;
    flags = 0;

    if (object == 0) {
        goto done;
    }

    type = fn_8011EB04((void *)object);
    state = fn_8011EB1C((void *)object);

    switch (level) {
    case 0:
    case 1:
    case 2:
        if (state == 1 && fn_8006D3E4(0, 8) != 0) {
            kind = 8;
            handled = 1;
        }
        break;
    }

    if (handled != 0) {
        goto done;
    }

    if (state == 1 || state == 2) {
        switch (type) {
        case 0x0:
            switch (level) {
            case 0x0:
                intensity = 20;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 0;
                break;
            case 0x1:
                intensity = 40;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 600;
                break;
            case 0x2:
                intensity = 70;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 1000;
                break;
            case 0x38:
                result = fn_801A9EF4(0xFE, 0x100);
                intensity = 75;
                kind = 2;
                time = 800;
                break;
            case 0x14:
                result = fn_801A9EF4(0xB, 0xF);
                intensity = 60;
                kind = 2;
                time = 0;
                break;
            case 0x10:
            case 0x2B:
            case 0x35:
            case 0x36:
            case 0x41:
                flags |= 1;
                result = fn_80050B08(fn_8005099C(), 0, 0x41, &intensity, (s8 *)&kind, &time, (s32 *)&flags);
                break;
            case 0x1B:
            case 0x1C:
            case 0x1D:
            case 0x24:
            case 0x25:
            case 0x26:
            case 0x2C:
            case 0x2D:
            case 0x49:
                result = fn_80050B08(fn_8005099C(), 0, level, &intensity, (s8 *)&kind, &time, (s32 *)&flags);
                break;
            case 0x11:
                intensity = 60;
                result = 0;
                kind = 2;
                time = 1500;
                break;
            case 0x12:
                intensity = 100;
                result = 0;
                kind = 2;
                time = 2000;
                break;
            case 0x1E:
            case 0x1F:
            case 0x20:
            case 0x34:
            case 0x51:
            case 0x52:
                result = fn_80049E74(object, level, &intensity, &kind, &time);
                break;
            case 0xA:
                intensity = 100;
                result = 0x1C;
                kind = 2;
                time = 5000;
                flags |= 8;
                break;
            case 0xB:
                intensity = 75;
                result = 0x10;
                kind = 2;
                time = 5000;
                break;
            case 0x46: {
                u32 pair;
                pair = lbl_8064E3D8;
                result = ((u16 *)&pair)[fn_801A9EF4(0, 1)];
                intensity = 40;
                kind = 4;
                time = 1000;
                break;
            }
            case 0x22: {
                s32 ids[4];
                ids[0] = pool[0];
                ids[1] = pool[1];
                ids[2] = pool[2];
                ids[3] = pool[3];
                result = fn_801A9F44(4, ids);
                intensity = 90;
                kind = 4;
                time = 1500;
                break;
            }
            case 0x23:
                if (fn_8011EB14((void *)object) == 5) {
                    s32 ids[4];
                    ids[0] = pool[4];
                    ids[1] = pool[5];
                    ids[2] = pool[6];
                    ids[3] = pool[7];
                    result = fn_801A9F44(4, ids);
                    intensity = 90;
                    kind = 4;
                    time = 1500;
                } else {
                    s32 ids[4];
                    ids[0] = pool[8];
                    ids[1] = pool[9];
                    ids[2] = pool[10];
                    ids[3] = pool[11];
                    result = fn_801A9F44(4, ids);
                    intensity = 70;
                    kind = 4;
                    time = 1500;
                }
                break;
            case 0x13:
                result = fn_801A9EF4(0x19F, 0x1A1);
                intensity = 70;
                kind = 2;
                time = 10000;
                break;
            case 0x21: {
                s32 ids[5];
                ids[0] = pool[12];
                ids[1] = pool[13];
                ids[2] = pool[14];
                ids[3] = pool[15];
                ids[4] = pool[16];
                result = fn_801A9F44(5, ids);
                intensity = 75;
                kind = 4;
                time = 1500;
                break;
            }
            case 0x2E:
                intensity = 100;
                result = 0xB9;
                kind = 4;
                time = 1500;
                break;
            case 0x37:
                intensity = 90;
                result = 0xD6;
                kind = 4;
                time = 1000;
                break;
            }
            break;
        case 0x90:
        case 0x96:
            switch (level) {
            case 0x0:
                intensity = 20;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 0;
                break;
            case 0x1:
                intensity = 40;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 600;
                break;
            case 0x2:
                intensity = 70;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 1000;
                break;
            case 0x14:
                result = fn_801A9EF4(0xB, 0xF);
                intensity = 60;
                kind = 2;
                time = 0;
                break;
            case 0x38:
                result = fn_801A9EF4(0xFA, 0xFD);
                intensity = 75;
                kind = 2;
                time = 800;
                break;
            case 0x10:
            case 0x2B:
            case 0x35:
            case 0x36:
            case 0x41:
                flags |= 1;
                result = fn_80050B08(fn_8005099C(), 0, 0x41, &intensity, (s8 *)&kind, &time, (s32 *)&flags);
                break;
            case 0x1B:
            case 0x1C:
            case 0x1D:
            case 0x24:
            case 0x25:
            case 0x26:
            case 0x2C:
            case 0x2D:
            case 0x49:
                result = fn_80050B08(fn_8005099C(), 0, level, &intensity, (s8 *)&kind, &time, (s32 *)&flags);
                break;
            case 0x11:
                intensity = 60;
                result = 0;
                kind = 2;
                time = 1500;
                break;
            case 0x12:
                intensity = 100;
                result = 0;
                kind = 2;
                time = 2000;
                break;
            case 0x39:
                result = fn_801A9EF4(0x33, 0x37);
                intensity = 100;
                kind = 2;
                time = 3000;
                break;
            case 0x1E:
            case 0x1F:
            case 0x20:
            case 0x34:
            case 0x51:
            case 0x52:
                result = fn_80049E74(object, level, &intensity, &kind, &time);
                break;
            case 0xA:
                intensity = 100;
                result = 0x1C;
                kind = 2;
                time = 5000;
                flags |= 8;
                break;
            case 0xB:
                intensity = 75;
                result = 0x10;
                kind = 2;
                time = 5000;
                break;
            case 0x46: {
                u32 pair;
                pair = lbl_8064E3DC;
                result = ((u16 *)&pair)[fn_801A9EF4(0, 1)];
                intensity = 40;
                kind = 4;
                time = 1000;
                break;
            }
            case 0x4B:
                intensity = 60;
                result = 0x1CD;
                kind = 2;
                time = 600;
                break;
            case 0x22:
                result = fn_801A9EF4(0x3F, 0x40);
                intensity = 90;
                kind = 4;
                time = 1500;
                break;
            case 0x23:
                if (fn_8011EB14((void *)object) == 5) {
                    result = fn_801A9EF4(0x3F, 0x40);
                    intensity = 90;
                    kind = 4;
                    time = 1500;
                } else {
                    result = fn_801A9EF4(0x3F, 0x40);
                    intensity = 70;
                    kind = 4;
                    time = 1500;
                }
                break;
            case 0x13:
                result = fn_801A9EF4(0x19F, 0x1A1);
                intensity = 70;
                kind = 2;
                time = 10000;
                break;
            case 0x21:
                result = fn_801A9EF4(0xCE, 0xD0);
                intensity = 70;
                kind = 4;
                time = 1500;
                break;
            case 0x57:
                if ((int)rand() < 128) {
                    result = fn_801A9EF4(0xCE, 0xD0);
                    intensity = 60;
                    kind = 4;
                    time = 1500;
                } else {
                    kind = 8;
                }
                break;
            case 0x2E:
                intensity = 100;
                result = 0xB9;
                kind = 4;
                time = 1500;
                break;
            case 0x3B:
                result = fn_801A9EF4(0x124, 0x129);
                intensity = 100;
                kind = 0;
                time = 0;
                break;
            case 0x3C: {
                u32 quad[2];
                quad[0] = lbl_8064E3E0;
                quad[1] = lbl_8064E3E4;
                result = ((u16 *)quad)[fn_801A9EF4(0, 3)];
                intensity = 100;
                kind = 0;
                time = 0;
                break;
            }
            case 0x3E: {
                u32 quad[2];
                quad[0] = lbl_8064E3E8;
                quad[1] = lbl_8064E3EC;
                result = ((u16 *)quad)[fn_801A9EF4(0, 3)];
                intensity = 100;
                kind = 0;
                time = 0;
                break;
            }
            }
            break;
        case 0x9:
            switch (level) {
            case 0x0:
                intensity = 30;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 0;
                break;
            case 0x1:
                intensity = 40;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 600;
                break;
            case 0x2:
                intensity = 70;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 1000;
                break;
            case 0x38:
                result = fn_801A9EF4(0xFA, 0xFD);
                intensity = 75;
                kind = 2;
                time = 800;
                break;
            case 0x10:
            case 0x2B:
            case 0x35:
            case 0x36:
            case 0x41:
                flags |= 1;
                result = fn_80050B08(fn_8005099C(), 0, 0x41, &intensity, (s8 *)&kind, &time, (s32 *)&flags);
                break;
            case 0x1B:
            case 0x1C:
            case 0x1D:
            case 0x24:
            case 0x25:
            case 0x26:
            case 0x2C:
            case 0x2D:
            case 0x49:
                result = fn_80050B08(fn_8005099C(), 0, level, &intensity, (s8 *)&kind, &time, (s32 *)&flags);
                break;
            case 0x11:
                intensity = 50;
                result = 0;
                kind = 2;
                time = 1500;
                break;
            case 0x12:
                intensity = 100;
                result = 0;
                kind = 2;
                time = 2000;
                break;
            case 0x1E:
            case 0x1F:
            case 0x20:
            case 0x34:
            case 0x51:
            case 0x52:
                result = fn_80049E74(object, level, &intensity, &kind, &time);
                break;
            case 0xA:
                intensity = 100;
                result = 0x1C;
                kind = 2;
                time = 5000;
                flags |= 8;
                break;
            case 0xB:
                intensity = 75;
                result = 0x10;
                kind = 2;
                time = 5000;
                break;
            case 0x46: {
                u32 pair;
                pair = lbl_8064E3F0;
                result = ((u16 *)&pair)[fn_801A9EF4(0, 1)];
                intensity = 40;
                kind = 4;
                time = 1000;
                break;
            }
            case 0x22:
                result = fn_801A9EF4(0x73, 0x75);
                intensity = 90;
                kind = 4;
                time = 1500;
                break;
            case 0x23:
                if (fn_8011EB14((void *)object) == 5) {
                    result = fn_801A9EF4(0x73, 0x75);
                    intensity = 90;
                    kind = 4;
                    time = 1500;
                } else {
                    result = fn_801A9EF4(0x189, 0x18C);
                    intensity = 70;
                    kind = 4;
                    time = 1500;
                }
                break;
            case 0x13:
                result = fn_801A9EF4(0x19F, 0x1A1);
                intensity = 70;
                kind = 2;
                time = 10000;
                break;
            case 0x21:
                result = fn_801A9EF4(0x4C, 0x4E);
                intensity = 60;
                kind = 4;
                time = 1500;
                break;
            case 0x57:
                if ((int)rand() < 128) {
                    result = fn_801A9EF4(0x4C, 0x4E);
                    intensity = 60;
                    kind = 4;
                    time = 1500;
                } else {
                    kind = 8;
                }
                break;
            case 0x37:
                result = fn_801A9EF4(0x224, 0x225);
                intensity = 100;
                kind = 2;
                time = 3000;
                break;
            case 0x3B: {
                u32 pair;
                pair = lbl_8064E3F4;
                result = ((u16 *)&pair)[fn_801A9EF4(0, 1)];
                intensity = 100;
                kind = 0;
                time = 0;
                break;
            }
            case 0x3C: {
                u32 quad[2];
                quad[0] = lbl_8064E3F8;
                quad[1] = lbl_8064E3FC;
                result = ((u16 *)quad)[fn_801A9EF4(0, 3)];
                intensity = 100;
                kind = 0;
                time = 0;
                break;
            }
            case 0x3E: {
                u32 quad[2];
                quad[0] = lbl_8064E400;
                quad[1] = lbl_8064E404;
                result = ((u16 *)quad)[fn_801A9EF4(0, 3)];
                intensity = 100;
                kind = 0;
                time = 0;
                break;
            }
            }
            break;
        case 0x12:
        case 0x91:
            switch (level) {
            case 0x00:
                intensity = 30;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 0;
                break;
            case 0x01:
                intensity = 40;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 600;
                break;
            case 0x02:
                intensity = 70;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 1000;
                break;
            case 0x38:
                result = fn_801A9EF4(0xFA, 0xFD);
                intensity = 75;
                kind = 2;
                time = 800;
                break;
            case 0x10:
            case 0x2B:
            case 0x35:
            case 0x36:
            case 0x41:
                flags |= 1;
                result = fn_80050B08(fn_8005099C(), 0, 0x41, &intensity, (s8 *)&kind, &time, (s32 *)&flags);
                break;
            case 0x1B:
            case 0x1C:
            case 0x1D:
            case 0x24:
            case 0x25:
            case 0x26:
            case 0x2C:
            case 0x2D:
            case 0x47:
            case 0x49:
                result = fn_80050B08(fn_8005099C(), 0, level, &intensity, (s8 *)&kind, &time, (s32 *)&flags);
                break;
            case 0x11:
                intensity = 50;
                result = 0;
                kind = 2;
                time = 1500;
                break;
            case 0x12:
                intensity = 100;
                result = 0;
                kind = 2;
                time = 2000;
                break;
            case 0x1E:
            case 0x1F:
            case 0x20:
            case 0x34:
            case 0x51:
            case 0x52:
                result = fn_80049E74(object, level, &intensity, &kind, &time);
                break;
            case 0x0A:
                intensity = 100;
                result = 0x1C;
                kind = 2;
                time = 5000;
                flags |= 8;
                break;
            case 0x0B:
                intensity = 75;
                result = 0x10;
                kind = 2;
                time = 5000;
                break;
            case 0x46: {  /* sda word lbl_8064E408 copied to sp+0x38, indexed by random 0..1 */
                u32 pair;
                pair = lbl_8064E408;
                result = ((u16 *)&pair)[fn_801A9EF4(0, 1)];
                intensity = 40;
                kind = 4;
                time = 1000;
                break;
            }
            case 0x22:
                result = fn_801A9EF4(0x3F, 0x40);
                intensity = 90;
                kind = 4;
                time = 1500;
                break;
            case 0x23:
                if (fn_8011EB14((void *)object) == 5) {
                    result = fn_801A9EF4(0x3F, 0x40);
                    intensity = 90;
                    kind = 4;
                    time = 1500;
                } else {
                    result = fn_801A9EF4(0x3F, 0x40);
                    intensity = 70;
                    kind = 4;
                    time = 1500;
                }
                break;
            case 0x2E:
                intensity = 70;
                result = 0x22A;
                kind = 4;
                time = 1500;
                break;
            case 0x13:
                result = fn_801A9EF4(0x19F, 0x1A1);
                intensity = 70;
                kind = 2;
                time = 10000;
                break;
            case 0x21:
                result = fn_801A9EF4(0x115, 0x117);
                intensity = 60;
                kind = 4;
                time = 1500;
                break;
            case 0x57:
                if ((int)rand() < 128) {
                    result = fn_801A9EF4(0x115, 0x117);
                    intensity = 60;
                    kind = 4;
                    time = 1500;
                } else {
                    kind = 8;
                }
                break;
            case 0x3B:
                result = fn_801A9EF4(0x133, 0x136);
                intensity = 100;
                kind = 0;
                time = 0;
                break;
            case 0x3C: {  /* 10 bytes (lwz,lwz,lhz) copied from pool+0x44 to sp+0x128 */
                u16 ids[5];
                *(s32 *)&ids[0] = pool[17];
                *(s32 *)&ids[2] = pool[18];
                ids[4] = ((const u16 *)pool)[38];
                result = ids[fn_801A9EF4(0, 4)];
                intensity = 100;
                kind = 0;
                time = 0;
                break;
            }
            case 0x3E:
                result = fn_801A9EF4(0x13A, 0x13B);
                intensity = 100;
                kind = 0;
                time = 0;
                break;
            }
            break;
        case 0x45:
            switch (level) {
            case 0x00:
                intensity = 30;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 0;
                break;
            case 0x01:
                intensity = 40;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 600;
                break;
            case 0x02:
                intensity = 70;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 1000;
                break;
            case 0x38:
                result = fn_801A9EF4(0xFA, 0xFD);
                intensity = 75;
                kind = 2;
                time = 800;
                break;
            case 0x10:
            case 0x2B:
            case 0x35:
            case 0x36:
            case 0x41:
                flags |= 1;
                result = fn_80050B08(fn_8005099C(), 0, 0x41, &intensity, (s8 *)&kind, &time, (s32 *)&flags);
                break;
            case 0x1B:
            case 0x1C:
            case 0x1D:
            case 0x24:
            case 0x25:
            case 0x26:
            case 0x2C:
            case 0x2D:
            case 0x49:
                result = fn_80050B08(fn_8005099C(), 0, level, &intensity, (s8 *)&kind, &time, (s32 *)&flags);
                break;
            case 0x11:
                intensity = 50;
                result = 0;
                kind = 2;
                time = 1500;
                break;
            case 0x12:
                intensity = 100;
                result = 0;
                kind = 2;
                time = 2000;
                break;
            case 0x1E:
            case 0x1F:
            case 0x20:
            case 0x34:
            case 0x51:
            case 0x52:
                result = fn_80049E74(object, level, &intensity, &kind, &time);
                break;
            case 0x0A:
                intensity = 100;
                result = 0x1C;
                kind = 2;
                time = 5000;
                flags |= 8;
                break;
            case 0x0B:
                intensity = 75;
                result = 0x10;
                kind = 2;
                time = 5000;
                break;
            case 0x46: {  /* sda word lbl_8064E40C copied to sp+0x34, indexed by random 0..1 */
                u32 pair;
                pair = lbl_8064E40C;
                result = ((u16 *)&pair)[fn_801A9EF4(0, 1)];
                intensity = 40;
                kind = 4;
                time = 1000;
                break;
            }
            case 0x22:
                result = fn_801A9EF4(0x3F, 0x40);
                intensity = 90;
                kind = 4;
                time = 1500;
                break;
            case 0x23:
                if (fn_8011EB14((void *)object) == 5) {
                    result = fn_801A9EF4(0x3F, 0x40);
                    intensity = 90;
                    kind = 4;
                    time = 1500;
                } else {
                    result = fn_801A9EF4(0x3F, 0x40);
                    intensity = 70;
                    kind = 4;
                    time = 1500;
                }
                break;
            case 0x13:
                result = fn_801A9EF4(0x19F, 0x1A1);
                intensity = 70;
                kind = 2;
                time = 10000;
                break;
            case 0x21:
                result = fn_801A9EF4(0x11C, 0x11E);
                intensity = 60;
                kind = 4;
                time = 1500;
                break;
            case 0x57:
                if ((int)rand() < 128) {
                    result = fn_801A9EF4(0x11C, 0x11E);
                    intensity = 60;
                    kind = 4;
                    time = 1500;
                } else {
                    kind = 8;
                }
                break;
            case 0x3B:
                intensity = 100;
                result = 0x113;
                kind = 0;
                time = 0;
                break;
            case 0x3C: {  /* 3 words copied from pool+0x50 to sp+0x11C, indexed as u16 by random 0..5 */
                s32 ids[3];
                ids[0] = pool[20];
                ids[1] = pool[21];
                ids[2] = pool[22];
                result = ((u16 *)ids)[fn_801A9EF4(0, 5)];
                intensity = 100;
                kind = 0;
                time = 0;
                break;
            }
            case 0x3E:
                intensity = 100;
                result = 0x110;
                kind = 0;
                time = 0;
                break;
            }
            break;
        case 0x46:
        case 0x8E:
            switch (level) {
            case 0x00:
                intensity = 30;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 0;
                break;
            case 0x01:
                intensity = 55;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 600;
                break;
            case 0x02:
                intensity = 70;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 1000;
                break;
            case 0x38:
                result = fn_801A9EF4(0xFA, 0xFD);
                intensity = 50;
                kind = 2;
                time = 800;
                break;
            case 0x10:
            case 0x2B:
            case 0x35:
            case 0x36:
            case 0x41:
                flags |= 1;
                result = fn_80050B08(fn_8005099C(), 0, 0x41, &intensity, (s8 *)&kind, &time, (s32 *)&flags);
                break;
            case 0x1B:
            case 0x1C:
            case 0x1D:
            case 0x24:
            case 0x25:
            case 0x26:
            case 0x2C:
            case 0x2D:
            case 0x49:
                result = fn_80050B08(fn_8005099C(), 0, level, &intensity, (s8 *)&kind, &time, (s32 *)&flags);
                break;
            case 0x11:
                intensity = 50;
                result = 0;
                kind = 2;
                time = 1500;
                break;
            case 0x12:
                intensity = 100;
                result = 0;
                kind = 2;
                time = 2000;
                break;
            case 0x1E:
            case 0x1F:
            case 0x20:
            case 0x34:
            case 0x51:
            case 0x52:
                result = fn_80049E74(object, level, &intensity, &kind, &time);
                break;
            case 0x0A:
                intensity = 100;
                result = 0x1C;
                kind = 2;
                time = 5000;
                flags |= 8;
                break;
            case 0x0B:
                intensity = 75;
                result = 0x10;
                kind = 2;
                time = 5000;
                break;
            case 0x46: {  /* sda word lbl_8064E410 copied to sp+0x30, indexed by random 0..1 */
                u32 pair;
                pair = lbl_8064E410;
                result = ((u16 *)&pair)[fn_801A9EF4(0, 1)];
                intensity = 40;
                kind = 4;
                time = 1000;
                break;
            }
            case 0x22:
                result = fn_801A9EF4(0x73, 0x75);
                intensity = 90;
                kind = 4;
                time = 1500;
                break;
            case 0x23:
                if (fn_8011EB14((void *)object) == 5) {
                    result = fn_801A9EF4(0x73, 0x75);
                    intensity = 90;
                    kind = 4;
                    time = 1500;
                } else {
                    result = fn_801A9EF4(0x189, 0x18C);
                    intensity = 70;
                    kind = 4;
                    time = 1500;
                }
                break;
            case 0x13:
                result = fn_801A9EF4(0x19F, 0x1A1);
                intensity = 70;
                kind = 2;
                time = 10000;
                break;
            case 0x21:
                result = fn_801A9EF4(0x11F, 0x122);
                intensity = 60;
                kind = 4;
                time = 1500;
                break;
            case 0x3B: {  /* sda words lbl_8064E414/418 copied to sp+0xC0, indexed as u16 by random 0..3 */
                u32 quad[2];
                quad[0] = lbl_8064E414;
                quad[1] = lbl_8064E418;
                result = ((u16 *)quad)[fn_801A9EF4(0, 3)];
                intensity = 100;
                kind = 0;
                time = 0;
                break;
            }
            case 0x3C: {  /* sda words lbl_8064E41C/420 copied to sp+0xB8, indexed as u16 by random 0..3 */
                u32 quad[2];
                quad[0] = lbl_8064E41C;
                quad[1] = lbl_8064E420;
                result = ((u16 *)quad)[fn_801A9EF4(0, 3)];
                intensity = 100;
                kind = 0;
                time = 0;
                break;
            }
            case 0x3E: {  /* sda words lbl_8064E424/428 copied to sp+0xB0, indexed as u16 by random 0..3 */
                u32 quad[2];
                quad[0] = lbl_8064E424;
                quad[1] = lbl_8064E428;
                result = ((u16 *)quad)[fn_801A9EF4(0, 3)];
                intensity = 100;
                kind = 0;
                time = 0;
                break;
            }
            case 0x3D: {  /* body emitted after 0x3E in retail */
                int n;
                n = fn_8006BE44();
                intensity = 75;
                result = 0x253;
                kind = 0;
                time = 0;
                switch (n) {
                case 2:
                    result = 0x254;
                    break;
                case 3:
                    result = 0x255;
                    break;
                }
                break;
            }
            }
            break;
        case 0x49:  /* 0x8004BFA0, jumptable_8024039C */
            switch (level) {
            case 0x0:
                intensity = 40;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 0;
                break;
            case 0x1:
                intensity = 60;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 600;
                break;
            case 0x2:
                intensity = 90;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 1000;
                break;
            case 0x38:
                result = fn_801A9EF4(0xFA, 0xFD);
                intensity = 75;
                kind = 2;
                time = 800;
                break;
            case 0x10:
            case 0x2B:
            case 0x35:
            case 0x36:
            case 0x41:
                flags |= 1;
                result = fn_80050B08(fn_8005099C(), 0, 0x41, &intensity, (s8 *)&kind, &time, (s32 *)&flags);
                break;
            case 0x1B:
            case 0x1C:
            case 0x1D:
            case 0x24:
            case 0x25:
            case 0x26:
            case 0x2C:
            case 0x2D:
            case 0x49:
                result = fn_80050B08(fn_8005099C(), 0, level, &intensity, (s8 *)&kind, &time, (s32 *)&flags);
                break;
            case 0x11:
                intensity = 50;
                result = 0;
                kind = 2;
                time = 1500;
                break;
            case 0x12:
                intensity = 100;
                result = 0;
                kind = 2;
                time = 2000;
                break;
            case 0x39:
                intensity = 100;
                result = 0x1D1;
                kind = 2;
                time = 3000;
                break;
            case 0x1E:
            case 0x1F:
            case 0x20:
            case 0x34:
            case 0x51:
            case 0x52:
                result = fn_80049E74(object, level, &intensity, &kind, &time);
                break;
            case 0xA:
                intensity = 100;
                result = 0x1C;
                kind = 2;
                time = 5000;
                flags |= 8;
                break;
            case 0xB:
                intensity = 75;
                result = 0x10;
                kind = 2;
                time = 5000;
                break;
            case 0x46: {  /* sda word 0x00330037 copied to sp+0x2C, indexed by random 0..1 */
                u32 pair;
                pair = lbl_8064E42C;
                result = ((u16 *)&pair)[fn_801A9EF4(0, 1)];
                intensity = 40;
                kind = 4;
                time = 1000;
                break;
            }
            case 0x22:
                result = fn_801A9EF4(0x3F, 0x40);
                intensity = 90;
                kind = 4;
                time = 1500;
                break;
            case 0x23:
                if (fn_8011EB14((void *)object) == 5) {
                    result = fn_801A9EF4(0x3F, 0x40);
                    intensity = 90;
                    kind = 4;
                    time = 1500;
                } else {
                    result = fn_801A9EF4(0x3F, 0x40);
                    intensity = 70;
                    kind = 4;
                    time = 1500;
                }
                break;
            case 0x13:
                result = fn_801A9EF4(0x19F, 0x1A1);
                intensity = 70;
                kind = 2;
                time = 10000;
                break;
            case 0x21:
                result = fn_801A9EF4(0x123, 0x126);
                intensity = 60;
                kind = 4;
                time = 1500;
                break;
            case 0x57:
                if ((int)rand() < 128) {
                    result = fn_801A9EF4(0x123, 0x126);
                    intensity = 60;
                    kind = 4;
                    time = 1500;
                } else {
                    kind = 8;
                }
                break;
            case 0x4B:
                intensity = 80;
                result = 0x19A;
                kind = 4;
                time = 500;
                break;
            case 0x3F:
                intensity = 80;
                result = 0x1C8;
                kind = 4;
                time = 500;
                break;
            case 0x4A:
                intensity = 100;
                result = 0x1C9;
                kind = 4;
                time = 500;
                break;
            case 0x3B:
                result = fn_801A9EF4(0x12A, 0x12B);
                intensity = 100;
                kind = 0;
                time = 0;
                break;
            case 0x3C: {  /* sda words 0x012D012E,0x01310132 copied to sp+0xA8, indexed by random 0..3 */
                u32 ids[2];
                ids[0] = lbl_8064E430;
                ids[1] = lbl_8064E434;
                result = ((u16 *)ids)[fn_801A9EF4(0, 3)];
                intensity = 100;
                kind = 0;
                time = 0;
                break;
            }
            case 0x3E: {  /* sda word 0x012F0130 + half 0x012C copied to sp+0xA0, indexed by random 0..2 */
                struct { u32 w; u16 h; } ids;
                ids.w = lbl_8064E438;
                ids.h = lbl_8064E43C;
                result = ((u16 *)&ids)[fn_801A9EF4(0, 2)];
                intensity = 100;
                kind = 0;
                time = 0;
                break;
            }
            }
            break;
        case 0x4A:  /* 0x8004C41C, jumptable_8024023C */
        case 0x92:
            switch (level) {
            case 0x0:
                intensity = 30;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 0;
                break;
            case 0x1:
                intensity = 40;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 600;
                break;
            case 0x2:
                intensity = 70;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 1000;
                break;
            case 0x38:
                result = fn_801A9EF4(0xFA, 0xFD);
                intensity = 75;
                kind = 2;
                time = 800;
                break;
            case 0x10:
            case 0x2B:
            case 0x35:
            case 0x36:
            case 0x41:
                flags |= 1;
                result = fn_80050B08(fn_8005099C(), 0, 0x41, &intensity, (s8 *)&kind, &time, (s32 *)&flags);
                break;
            case 0x1B:
            case 0x1C:
            case 0x1D:
            case 0x24:
            case 0x25:
            case 0x26:
            case 0x2C:
            case 0x2D:
            case 0x49:
                result = fn_80050B08(fn_8005099C(), 0, level, &intensity, (s8 *)&kind, &time, (s32 *)&flags);
                break;
            case 0x11:
                intensity = 50;
                result = 0;
                kind = 2;
                time = 1500;
                break;
            case 0x12:
                intensity = 100;
                result = 0;
                kind = 2;
                time = 2000;
                break;
            case 0x1E:
            case 0x1F:
            case 0x20:
            case 0x34:
            case 0x51:
            case 0x52:
                result = fn_80049E74(object, level, &intensity, &kind, &time);
                break;
            case 0xA:
                intensity = 100;
                result = 0x1C;
                kind = 2;
                time = 5000;
                flags |= 8;
                break;
            case 0xB:
                intensity = 75;
                result = 0x10;
                kind = 2;
                time = 5000;
                break;
            case 0x46: {  /* sda word 0x00330037 copied to sp+0x28, indexed by random 0..1 */
                u32 pair;
                pair = lbl_8064E440;
                result = ((u16 *)&pair)[fn_801A9EF4(0, 1)];
                intensity = 40;
                kind = 4;
                time = 1000;
                break;
            }
            case 0x22:
                result = fn_801A9EF4(0x3F, 0x40);
                intensity = 90;
                kind = 4;
                time = 1500;
                break;
            case 0x23:
                if (fn_8011EB14((void *)object) == 5) {
                    result = fn_801A9EF4(0x3F, 0x40);
                    intensity = 90;
                    kind = 4;
                    time = 1500;
                } else {
                    result = fn_801A9EF4(0x3F, 0x40);
                    intensity = 70;
                    kind = 4;
                    time = 1500;
                }
                break;
            case 0x13:
                result = fn_801A9EF4(0x19F, 0x1A1);
                intensity = 70;
                kind = 2;
                time = 10000;
                break;
            case 0x21:
                result = fn_801A9EF4(0x127, 0x12A);
                intensity = 100;
                kind = 4;
                time = 1500;
                break;
            case 0x57:
                if ((int)rand() < 128) {
                    result = fn_801A9EF4(0x127, 0x12A);
                    intensity = 60;
                    kind = 4;
                    time = 1500;
                } else {
                    kind = 8;
                }
                break;
            case 0x3D:
                fn_8006BE44();
                intensity = 75;
                result = 0x257;
                kind = 0;
                time = 0;
                break;
            case 0x3B: {  /* sda word 0x01490151 + half 0x0153 copied to sp+0x98, indexed by random 0..2 */
                struct { u32 w; u16 h; } ids;
                ids.w = lbl_8064E444;
                ids.h = lbl_8064E448;
                result = ((u16 *)&ids)[fn_801A9EF4(0, 2)];
                intensity = 100;
                kind = 0;
                time = 0;
                break;
            }
            case 0x3C: {  /* sda words 0x014A014B,0x014E014F copied to sp+0x90, indexed by random 0..3 */
                u32 ids[2];
                ids[0] = lbl_8064E44C;
                ids[1] = lbl_8064E450;
                result = ((u16 *)ids)[fn_801A9EF4(0, 3)];
                intensity = 100;
                kind = 0;
                time = 0;
                break;
            }
            case 0x3E: {  /* 4 words copied from pool+0x5C to sp+0x10C */
                s32 ids[4];
                ids[0] = pool[23];
                ids[1] = pool[24];
                ids[2] = pool[25];
                ids[3] = pool[26];
                result = fn_801A9F44(4, ids);
                intensity = 100;
                kind = 0;
                time = 0;
                break;
            }
            }
            break;
        case 0x4B:  /* 0x8004C858, jumptable_802400DC */
            switch (level) {
            case 0x0:
                intensity = 30;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 0;
                break;
            case 0x1:
                intensity = 60;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 600;
                break;
            case 0x2:
                intensity = 90;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 1000;
                break;
            case 0x38:
                result = fn_801A9EF4(0xFA, 0xFD);
                intensity = 75;
                kind = 2;
                time = 800;
                break;
            case 0x10:
            case 0x2B:
            case 0x35:
            case 0x36:
            case 0x41:
                flags |= 1;
                result = fn_80050B08(fn_8005099C(), 0, 0x41, &intensity, (s8 *)&kind, &time, (s32 *)&flags);
                break;
            case 0x1B:
            case 0x1C:
            case 0x1D:
            case 0x24:
            case 0x25:
            case 0x26:
            case 0x2C:
            case 0x2D:
            case 0x47:
            case 0x49:
                result = fn_80050B08(fn_8005099C(), 0, level, &intensity, (s8 *)&kind, &time, (s32 *)&flags);
                break;
            case 0x11:
                intensity = 50;
                result = 0;
                kind = 2;
                time = 1500;
                break;
            case 0x12:
                intensity = 100;
                result = 0;
                kind = 2;
                time = 2000;
                break;
            case 0x1E:
            case 0x1F:
            case 0x20:
            case 0x34:
            case 0x51:
            case 0x52:
                result = fn_80049E74(object, level, &intensity, &kind, &time);
                break;
            case 0xA:
                intensity = 100;
                result = 0x1C;
                kind = 2;
                time = 5000;
                flags |= 8;
                break;
            case 0xB:
                intensity = 75;
                result = 0x10;
                kind = 2;
                time = 5000;
                break;
            case 0x46: {  /* sda word 0x00330037 copied to sp+0x24, indexed by random 0..1 */
                u32 pair;
                pair = lbl_8064E454;
                result = ((u16 *)&pair)[fn_801A9EF4(0, 1)];
                intensity = 40;
                kind = 4;
                time = 1000;
                break;
            }
            case 0x22:
                result = fn_801A9EF4(0x3F, 0x40);
                intensity = 90;
                kind = 4;
                time = 1500;
                break;
            case 0x23:
                if (fn_8011EB14((void *)object) == 5) {
                    result = fn_801A9EF4(0x3F, 0x40);
                    intensity = 90;
                    kind = 4;
                    time = 1500;
                } else {
                    result = fn_801A9EF4(0x3F, 0x40);
                    intensity = 70;
                    kind = 4;
                    time = 1500;
                }
                break;
            case 0x13:
                result = fn_801A9EF4(0x19F, 0x1A1);
                intensity = 70;
                kind = 2;
                time = 10000;
                break;
            case 0x21:
                result = fn_801A9EF4(0x135, 0x137);
                intensity = 60;
                kind = 4;
                time = 1500;
                break;
            case 0x57:
                if ((int)rand() < 128) {
                    result = fn_801A9EF4(0x135, 0x137);
                    intensity = 60;
                    kind = 4;
                    time = 1500;
                } else {
                    kind = 8;
                }
                break;
            case 0x3B:
                result = fn_801A9EF4(0x155, 0x156);
                intensity = 100;
                kind = 0;
                time = 0;
                break;
            case 0x3C: {  /* 2 words + half copied from pool+0x6C to sp+0x100, indexed by random 0..4 */
                struct { s32 a; s32 b; u16 c; } ids;
                ids.a = pool[27];
                ids.b = pool[28];
                ids.c = *(const u16 *)&pool[29];
                result = ((u16 *)&ids)[fn_801A9EF4(0, 4)];
                intensity = 100;
                kind = 0;
                time = 0;
                break;
            }
            case 0x3E: {  /* sda word 0x015C015D + half 0x0157 copied to sp+0x88, indexed by random 0..2 */
                struct { u32 w; u16 h; } ids;
                ids.w = lbl_8064E458;
                ids.h = lbl_8064E45C;
                result = ((u16 *)&ids)[fn_801A9EF4(0, 2)];
                intensity = 100;
                kind = 0;
                time = 0;
                break;
            }
            case 0x3D:
            {
                int phase = fn_8006BE44();
                result = 0x256;
                if (phase >= 2) {
                    result = 0x257;
                }
            }
                intensity = 75;
                kind = 0;
                time = 0;
                break;
            }
            break;
        case 0x4C:
        case 0x93:
            switch (level) {
            case 0:
                intensity = 30;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 0;
                break;
            case 1:
                intensity = 40;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 600;
                break;
            case 2:
                intensity = 70;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 1000;
                break;
            case 0x38:
                result = fn_801A9EF4(0xFA, 0xFD);
                intensity = 75;
                kind = 2;
                time = 800;
                break;
            case 0x10:
            case 0x2B:
            case 0x35:
            case 0x36:
            case 0x41:
                flags |= 1;
                result = fn_80050B08(fn_8005099C(), 0, 0x41, &intensity, (s8 *)&kind, &time, (s32 *)&flags);
                break;
            case 0x1B:
            case 0x1C:
            case 0x1D:
            case 0x24:
            case 0x25:
            case 0x26:
            case 0x2C:
            case 0x2D:
            case 0x49:
                result = fn_80050B08(fn_8005099C(), 0, level, &intensity, (s8 *)&kind, &time, (s32 *)&flags);
                break;
            case 0x11:
                intensity = 50;
                result = 0;
                kind = 2;
                time = 1500;
                break;
            case 0x12:
                intensity = 100;
                result = 0;
                kind = 2;
                time = 2000;
                break;
            case 0x1E:
            case 0x1F:
            case 0x20:
            case 0x34:
            case 0x51:
            case 0x52:
                result = fn_80049E74(object, level, &intensity, &kind, &time);
                break;
            case 0x0A:
                intensity = 100;
                result = 0x1C;
                kind = 2;
                time = 5000;
                flags |= 8;
                break;
            case 0x0B:
                intensity = 75;
                result = 0x10;
                kind = 2;
                time = 5000;
                break;
            case 0x46: {  /* sda2 word 0x00330037 copied to sp+0x20 */
                u32 pair;
                pair = lbl_8064E460;
                result = ((u16 *)&pair)[fn_801A9EF4(0, 1)];
                intensity = 40;
                kind = 4;
                time = 1000;
                break;
            }
            case 0x22:
                result = fn_801A9EF4(0x3F, 0x40);
                intensity = 90;
                kind = 4;
                time = 1500;
                break;
            case 0x23:
                if (fn_8011EB14((void *)object) == 5) {
                    result = fn_801A9EF4(0x3F, 0x40);
                    intensity = 90;
                    kind = 4;
                    time = 1500;
                } else {
                    result = fn_801A9EF4(0x3F, 0x40);
                    intensity = 70;
                    kind = 4;
                    time = 1500;
                }
                break;
            case 0x13:
                result = fn_801A9EF4(0x19F, 0x1A1);
                intensity = 70;
                kind = 2;
                time = 10000;
                break;
            case 0x21:
                result = fn_801A9EF4(0x115, 0x117);
                intensity = 60;
                kind = 4;
                time = 1500;
                break;
            case 0x57:
                if ((int)rand() < 128) {
                    result = fn_801A9EF4(0x115, 0x117);
                    intensity = 60;
                    kind = 4;
                    time = 1500;
                } else {
                    kind = 8;
                }
                break;
            case 0x37:
                intensity = 100;
                result = 0x14C;
                kind = 4;
                time = 1000;
                break;
            case 0x4B:
                intensity = 50;
                result = 0x19A;
                kind = 4;
                time = 500;
                break;
            case 0x3B:
                intensity = 100;
                result = 0xF7;
                kind = 0;
                time = 0;
                break;
            case 0x3C: {  /* 6 bytes {0xF1,0xF2,0xF5} from sda2 copied to sp+0x80 */
                u32 tri[2];
                tri[0] = lbl_8064E464;
                ((u16 *)tri)[2] = lbl_8064E468;
                result = ((u16 *)tri)[fn_801A9EF4(0, 2)];
                intensity = 100;
                kind = 0;
                time = 0;
                break;
            }
            case 0x3E: {  /* 6 bytes {0xF3,0xF4,0xF6} from sda2 copied to sp+0x78 */
                u32 tri[2];
                tri[0] = lbl_8064E46C;
                ((u16 *)tri)[2] = lbl_8064E470;
                result = ((u16 *)tri)[fn_801A9EF4(0, 2)];
                intensity = 100;
                kind = 0;
                time = 0;
                break;
            }
            }
            break;
        case 0x51:
            switch (level) {
            case 0:
                intensity = 30;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 0;
                break;
            case 1:
                intensity = 40;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 600;
                break;
            case 2:
                intensity = 70;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 1000;
                break;
            case 0x38:
                result = fn_801A9EF4(0xFA, 0xFD);
                intensity = 75;
                kind = 2;
                time = 800;
                break;
            case 0x10:
            case 0x2B:
            case 0x35:
            case 0x36:
            case 0x41:
                flags |= 1;
                result = fn_80050B08(fn_8005099C(), 0, 0x41, &intensity, (s8 *)&kind, &time, (s32 *)&flags);
                break;
            case 0x1B:
            case 0x1C:
            case 0x1D:
            case 0x24:
            case 0x25:
            case 0x26:
            case 0x2C:
            case 0x2D:
            case 0x42:
            case 0x49:
                result = fn_80050B08(fn_8005099C(), 0, level, &intensity, (s8 *)&kind, &time, (s32 *)&flags);
                break;
            case 0x11:
                intensity = 50;
                result = 0;
                kind = 2;
                time = 1500;
                break;
            case 0x12:
                intensity = 100;
                result = 0;
                kind = 2;
                time = 2000;
                break;
            case 0x1E:
            case 0x1F:
            case 0x20:
            case 0x34:
            case 0x51:
            case 0x52:
                result = fn_80049E74(object, level, &intensity, &kind, &time);
                break;
            case 0x0A:
                intensity = 100;
                result = 0x1C;
                kind = 2;
                time = 5000;
                flags |= 8;
                break;
            case 0x0B:
                intensity = 75;
                result = 0x10;
                kind = 2;
                time = 5000;
                break;
            case 0x46: {  /* sda2 word 0x00330037 copied to sp+0x1C */
                u32 pair;
                pair = lbl_8064E474;
                result = ((u16 *)&pair)[fn_801A9EF4(0, 1)];
                intensity = 40;
                kind = 4;
                time = 1000;
                break;
            }
            case 0x22:
                result = fn_801A9EF4(0x3F, 0x40);
                intensity = 90;
                kind = 4;
                time = 1500;
                break;
            case 0x23:
                if (fn_8011EB14((void *)object) == 5) {
                    result = fn_801A9EF4(0x3F, 0x40);
                    intensity = 90;
                    kind = 4;
                    time = 1500;
                } else {
                    result = fn_801A9EF4(0x3F, 0x40);
                    intensity = 70;
                    kind = 4;
                    time = 1500;
                }
                break;
            case 0x13:
                result = fn_801A9EF4(0x19F, 0x1A1);
                intensity = 70;
                kind = 2;
                time = 10000;
                break;
            case 0x21:
                result = fn_801A9EF4(0x12F, 0x134);
                intensity = 60;
                kind = 4;
                time = 1500;
                break;
            case 0x57:
                if ((int)rand() < 128) {
                    result = fn_801A9EF4(0x12F, 0x134);
                    intensity = 60;
                    kind = 4;
                    time = 1500;
                } else {
                    kind = 8;
                }
                break;
            case 0x3F:
                intensity = 100;
                result = 0x1C8;
                kind = 4;
                time = 500;
                break;
            case 0x3B:
                result = fn_801A9EF4(0x141, 0x142);
                intensity = 100;
                kind = 0;
                time = 0;
                break;
            case 0x3C: {  /* 10 bytes (5 u16) copied from pool+0x78 to sp+0xF4 */
                u32 ids[3];
                ids[0] = pool[30];
                ids[1] = pool[31];
                ((u16 *)ids)[4] = ((const u16 *)pool)[0x40];
                result = ((u16 *)ids)[fn_801A9EF4(0, 4)];
                intensity = 100;
                kind = 0;
                time = 0;
                break;
            }
            case 0x3E: {  /* 8 bytes {0x147,0x148,0x143,0x144} from sda2 copied to sp+0x70 */
                u32 quad[2];
                quad[0] = lbl_8064E478;
                quad[1] = lbl_8064E47C;
                result = ((u16 *)quad)[fn_801A9EF4(0, 3)];
                intensity = 100;
                kind = 0;
                time = 0;
                break;
            }
            }
            break;
        case 0x55:
        case 0x77:
        case 0x78:
        case 0x79:
        case 0x7A:
        case 0x8F:
            switch (level) {
            case 0:
                intensity = 30;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 0;
                break;
            case 1:
                intensity = 40;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 600;
                break;
            case 2:
                intensity = 70;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 1000;
                break;
            case 0x38:
                result = fn_801A9EF4(0xFA, 0xFD);
                intensity = 75;
                kind = 2;
                time = 800;
                break;
            case 0x10:
            case 0x2B:
            case 0x35:
            case 0x36:
            case 0x41:
                flags |= 1;
                result = fn_80050B08(fn_8005099C(), 0, 0x41, &intensity, (s8 *)&kind, &time, (s32 *)&flags);
                break;
            case 0x1B:
            case 0x1C:
            case 0x1D:
            case 0x24:
            case 0x25:
            case 0x26:
            case 0x2C:
            case 0x2D:
            case 0x49:
                result = fn_80050B08(fn_8005099C(), 0, level, &intensity, (s8 *)&kind, &time, (s32 *)&flags);
                break;
            case 0x11:
                intensity = 50;
                result = 0;
                kind = 2;
                time = 1500;
                break;
            case 0x12:
                intensity = 100;
                result = 0;
                kind = 2;
                time = 2000;
                break;
            case 0x39:
                intensity = 100;
                result = 0x19B;
                kind = 2;
                time = 3000;
                break;
            case 0x1E:
            case 0x1F:
            case 0x20:
            case 0x34:
            case 0x51:
            case 0x52:
                result = fn_80049E74(object, level, &intensity, &kind, &time);
                break;
            case 0x0A:
                intensity = 100;
                result = 0x1C;
                kind = 2;
                time = 5000;
                flags |= 8;
                break;
            case 0x0B:
                intensity = 75;
                result = 0x10;
                kind = 2;
                time = 5000;
                break;
            case 0x46: {  /* sda2 word 0x00330037 copied to sp+0x18 */
                u32 pair;
                pair = lbl_8064E480;
                result = ((u16 *)&pair)[fn_801A9EF4(0, 1)];
                intensity = 40;
                kind = 4;
                time = 1000;
                break;
            }
            case 0x22:
                result = fn_801A9EF4(0x11A, 0x11B);
                intensity = 90;
                kind = 4;
                time = 1500;
                break;
            case 0x23:
                if (fn_8011EB14((void *)object) == 5) {
                    result = fn_801A9EF4(0x119, 0x11B);
                    intensity = 90;
                    kind = 4;
                    time = 1500;
                } else {
                    result = fn_801A9EF4(0x119, 0x11B);
                    intensity = 70;
                    kind = 4;
                    time = 1500;
                }
                break;
            case 0x13:
                result = fn_801A9EF4(0x19F, 0x1A1);
                intensity = 70;
                kind = 2;
                time = 10000;
                break;
            case 0x21: {  /* sda2 word 0x0118011A copied to sp+0x14 */
                u32 pair;
                pair = lbl_8064E484;
                result = ((u16 *)&pair)[fn_801A9EF4(0, 1)];
                intensity = 60;
                kind = 4;
                time = 1500;
                break;
            }
            case 0x37:
                intensity = 80;
                result = 0xD6;
                kind = 4;
                time = 1000;
                break;
            case 0x4E:
            case 0x4F:
                kind = 8;
                break;
            case 0x3F:
                intensity = 100;
                result = 0x18D;
                kind = 4;
                time = 1000;
                break;
            case 0x4A:
                intensity = 75;
                result = 0x1CD;
                kind = 2;
                time = 600;
                break;
            case 0x3D:
            {
                int phase = fn_8006BE44();
                result = 0x256;
                if (phase >= 2) {
                    result = 0x257;
                }
            }
                intensity = 75;
                kind = 0;
                time = 0;
                break;
            case 0x3B:
                result = fn_801A9EF4(0x108, 0x109);
                intensity = 100;
                kind = 0;
                time = 0;
                break;
            case 0x3C: {  /* 8 bytes {0x102,0x104,0x105,0x107} from sda2 copied to sp+0x68 */
                u32 quad[2];
                quad[0] = lbl_8064E488;
                quad[1] = lbl_8064E48C;
                result = ((u16 *)quad)[fn_801A9EF4(0, 3)];
                intensity = 100;
                kind = 0;
                time = 0;
                break;
            }
            case 0x3E: {  /* 6 bytes {0x103,0x106,0x10A} from sda2 copied to sp+0x60 */
                u32 tri[2];
                tri[0] = lbl_8064E490;
                ((u16 *)tri)[2] = lbl_8064E494;
                result = ((u16 *)tri)[fn_801A9EF4(0, 2)];
                intensity = 100;
                kind = 0;
                time = 0;
                break;
            }
            }
            break;
        case 0x1:
        case 0x6:
        case 0x7:
        case 0x8:
            if (fn_8006D2C8(fn_8006D444(fn_80204844(fn_80201B9C(), 0x20)), 0x13) != 0) {
                flags |= 0x40;
            }
            switch (level) {
            case 0x21:
                if (fn_80066BB8((void *)object, 0) != 0) {
                    result = fn_801A9EF4(0x2C8, 0x2C9);
                    intensity = 85;
                    kind = 2;
                    time = 5000;
                } else {
                    kind = 8;
                }
                break;
            case 0x1:
                intensity = 80;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 1500;
                break;
            case 0x2:
                intensity = 100;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 2000;
                break;
            case 0x13:
                result = fn_801A9EF4(0x19F, 0x1A1);
                intensity = 100;
                kind = 2;
                time = 10000;
                break;
            case 0x16: {  /* 3 words copied from pool+0x84 to sp+0xE8 */
                s32 ids[3];
                ids[0] = pool[0x84 / 4];
                ids[1] = pool[0x88 / 4];
                ids[2] = pool[0x8C / 4];
                result = fn_801A9F44(3, ids);
                intensity = 85;
                kind = 2;
                time = 1500;
                break;
            }
            case 0x15:
                intensity = 90;
                result = 0x16;
                kind = 2;
                time = 2000;
                break;
            case 0x19:
                intensity = 100;
                result = 0x1A3;
                kind = 2;
                time = 1500;
                break;
            case 0x18:
                if (fn_80066BB8((void *)object, 0) != 0) {
                    result = fn_801A9EF4(0x19, 0x1B);
                    intensity = 100;
                    kind = 2;
                    time = 1500;
                } else {
                    result = fn_801A9EF4(0x19F, 0x1A1);
                    intensity = 100;
                    kind = 2;
                    time = 10000;
                }
                break;
            case 0xB:
                intensity = 60;
                result = 0x10;
                kind = 2;
                time = 2000;
                break;
            case 0xA:
            case 0x33:
                result = fn_801A9EF4(0x13, 0x15);
                intensity = 60;
                kind = 2;
                time = 2000;
                break;
            case 0x17:
                result = fn_801A9EF4(0x17, 0x18);
                intensity = 70;
                kind = 2;
                time = 5000;
                break;
            case 0x1A:
                intensity = 100;
                result = 0x3B;
                kind = 3;
                time = 5000;
                break;
            case 0x30:
                intensity = 90;
                result = 0xC0;
                kind = 2;
                time = 5000;
                break;
            case 0x31:
                intensity = 55;
                result = 0xBD;
                kind = 2;
                time = 5000;
                break;
            case 0x35:
                intensity = 100;
                result = 0x19E;
                kind = 2;
                time = 3000;
                break;
            case 0x29:
                intensity = 100;
                result = 0x1;
                kind = 2;
                time = 3000;
                break;
            case 0x2A:
                result = fn_801A9EF4(0x17, 0x18);
                intensity = 127;
                kind = 2;
                time = 5000;
                break;
            case 0x3F:
            case 0x4A:
                result = fn_801A9EF4(0x17, 0x18);
                intensity = 100;
                kind = 2;
                time = 5000;
                break;
            case 0x4E:
            case 0x4F:
                if ((int)rand() < 51) {
                    result = fn_801A9EF4(0x17, 0x18);
                    intensity = 90;
                    kind = 2;
                    time = 5000;
                } else {
                    kind = 8;
                }
                break;
            }
            break;
        case 0x2:
        case 0xF:
        case 0x10:
            switch (level) {
            case 0x2:
                result = fn_8004998C((int)object, &intensity, &flags);
                intensity = 120;
                kind = 2;
                time = 1500;
                break;
            case 0x1:
                result = fn_8004998C((int)object, &intensity, &flags);
                intensity = 100;
                kind = 2;
                time = 1500;
                break;
            case 0x13:
                if (lbl_8064C83C < lbl_8064D5A8 - 10 || lbl_8064C83C > lbl_8064D5A8) {
                    lbl_8064C83C = lbl_8064D5A8;
                    intensity = 70;
                    result = 0x1F0;
                    kind = 2;
                    time = 10000;
                } else {
                    kind = 8;
                }
                break;
            case 0x16: {  /* sdata2 words lbl_8064E498 (0xB8), lbl_8064E49C (0xD3) copied to sp+0x58 */
                s32 ids[2];
                ids[0] = lbl_8064E498;
                ids[1] = lbl_8064E49C;
                result = fn_801A9F44(2, ids);
                intensity = 80;
                kind = 2;
                time = 1500;
                break;
            }
            case 0x18:
            case 0x19:
                intensity = 80;
                result = 0xB7;
                kind = 2;
                time = 1500;
                break;
            case 0xB:
                intensity = 127;
                result = 0x10;
                kind = 2;
                time = 2000;
                break;
            case 0x33:
                intensity = 80;
                result = 0xD5;
                kind = 2;
                time = 2000;
                break;
            case 0xA:
                intensity = 127;
                result = 0xD4;
                kind = 2;
                time = 2000;
                break;
            case 0x17:
                intensity = 60;
                result = 0xB7;
                kind = 2;
                time = 5000;
                break;
            case 0x29:
                intensity = 127;
                result = 0xB6;
                kind = 3;
                time = 5000;
                break;
            case 0x2A:
                intensity = 127;
                result = 0xB5;
                kind = 2;
                time = 5000;
                lbl_8063D400[2] -= lbl_8064E4B0;
                break;
            case 0x1E:
            case 0x51:
                result = fn_801A9EF4(0x1F6, 0x1F7);
                intensity = 70;
                kind = 2;
                time = 3000;
                break;
            case 0x1F:
            case 0x52:
                result = fn_801A9EF4(0x1F8, 0x1F9);
                intensity = 70;
                kind = 2;
                time = 3000;
                break;
            case 0x3F:
                result = fn_801A9EF4(0x1FA, 0x1FC);
                intensity = 85;
                kind = 2;
                time = 5000;
                break;
            case 0x4A:
                result = fn_801A9EF4(0x1FA, 0x1FC);
                intensity = 85;
                kind = 2;
                time = 5000;
                break;
            case 0x4E:
            case 0x4F:
                if ((int)rand() < 25) {
                    result = fn_801A9EF4(0x1FA, 0x1FC);
                    intensity = 70;
                    kind = 2;
                    time = 5000;
                } else {
                    kind = 8;
                }
                break;
            }
            break;
        case 0x3:
        case 0x47:
        case 0x48:
            switch (level) {
            case 0xA:
            case 0x21:
            case 0x33:
                intensity = 100;
                result = 0x15B;
                kind = 2;
                time = 1500;
                break;
            case 0x1:
                result = fn_801A9EF4(0x15E, 0x160);
                intensity = 80;
                kind = 2;
                time = 1500;
                break;
            case 0x2:
                result = fn_801A9EF4(0x15E, 0x160);
                intensity = 100;
                kind = 2;
                time = 1500;
                break;
            case 0x41:
                intensity = 100;
                result = 0x15C;
                kind = 2;
                time = 1500;
                break;
            case 0x2A:
                intensity = 100;
                result = 0x159;
                kind = 2;
                time = 1500;
                break;
            case 0x43:
                intensity = 100;
                result = 0x15A;
                kind = 2;
                time = 1500;
                break;
            case 0x13:
                result = fn_801A9EF4(0x19F, 0x1A1);
                intensity = 90;
                kind = 2;
                time = 10000;
                break;
            case 0x18:
            case 0x19:
                intensity = 80;
                result = 0x11;
                kind = 2;
                time = 1000;
                break;
            case 0xB:
            case 0x30:
                intensity = 100;
                result = 0x15D;
                kind = 2;
                time = 1500;
                break;
            case 0x17:
                intensity = 100;
                result = 0x158;
                kind = 2;
                time = 1500;
                break;
            case 0x3F:
                intensity = 80;
                result = 0x158;
                kind = 2;
                time = 1500;
                break;
            case 0x4A:
                intensity = 80;
                result = 0x264;
                kind = 2;
                time = 1500;
                break;
            case 0x4E:
            case 0x4F:
                if ((int)rand() < 25) {
                    intensity = 50;
                    result = 0x264;
                    kind = 2;
                    time = 1500;
                } else if ((int)rand() < 25) {
                    intensity = 50;
                    result = 0x265;
                    kind = 2;
                    time = 1500;
                } else {
                    kind = 8;
                }
                break;
            }
            break;
        case 0x42:
        case 0x43:
        case 0x44:
            switch (level) {
            case 0x1:
            case 0x2:
                intensity = 75;
                result = fn_801A9EF4(0x204, 0x207);
                kind = 2;
                time = 600;
                break;
            case 0xA:
                flags |= 8;
                intensity = 120;
                result = 0x5E;
                kind = 2;
                time = 1500;
                break;
            case 0x21:
            case 0x29:
                intensity = 100;
                result = 0x20E;
                kind = 2;
                time = 1000;
                break;
            case 0xB:
                intensity = 100;
                result = 0x20B;
                kind = 2;
                time = 1000;
                break;
            case 0x35:
            case 0x36:
            case 0x41:
                intensity = 100;
                result = 0x20D;
                kind = 2;
                time = 600;
                break;
            case 0x13:
                result = fn_801A9EF4(0x19F, 0x1A1);
                intensity = 90;
                kind = 2;
                time = 10000;
                break;
            case 0x17:
                intensity = 100;
                result = 0x20F;
                kind = 2;
                time = 5000;
                break;
            case 0x32:
                result = fn_801A9EF4(0xC4, 0xC7);
                intensity = 80;
                kind = 2;
                time = 5000;
                break;
            case 0x3F:
                intensity = 80;
                result = 0x20F;
                kind = 2;
                time = 5000;
                break;
            case 0x4E:
            case 0x4F:
                if ((int)rand() < 25) {
                    intensity = 70;
                    result = 0x20F;
                    kind = 2;
                    time = 5000;
                } else {
                    kind = 8;
                }
                break;
            }
            break;
        case 0x4:
        case 0x1D:
        case 0x1E:
            switch (level) {
            case 0x1:
                intensity = 75;
                result = fn_801A9EF4(0x204, 0x207);
                kind = 2;
                time = 600;
                break;
            case 0xA:
                intensity = 100;
                result = 0x20A;
                kind = 2;
                time = 1000;
                break;
            case 0x33:
                intensity = 80;
                result = 0x20A;
                kind = 2;
                time = 2000;
                break;
            case 0xB:
                intensity = 100;
                result = 0x20B;
                kind = 2;
                time = 1000;
                break;
            case 0x13:
                result = fn_801A9EF4(0x19F, 0x1A1);
                intensity = 90;
                kind = 2;
                time = 10000;
                break;
            case 0x21:
                intensity = 110;
                result = fn_801A9EF4(0x208, 0x209);
                kind = 2;
                time = 1000;
                break;
            case 0x40:
                intensity = 100;
                result = 0x147;
                kind = 2;
                time = 600;
                break;
            case 0x17:
                intensity = 100;
                result = 0x153;
                kind = 2;
                time = 600;
                break;
            case 0x41:
                intensity = 100;
                result = 0x154;
                kind = 2;
                time = 600;
                break;
            case 0x3F:
                intensity = 80;
                result = 0x153;
                kind = 2;
                time = 600;
                break;
            case 0x4E:
            case 0x4F:
                if ((int)rand() < 25) {
                    intensity = 70;
                    result = 0x153;
                    kind = 2;
                    time = 5000;
                } else {
                    kind = 8;
                }
                break;
            }
            break;
        case 0x1C:
        case 0x4F:
        case 0x50:
            switch (level) {
            case 0x13:
                result = fn_801A9EF4(0x2AD, 0x2AE);
                intensity = 100;
                kind = 2;
                time = 10000;
                break;
            case 0xA:
            case 0xB:
                intensity = 100;
                result = 0x22D;
                kind = 2;
                time = 1500;
                break;
            case 0x4B:
                intensity = 50;
                result = 0x12D;
                kind = 2;
                time = 1500;
                break;
            case 0x4C:
                intensity = 90;
                result = 0x12B;
                kind = 2;
                time = 1500;
                break;
            case 0x1:
                intensity = 70;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 600;
                break;
            case 0x17:
                result = fn_801A9EF4(0x12B, 0x12D);
                intensity = 100;
                kind = 2;
                time = 1500;
                break;
            case 0x41:
                intensity = 100;
                result = 0x167;
                kind = 2;
                time = 1500;
                break;
            case 0x29:
                result = fn_801A9EF4(0x12B, 0x12D);
                intensity = 120;
                kind = 2;
                time = 1500;
                break;
            case 0x3F:
                result = fn_801A9EF4(0x12B, 0x12D);
                intensity = 80;
                kind = 2;
                time = 1500;
                break;
            case 0x4A:
                result = fn_801A9EF4(0x12B, 0x12D);
                intensity = 60;
                kind = 2;
                time = 1500;
                break;
            case 0x4E:
                if ((int)rand() < 12) {
                    result = fn_801A9EF4(0x12B, 0x12D);
                    intensity = 70;
                    kind = 2;
                    time = 1500;
                } else {
                    kind = 8;
                }
                break;
            case 0x4F:
                if ((int)rand() < 25) {
                    result = fn_801A9EF4(0x12B, 0x12D);
                    intensity = 70;
                    kind = 2;
                    time = 1500;
                } else {
                    kind = 8;
                }
                break;
            }
            break;
        case 0x1F:
            switch (level) {
            case 0xA:
                flags |= 8;
                intensity = 120;
                result = 0x5B;
                kind = 2;
                time = 1500;
                break;
            case 0x1:
                intensity = 120;
                result = 0x22E;
                kind = 2;
                time = 1500;
                break;
            case 0xB:
                intensity = 100;
                result = 0x230;
                kind = 5;
                time = 1500;
                break;
            case 0x35:
            case 0x41:
                intensity = 120;
                result = 0x16B;
                kind = 2;
                time = 1500;
                break;
            case 0x13:
                result = fn_801A9EF4(0x19F, 0x1A1);
                intensity = 70;
                kind = 2;
                time = 10000;
                break;
            case 0x21:
                intensity = 120;
                result = 0x16C;
                kind = 2;
                time = 1500;
                break;
            case 0x17:
                intensity = 100;
                result = 0x16A;
                kind = 2;
                time = 1500;
                break;
            case 0x3F:
                intensity = 80;
                result = 0x16A;
                kind = 2;
                time = 1500;
                break;
            case 0x4E:
            case 0x4F:
                if ((int)rand() < 51) {
                    intensity = 100;
                    result = 0x16A;
                    kind = 2;
                    time = 5000;
                } else {
                    kind = 8;
                }
                break;
            case 0x34:
                break;
            }
            break;
        case 0x4D:
            switch (level) {
            case 0xA:
                flags |= 8;
                intensity = 120;
                result = 0x5C;
                kind = 2;
                time = 1500;
                break;
            case 0x1:
                intensity = 70;
                result = 0x22E;
                kind = 2;
                time = 1500;
                break;
            case 0xB:
                intensity = 100;
                result = 0x230;
                kind = 5;
                time = 1500;
                break;
            case 0x41:
                intensity = 100;
                result = 0x16B;
                kind = 2;
                time = 1500;
                break;
            case 0x13:
                result = fn_801A9EF4(0x19F, 0x1A1);
                intensity = 70;
                kind = 2;
                time = 10000;
                break;
            case 0x21:
                intensity = 120;
                result = 0x236;
                kind = 2;
                time = 1500;
                break;
            case 0x17:
                intensity = 100;
                result = 0x16A;
                kind = 2;
                time = 1500;
                break;
            case 0x3F:
                result = fn_801A9EF4(0x233, 0x234);
                intensity = 100;
                kind = 2;
                time = 1500;
                break;
            case 0x4E:
            case 0x4F:
                if ((int)rand() < 51) {
                    intensity = 100;
                    result = 0x234;
                    kind = 2;
                    time = 5000;
                } else {
                    kind = 8;
                }
                break;
            case 0x40: /* NOTE: explicit empty case (cmpwi r25,0x40; beq exit); body position unknown */
                break;
            }
            break;
        case 0x4E:
            switch (level) {
            case 0xA:
                flags |= 8;
                intensity = 120;
                result = 0x5D;
                kind = 2;
                time = 1500;
                break;
            case 0x1:
                intensity = 100;
                result = 0x22E;
                kind = 2;
                time = 1500;
                break;
            case 0xB:
                intensity = 100;
                result = 0x230;
                kind = 5;
                time = 1500;
                break;
            case 0x41:
                intensity = 100;
                result = 0x16B;
                kind = 2;
                time = 1500;
                break;
            case 0x13:
                result = fn_801A9EF4(0x19F, 0x1A1);
                intensity = 70;
                kind = 2;
                time = 10000;
                break;
            case 0x21:
                intensity = 120;
                result = 0x235;
                kind = 2;
                time = 1500;
                break;
            case 0x17:
                intensity = 100;
                result = 0x16A;
                kind = 2;
                time = 1500;
                break;
            case 0x3F:
                intensity = 80;
                result = 0x237;
                kind = 2;
                time = 1500;
                break;
            case 0x4A:
                intensity = 100;
                result = 0x22F;
                kind = 2;
                time = 1500;
                break;
            case 0x4E:
            case 0x4F:
                if ((int)rand() < 51) {
                    intensity = 100;
                    result = 0x237;
                    kind = 2;
                    time = 5000;
                } else {
                    kind = 8;
                }
                break;
            case 0x40: /* NOTE: explicit empty case (cmpwi r25,0x40; beq exit); body position unknown */
                break;
            }
            break;
        case 0x54:
            switch (level) {
            case 0x21:
                result = fn_801A9EF4(0x2B9, 0x2BB);
                intensity = 100;
                kind = 5;
                time = 10000;
                break;
            case 0x29:
                intensity = 100;
                result = 0x243;
                kind = 5;
                time = 1500;
                break;
            case 0xA:
                intensity = 127;
                result = 0x248;
                kind = 2;
                time = 1500;
                break;
            case 0x16:
            case 0x41:
                intensity = 127;
                result = 0x2C2;
                kind = 5;
                time = 1500;
                break;
            case 0x2A:
                intensity = 100;
                result = 0x23D;
                kind = 2;
                time = 1500;
                break;
            case 0x43:
            case 0x4B:
                intensity = 100;
                result = 0x2C3;
                kind = 5;
                time = 1500;
                break;
            case 0x13:
                result = fn_801A9EF4(0x19F, 0x1A1);
                intensity = 100;
                kind = 2;
                time = 10000;
                break;
            case 0x3F:
                intensity = 80;
                result = 0x244;
                kind = 5;
                time = 1500;
                break;
            case 0x4A:
                intensity = 80;
                result = 0x245;
                kind = 5;
                time = 1500;
                break;
            case 0x4E:
            case 0x4F:
                if ((int)rand() < 25) {
                    intensity = 80;
                    result = 0x246;
                    kind = 5;
                    time = 1500;
                } else {
                    kind = 8;
                }
                break;
            }
            break;
        case 0x52:
            switch (level) {
            case 0x21:
                result = fn_801A9EF4(0x2BF, 0x2C1);
                intensity = 100;
                kind = 5;
                time = 10000;
                break;
            case 0xA:
                intensity = 127;
                result = 0x262;
                kind = 2;
                time = 1500;
                break;
            case 0x41:
                intensity = 127;
                result = 0x25B;
                kind = 2;
                time = 1500;
                break;
            case 0x2A:
                intensity = 100;
                result = 0x257;
                kind = 2;
                time = 1500;
                break;
            case 0x13:
                result = fn_801A9EF4(0x19F, 0x1A1);
                intensity = 100;
                kind = 2;
                time = 10000;
                break;
            case 0x3F:
                intensity = 80;
                result = 0x25F;
                kind = 2;
                time = 1500;
                break;
            case 0x4A:
                intensity = 80;
                result = 0x260;
                kind = 2;
                time = 1500;
                break;
            case 0x4E:
            case 0x4F:
                if ((int)rand() < 25) {
                    intensity = 80;
                    result = 0x261;
                    kind = 2;
                    time = 1500;
                } else {
                    kind = 8;
                }
                break;
            }
            break;
        case 0x53:
            switch (level) {
            case 0x21:
                result = fn_801A9EF4(0x2BC, 0x2BE);
                intensity = 100;
                kind = 5;
                time = 10000;
                break;
            case 0xA:
                intensity = 127;
                result = 0x256;
                kind = 2;
                time = 1500;
                break;
            case 0x1:
                intensity = 80;
                result = 0x169;
                kind = 2;
                time = 1500;
                break;
            case 0x41:
                intensity = 127;
                result = 0x255;
                kind = 2;
                time = 1500;
                break;
            case 0x2A:
                intensity = 100;
                result = 0x251;
                kind = 2;
                time = 1500;
                break;
            case 0x43:
                intensity = 100;
                result = 0x249;
                kind = 2;
                time = 1500;
                break;
            case 0x13:
                result = fn_801A9EF4(0x19F, 0x1A1);
                intensity = 100;
                kind = 2;
                time = 10000;
                break;
            case 0x3F:
                intensity = 80;
                result = 0x252;
                kind = 2;
                time = 1500;
                break;
            case 0x4A:
                intensity = 80;
                result = 0x253;
                kind = 2;
                time = 1500;
                break;
            case 0x4E:
            case 0x4F:
                if ((int)rand() < 25) {
                    intensity = 80;
                    result = 0x254;
                    kind = 2;
                    time = 1500;
                } else {
                    kind = 8;
                }
                break;
            case 0xB:
            case 0x40:
                break;
            }
            break;
        case 0x56:
            switch (level) {
            case 0x0:
                intensity = 20;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 0;
                break;
            case 0x1:
                intensity = 30;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 600;
                break;
            case 0x2:
                intensity = 60;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 1000;
                break;
            case 0x14:
                result = fn_801A9EF4(0xB, 0xF);
                intensity = 100;
                kind = 2;
                time = 0;
                break;
            case 0x2A:
                intensity = 100;
                result = 0x213;
                kind = 2;
                time = 1000;
                break;
            case 0x3F:
                result = fn_801A9EF4(0x210, 0x211);
                intensity = 120;
                kind = 5;
                time = 1000;
                break;
            case 0x10:
            case 0x2B:
            case 0x35:
            case 0x36:
            case 0x41:
                flags |= 1;
                result = fn_80050B08(0xBA, 0, 0x41, &intensity, (s8 *)&kind, &time, (s32 *)&flags);
                break;
            case 0x1B:
            case 0x1C:
            case 0x1D:
            case 0x24:
            case 0x25:
            case 0x26:
            case 0x2C:
            case 0x2D:
            case 0x49:
                result = fn_80050B08(0xBA, 0, level, &intensity, (s8 *)&kind, &time, (s32 *)&flags);
                break;
            case 0x1E:
            case 0x1F:
            case 0x20:
            case 0x34:
            case 0x51:
            case 0x52:
                result = fn_80049E74(object, level, &intensity, &kind, &time);
                break;
            case 0xA:
            case 0xB:
                intensity = 75;
                result = 0x10;
                kind = 2;
                time = 5000;
                break;
            case 0x46: {  /* sda2 word 0x00330037 copied to sp+0x10, indexed by random 0..1 */
                u32 pair;
                pair = lbl_8064E4A0;
                result = ((u16 *)&pair)[fn_801A9EF4(0, 1)];
                intensity = 40;
                kind = 2;
                time = 1000;
                break;
            }
            case 0x22:
            case 0x23:
                result = fn_801A9EF4(0x3F, 0x40);
                intensity = 70;
                kind = 2;
                time = 1500;
                break;
            case 0x21: {  /* 5 words copied from pool+0x90 to sp+0x164 */
                s32 ids[5];
                ids[0] = pool[36];
                ids[1] = pool[37];
                ids[2] = pool[38];
                ids[3] = pool[39];
                ids[4] = pool[40];
                result = fn_801A9F44(5, ids);
                intensity = 75;
                kind = 2;
                time = 1500;
                break;
            }
            case 0x17:
                result = fn_801A9EF4(0x17, 0x18);
                intensity = 30;
                kind = 2;
                time = 5000;
                break;
            case 0x13:
                result = fn_801A9EF4(0x17, 0x18);
                intensity = 60;
                kind = 2;
                time = 10000;
                break;
            case 0x4B:
                intensity = 100;
                result = 0x1CE;
                kind = 2;
                time = 600;
                break;
            case 0x37:
                intensity = 90;
                result = 0xD6;
                kind = 4;
                time = 1000;
                break;
            case 0x4E:
            case 0x4F:
                if ((int)rand() < 51) {
                    result = fn_801A9EF4(0x17, 0x18);
                    intensity = 90;
                    kind = 2;
                    time = 5000;
                } else {
                    kind = 8;
                }
                break;
            }
            break;
        case 0x63:
            switch (level) {
            case 0x3F:
                result = fn_801A9EF4(0x138, 0x139);
                intensity = 50;
                kind = 2;
                time = 1500;
                break;
            }
            break;
        case 0x57:
        case 0x58:
        case 0x66:
        case 0x67:
        case 0x6A:
        case 0x6C:
        case 0x6D:
        case 0x75:
        case 0x7C:
        case 0x83:
        case 0x86:
        case 0x9D:
        case 0x9E:
        case 0x9F:
            switch (level) {
            case 0x17:
                intensity = 100;
                result = 0x273;
                kind = 2;
                time = 5000;
                break;
            case 0x1:
                intensity = 55;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 600;
                break;
            case 0x2:
                intensity = 75;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 600;
                break;
            case 0xB:
                intensity = 75;
                result = 0x10;
                kind = 2;
                time = 5000;
                break;
            case 0x13:
                result = fn_801A9EF4(0x19F, 0x1A1);
                intensity = 70;
                kind = 2;
                time = 10000;
                break;
            case 0x19:
                intensity = 100;
                result = 0x1A3;
                kind = 2;
                time = 1500;
                break;
            case 0x18:
                intensity = 80;
                result = 0x11;
                kind = 2;
                time = 1000;
                break;
            case 0x21:
                result = fn_801A9EF4(0x11C, 0x11E);
                intensity = 60;
                kind = 2;
                time = 1500;
                break;
            case 0x46: {  /* sda word lbl_8064E4A4 copied to sp+0xC, indexed by random 0..1 */
                u32 pair;
                pair = lbl_8064E4A4;
                result = ((u16 *)&pair)[fn_801A9EF4(0, 1)];
                intensity = 40;
                kind = 2;
                time = 1000;
                break;
            }
            case 0x4B:
                intensity = 50;
                result = 0x19A;
                kind = 4;
                time = 500;
                break;
            case 0xA:
                if (fn_800CAF7C(fn_80201BD0((void *)object)) != 0) {
                    result = fn_801A9EF4(0x21B, 0x21C);
                } else {
                    result = fn_801A9EF4(0xC6, 0xC7);
                }
                intensity = 90;
                kind = 2;
                time = 2000;
                break;
            }
            break;
        case 0x69:
        case 0x6B:
        case 0x74:
        case 0x85:
        case 0x9A:
            switch (level) {
            case 0x17:
                intensity = 100;
                result = 0x273;
                kind = 2;
                time = 5000;
                break;
            case 0x1:
                intensity = 40;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 600;
                break;
            case 0xB:
                intensity = 75;
                result = 0x10;
                kind = 2;
                time = 5000;
                break;
            case 0x13:
                result = fn_801A9EF4(0x19F, 0x1A1);
                intensity = 70;
                kind = 2;
                time = 10000;
                break;
            case 0x19:
                intensity = 100;
                result = 0x1A3;
                kind = 2;
                time = 1500;
                break;
            case 0x18:
                intensity = 70;
                result = 0x11;
                kind = 2;
                time = 1000;
                break;
            case 0x21:
                result = fn_801A9EF4(0x11F, 0x120);
                intensity = 60;
                kind = 2;
                time = 1500;
                break;
            case 0x4B:
                intensity = 50;
                result = 0x19A;
                kind = 4;
                time = 500;
                break;
            case 0xA:
                if (fn_800CAF7C(fn_80201BD0((void *)object)) != 0) {
                    result = fn_801A9EF4(0x219, 0x21A);
                } else {
                    result = fn_801A9EF4(0xC6, 0xC7);
                }
                intensity = 90;
                kind = 2;
                time = 2000;
                break;
            }
            break;
        case 0x76:
            switch (level) {
            case 0x1:
                intensity = 55;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 600;
                break;
            case 0x2:
                intensity = 75;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 600;
                break;
            case 0xB:
                intensity = 75;
                result = 0x10;
                kind = 2;
                time = 5000;
                break;
            case 0x13:
                result = fn_801A9EF4(0x19F, 0x1A1);
                intensity = 70;
                kind = 2;
                time = 10000;
                break;
            case 0x19:
                intensity = 100;
                result = 0x1A3;
                kind = 2;
                time = 1500;
                break;
            case 0x18:
                intensity = 80;
                result = 0x11;
                kind = 2;
                time = 1000;
                break;
            case 0x21:
                result = fn_801A9EF4(0x11C, 0x11E);
                intensity = 60;
                kind = 2;
                time = 1500;
                break;
            case 0x17:
                result = fn_801A9EF4(0x17, 0x18);
                intensity = 70;
                kind = 2;
                time = 5000;
                break;
            case 0x30:
                intensity = 90;
                result = 0xC0;
                kind = 2;
                time = 5000;
                break;
            case 0x15:
                intensity = 90;
                result = 0x16;
                kind = 2;
                time = 2000;
                break;
            case 0xA:
                result = fn_801A9EF4(0x13, 0x15);
                intensity = 60;
                kind = 2;
                time = 2000;
                break;
            }
            break;
        case 0x6E:
        case 0x6F:
            if (lbl_8064D5A8 != lbl_8064C840) {
                lbl_8064C840 = lbl_8064D5A8;
                switch (level) {
                case 0x48:
                    intensity = 100;
                    result = 0x1D3;
                    kind = 2;
                    time = 2000;
                    break;
                case 0x41:
                    intensity = 100;
                    result = 0x156;
                    kind = 2;
                    time = 3000;
                    break;
                case 0x42:
                    intensity = 100;
                    result = 0x157;
                    kind = 2;
                    time = 3000;
                    break;
                }
            } else {
                kind = 8;
            }
            break;
        case 0x59:
        case 0x5A:
        case 0x5B:
            switch (level) {
            case 0x41:
                intensity = 80;
                result = 0x1A2;
                kind = 2;
                time = 5000;
                break;
            }
            break;
        case 0x7E:
            switch (level) {
            case 0x1E:
            case 0x1F:
            case 0x20:
            case 0x34:
            case 0x51:
            case 0x52:
                kind = 8;
                break;
            case 0x1:
                intensity = 80;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 1500;
                break;
            case 0x2:
                intensity = 100;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 2000;
                break;
            case 0xB:
                intensity = 127;
                result = 0x10;
                kind = 2;
                time = 2000;
                break;
            case 0x14:
                result = fn_801A9EF4(0xB, 0xF);
                intensity = 50;
                kind = 2;
                time = 0;
                break;
            case 0x10:
            case 0x35:
            case 0x36:
            case 0x41:
                flags |= 1;
                result = fn_80050B08(1, 0, 0x41, &intensity, (s8 *)&kind, &time, (s32 *)&flags);
                break;
            case 0x13:
            case 0x21:
                result = fn_801A9EF4(0x19F, 0x1A1);
                intensity = 100;
                kind = 2;
                time = 10000;
                break;
            case 0xA:
            case 0x33:
                result = fn_801A9EF4(0x13, 0x15);
                intensity = 60;
                kind = 2;
                time = 2000;
                break;
            case 0x17:
                result = fn_801A9EF4(0x17, 0x18);
                intensity = 70;
                kind = 2;
                time = 5000;
                break;
            case 0x23:
                result = fn_801A9EF4(0x3F, 0x40);
                intensity = 50;
                kind = 2;
                time = 1500;
                break;
            }
            break;
        case 0x89:
            switch (level) {
            case 0x1:
                intensity = 80;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 1500;
                break;
            case 0x2:
                intensity = 100;
                result = fn_8004998C((int)object, &intensity, &flags);
                kind = 2;
                time = 2000;
                break;
            case 0xB:
                intensity = 75;
                result = 0x10;
                kind = 2;
                time = 5000;
                break;
            case 0x10:
            case 0x35:
            case 0x36:
            case 0x41:
            case 0x47:
                flags |= 1;
                result = fn_80050B08(0x6E, 0, 0x41, &intensity, (s8 *)&kind, &time, (s32 *)&flags);
                break;
            case 0x1E:
            case 0x1F:
            case 0x20:
            case 0x34:
            case 0x51:
            case 0x52:
                result = fn_80049E74(object, level, &intensity, &kind, &time);
                break;
            case 0x23:
            case 0x46: {  /* 2 sda words lbl_8064E4A8/lbl_8064E4AC copied to sp+0x50 */
                s32 ids[2];
                ids[0] = lbl_8064E4A8;
                ids[1] = lbl_8064E4AC;
                result = fn_801A9F44(2, ids);
                intensity = 85;
                kind = 2;
                time = 1500;
                break;
            }
            case 0x13:
                result = fn_801A9EF4(0x19F, 0x1A1);
                intensity = 100;
                kind = 2;
                time = 10000;
                break;
            case 0x33:
                result = fn_801A9EF4(0x13, 0x15);
                intensity = 60;
                kind = 2;
                time = 2000;
                break;
            case 0x17:
                intensity = 70;
                result = 0x273;
                kind = 2;
                time = 5000;
                break;
            case 0x21:
                result = fn_801A9EF4(0x2C8, 0x2C9);
                intensity = 85;
                kind = 2;
                time = 5000;
                break;
            case 0x4F:
                if ((int)rand() < 51) {
                    result = fn_80049E74(object, 0x1E, &intensity, &kind, &time);
                    intensity = 90;
                } else {
                    kind = 8;
                }
                break;
            }
            break;
        case 0x60:
        case 0x61:
        case 0x62:
            switch (level) {
            case 0x13:
                result = fn_801A9EF4(0x28, 0x32);
                intensity = 100;
                kind = 2;
                time = 5000;
                break;
            }
            break;
        }
    } else if (state == 4) {
    } else if (state == 3) {
        switch (type) {
        case 0x14:
            switch (level) {
            case 0x3F:
                intensity = 60;
                result = 0x144;
                kind = 2;
                time = 5000;
                break;
            case 0x4A:
                intensity = 60;
                result = 0x145;
                kind = 2;
                time = 5000;
                break;
            }
            break;
        case 0x5D:
        case 0x90:
        case 0x92:
        case 0x97:
            switch (level) {
            case 0x0B:
            case 0x4B:
                intensity = 100;
                result = 0x1D9;
                kind = 2;
                time = 5000;
                flags |= 0x10;
                break;
            }
            break;
        case 0x91:
        case 0x98:
        case 0x99:
            switch (level) {
            case 0x0B:
            case 0x4B:
                intensity = 100;
                result = 0x1DA;
                kind = 2;
                time = 5000;
                flags |= 0x10;
                break;
            }
            break;
        case 0x58:
        case 0x5A:
            switch (level) {
            case 0x0B:
            case 0x4B:
                intensity = 100;
                result = 0x211;
                kind = 2;
                time = 5000;
                flags |= 0x10;
                break;
            }
            break;
        case 0x43:
            switch (level) {
            case 0x0B:
            case 0x4B:
                intensity = 100;
                result = 0x1D1;
                kind = 2;
                time = 5000;
                flags |= 0x10;
                break;
            }
            break;
        case 0x54:
            switch (level) {
            case 0x0B:
            case 0x4B:
                intensity = 100;
                result = 0x1CE;
                kind = 2;
                time = 5000;
                flags |= 0x10;
                break;
            }
            break;
        case 0x3D:
            switch (level) {
            case 0x0B:
            case 0x4B:
                intensity = 100;
                result = 0x25A;
                kind = 2;
                time = 5000;
                flags |= 0x10;
                break;
            }
            break;
        case 0x52:
        case 0x55:
            switch (level) {
            case 0x0B:
            case 0x4B:
                intensity = 100;
                result = 0x25B;
                kind = 2;
                time = 5000;
                flags |= 0x10;
                break;
            }
            break;
        case 0x53:
            switch (level) {
            case 0x0B:
            case 0x4B:
                intensity = 100;
                result = 0x25D;
                kind = 2;
                time = 5000;
                flags |= 0x10;
                break;
            }
            break;
        case 0x93:
            switch (level) {
            case 0x0B:
            case 0x4B:
                intensity = 100;
                result = 0x25E;
                kind = 2;
                time = 5000;
                flags |= 0x10;
                break;
            }
            break;
        case 0x49:
            switch (level) {
            case 0x0B:
            case 0x4B:
                intensity = 100;
                result = 0x260;
                kind = 2;
                time = 5000;
                flags |= 0x10;
                break;
            }
            break;
        case 0x147: {
            int found;
            found = fn_8012FA54((void *)object, 15);
            kind = 8;
            if (found != 0) {
                switch (level) {
                case 0x3F:
                    intensity = 100;
                    result = 6;
                    kind = 2;
                    time = 5000;
                    flags |= 8;
                    break;
                }
            }
            break;
        }
        case 0xF7:
        case 0xF8:
        case 0xF9:
        case 0xFA:
        case 0xFB:
        case 0xFC:
            switch (level) {
            case 0x13:
                result = fn_801A9EF4(0x19F, 0x1A1);
                intensity = 100;
                kind = 2;
                time = 5000;
                break;
            }
            break;
        }
    }

done:
    if (out_intensity != 0) {
        *out_intensity = intensity;
    }
    if (out_kind != 0) {
        *out_kind = kind;
    }
    if (out_time != 0) {
        *out_time = time;
    }
    if (out_flags != 0) {
        *out_flags = flags;
    }
    return result;
}
