typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

extern char lbl_80251120[], lbl_80251130[];
extern u8 lbl_80606318[];
extern float lbl_80650C5C, lbl_80650C68, lbl_80650C6C, lbl_80650C70;
extern u8 fn_8018E26C(void*, void*);
extern int fn_80179064(int, int, int, int);
extern void* fn_801E741C(char*);
extern void fn_801F5F98(void*, int, int, u16, unsigned int);
extern void fn_8018EFB0(void*, int, int);
extern float fn_801790F0(float, float);
extern void fn_8017A12C(float*, float, float);
extern int fn_8017A010(float*, int, float, float, float);
extern void fn_80179904(void*, s16);
extern int rand(void);
extern int fn_8019E5E4(u8*);

int fn_8019E8C8(u8* obj)
{
    u8* item;
    u8* entry;
    int moved;
    int distance;
    s16 timer;

    moved = 0;
    item = *(u8**)(obj + 0x4C);
    if (item[0] != 0)
        fn_8018E26C(item, item + 0x2B);

    distance = fn_80179064(*(s16*)(item + 0x0A), *(s16*)(item + 0x0C),
                           *(s16*)(obj + 0x9C), *(s16*)(obj + 0xAC));
    timer = *(s16*)(obj + 0x92);
    if (timer > 0) {
        *(s16*)(obj + 0x92) = timer - 1;
        if (*(s16*)(obj + 0x92) == 1) {
            u8* data;
            void* sound;
            sound = fn_801E741C(lbl_80251120);
            data = lbl_80606318;
            fn_801F5F98(sound, 2, 0, *(u16*)(data + 2), *(unsigned int*)(data + 4));
            sound = fn_801E741C(lbl_80251130);
            fn_801F5F98(sound, 2, 0, *(u16*)(data + 2), *(unsigned int*)(data + 4));
            *(s16*)(obj + 0x92) = -300;
        }
    } else if (distance <= 30) {
        moved = 1;
        fn_8018EFB0(item + 0x10, 0x40, 0);
        fn_8018EFB0(item + 0x10, 0x40, 1);
        *(s16*)(obj + 0x9C) = *(s16*)(item + 0x0A) + *(s16*)(item + 0x10);
        *(s16*)(obj + 0xAC) = *(s16*)(item + 0x0C) + *(s16*)(item + 0x12);
        if (*(s16*)(obj + 0x9C) > *(s16*)(obj + 0x94) ||
            *(s16*)(obj + 0x9C) < *(s16*)(obj + 0x96))
            *(s16*)(obj + 0x9C) = *(s16*)(obj + 0x10);
        if (*(s16*)(obj + 0xAC) > *(s16*)(obj + 0x98) ||
            *(s16*)(obj + 0xAC) < *(s16*)(obj + 0x9A))
            *(s16*)(obj + 0xAC) = *(s16*)(obj + 0x12);
        *(s16*)(item + 0x10) = *(s16*)(obj + 0x9C) - *(s16*)(item + 0x0A);
        *(s16*)(item + 0x12) = *(s16*)(obj + 0xAC) - *(s16*)(item + 0x0C);
        *(s16*)(item + 0x14) = 0;
        *(float*)(obj + 0xDC) = fn_801790F0((float)*(s16*)(item + 0x12),
                                            (float)*(s16*)(item + 0x10)) - lbl_80650C5C;
        *(s16*)(obj + 0x92) = 0;
    } else {
        float difference;
        float magnitude;
        if (timer < 0) {
            *(s16*)(obj + 0x92) = timer + 1;
            if (*(s16*)(obj + 0x92) == -1) {
                u8* data;
                void* sound;
                sound = fn_801E741C(lbl_80251120);
                data = lbl_80606318;
                fn_801F5F98(sound, 0, 2, *(u16*)(data + 2), *(unsigned int*)(data + 4));
                sound = fn_801E741C(lbl_80251130);
                fn_801F5F98(sound, 0, 2, *(u16*)(data + 2), *(unsigned int*)(data + 4));
                *(s16*)(obj + 0x92) = (rand() & 0x3F) + 50;
            }
        }
        fn_8017A12C(&difference, *(float*)(obj + 0xBC), *(float*)(obj + 0xDC));
        magnitude = difference < lbl_80650C68 ? -difference : difference;
        if (magnitude > lbl_80650C6C)
            fn_8017A010((float*)(obj + 0xBC), 0, *(float*)(obj + 0xDC),
                        lbl_80650C70, lbl_80650C6C);
        *(s16*)(item + 0x10) = *(s16*)(obj + 0x9C) - *(s16*)(item + 0x0A);
        *(s16*)(item + 0x12) = *(s16*)(obj + 0xAC) - *(s16*)(item + 0x0C);
        *(s16*)(item + 0x14) = 0;
        fn_80179904(item + 0x10, 2);
        *(s16*)(item + 0x0A) += *(s16*)(item + 0x10) + (1 - (rand() & 1));
        *(s16*)(item + 0x0C) += *(s16*)(item + 0x12) + (1 - (rand() & 1));
        *(s16*)(item + 0x0E) += *(s16*)(item + 0x14);
    }

    *(u16*)(obj + 0x0A) += 1;
    if (moved) {
        int count;
        entry = *(u8**)(obj + 0x4C);
        count = obj[1];
        {
            u8* data;
            void* sound;
            sound = fn_801E741C(lbl_80251120);
            data = lbl_80606318;
            fn_801F5F98(sound, 2, 0, *(u16*)(data + 2), *(unsigned int*)(data + 4));
            sound = fn_801E741C(lbl_80251130);
            fn_801F5F98(sound, 2, 0, *(u16*)(data + 2), *(unsigned int*)(data + 4));
        }
        {
            int i;
        *(void**)(obj + 0x14C) = fn_8019E5E4;
        for (i = 0; i < count; i++, entry += 0x38)
            *(u16*)(entry + 8) = *(u16*)(obj + 0x0A) + (rand() & 0x7F) + 360;
        }
    }
    return 0;
}
