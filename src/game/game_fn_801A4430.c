typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct QueryResult {
    u32 header[2];
    float position[3];
    float direction[3];
    float value;
} QueryResult;

extern u32 lbl_80651E88;
extern u16 lbl_80651E8C;
extern u32 lbl_80650D70;
extern const float lbl_80650D74;
extern const float lbl_80650D78;
extern const float lbl_80650D7C;
extern const float lbl_80650D80;
extern void* lbl_8064D224;
extern u8 lbl_80607120[];
extern u8 lbl_80606328[];
extern u8 lbl_80606318[];

extern void fn_801804AC(void*, void*, void*, void*);
extern void* memset(void*, int, unsigned long);
extern void* memcpy(void*, const void*, unsigned long);
extern void fn_80180554(void*, void*, void*, void*, int, int);
extern void fn_801805E0(void*, int, u8, u8, float, void*);
extern void fn_80180518(void*, int, int);
extern int fn_800FBFB0(void);
extern void fn_8018E230(void*, void*, int, int, int, int);
extern void fn_8018CB70(void*, u8, u16);
extern void fn_8018C540(void*, void*, u8, int, u16);
extern void fn_801F5A04(void*, s16, void*, void*);
extern void fn_8018F014(void*, u16);
extern void* fn_80201890(u32);
extern int fn_8011F598(void*, int, int, int, void*, int);
extern void fn_801A4874(float*, s16*);
extern float fn_80048C2C(float);
extern float fn_80048C50(float);
extern u32 fn_8018EF9C(u32);

void fn_801A4430(u8* object, void* position, u8* descriptor, u8* config)
{
    struct { u32 word; u16 half; } setup;
    u32 texture;
    u8 count;
    u8* entry;
    u8 spread;
    int i;

    setup.word = lbl_80651E88;
    setup.half = lbl_80651E8C;
    texture = lbl_80650D70;
    count = config[0];
    fn_801804AC(object, config + 0x24, descriptor, &setup);
    object[0] = 0x80;
    object[1] = count;
    object[4] = config[3];
    *(u16*)(object + 0x0c) = *(u16*)(config + 6);
    *(s16*)(object + 0x0e) = *(s16*)(config + 4);
    *(u16*)(object + 0x0a) = 0;
    *(u32*)(object + 0x44) = 0;
    *(float*)(object + 0x3c) = lbl_80650D74;
    *(float*)(object + 0x40) = lbl_80650D78;
    *(void**)(object + 0x68) = lbl_8064D224;
    memset(object + 0x24, 0, 0x10);

    entry = *(u8**)(object + 0x4c);
    spread = (config[1] >> 1) - 1;
    switch (config[0x20]) {
    case 1:
        for (i = 0; (u8)i < count;) {
            u8 coord[6];
            memcpy(coord, config + 0x2a, 6);
            fn_8018F014(coord, *(u16*)(config + 0x22));
            fn_80180554(entry, coord, descriptor, &setup, 0, 0);
            entry += 0x38;
            i++;
        }
        break;
    case 2:
    {
        void* source = fn_80201890(*(u32*)(config + 0x34));
        if (source != 0) {
            int previous = -1;
            for (i = 0; (u8)i < count;) {
                s16 coord[3];
                QueryResult result;
                previous = fn_8011F598(source, 0x10, 0, previous, &result, 1);
                if (previous == -1)
                    previous = fn_8011F598(source, 0x10, 0, -1, &result, 1);
                fn_801A4874(result.position + 0, coord + 0);
                fn_801A4874(result.position + 1, coord + 1);
                fn_801A4874(result.position + 2, coord + 2);
                fn_80180554(entry, coord, descriptor, &setup, 0, 0);
                entry += 0x38;
                i++;
            }
        } else {
            *(u16*)(object + 0x22) = 8;
        }
        break;
    }
    case 3:
    {
        float scale = lbl_80650D7C;
        for (i = 0; (u8)i < count;) {
            float angle = scale * (float)(u8)i / (float)count;
            s16 coord[3];
            coord[0] = (s16)((float)*(u16*)(config + 0x22) * fn_80048C2C(angle) + (float)*(s16*)(config + 0x2a));
            coord[1] = (s16)((float)*(u16*)(config + 0x22) * fn_80048C50(angle) + (float)*(s16*)(config + 0x2c));
            coord[2] = *(s16*)(config + 0x2e);
            fn_80180554(entry, coord, descriptor, &setup, 0, 0);
            entry += 0x38;
            i++;
        }
        break;
    }
    }

    entry = *(u8**)(object + 0x4c);
    for (i = 0; (u8)i < count;) {
        fn_801805E0(entry + 0x20, 4, (u8)(config[1] - (spread & fn_800FBFB0())), (u8)i << 2, lbl_80650D80, &texture);
        fn_8018E230(entry, entry + 0x2b, 1, 0, object[4], 0xcc);
        fn_80180518(object + 0x24, i, 1);
        entry += 0x38;
        i++;
    }
    fn_8018CB70(*(void**)(object + 0x54), count, *(u16*)(lbl_80607120 + 2));
    {
        u32 resolved_texture = fn_8018EF9C(*(u32*)(config + 0x30));
        fn_8018C540(*(void**)(object + 0x58), &resolved_texture, count, 4, *(u16*)(lbl_80607120 + 2));
    }
    if (*(s16*)(config + 4) >= 0)
        fn_801F5A04(object + 0x6c, *(s16*)(config + 4), lbl_80606328, lbl_80606318);
}
