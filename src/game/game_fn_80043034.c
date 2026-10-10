typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
#define NULL ((void*)0)

typedef struct LevelEntry {
    u16 unk_00;
    u16 level;
    u32 unk_04;
    u32 unk_08;
} LevelEntry;

typedef struct RootState {
    u32 unk_00;
    u32 unk_04;
    u32 mode_08;
} RootState;

extern s32 lbl_8064C7C8;
extern s32 lbl_8064C7F4;
extern void* lbl_8064D74C;
extern void* lbl_8064C52C;
extern void* lbl_8064C530;
extern void* lbl_8064C4E0;
extern s32 lbl_8064C4E4;
extern char lbl_803040F0[];
extern char lbl_8023EA2C[]; /* "ELoading.tpl" */
extern LevelEntry lbl_8030411C;
extern RootState lbl_803003C8;
extern char lbl_80332500[];
extern char lbl_80332520[];
extern char lbl_80606328[];
extern char lbl_80606318[];

extern void fn_8020D318(char*, LevelEntry**, s32);
extern void fn_80138224(void);
extern void* fn_80135748(u32*);
extern void* fn_80024638(void*, void*, u32*);
extern void fn_8015DAB0(void);
extern void fn_801EB194(s32);
extern void fn_800242B8(void*);
extern void fn_801AD404(s32, s32, s32);
extern void fn_801AD4B4(s32, s32, s32, s32);
extern s32 fn_801AD898(void);
extern void fn_801A99B4(void);
extern void fn_801EF530(void);
extern void fn_801EF580(void*);
extern void fn_801358C4(void);
extern u32 fn_801E88E4(void*);
extern void fn_80139C1C(void);
extern void* fn_801E86A0(void*, u32);
extern void* fn_80125788(void*);
extern void fn_80138994(void*, u32);
extern s32 fn_801E79FC(void*, s32);
extern void fn_800DBF3C(s32);
extern void fn_801F5A04(char*, s32, char*, char*);

void fn_80043034(u32 arg) {
    LevelEntry* entry;
    u32 size;
    void* dest;
    void* handle;
    s32 i;
    s32 level;
    u32 j;
    void* obj;
    u32 k;
    void* other;

    if (lbl_8064C7C8 == 0) {
        return;
    }
    lbl_8064C7C8 = 0;
    if (arg == 0xA1BEEF) {
        fn_8020D318(lbl_803040F0, &entry, 1);
        return;
    }

    fn_80138224();
    if (lbl_8064C7F4 != 0) {
        dest = fn_80135748(&size);
        handle = fn_80024638(lbl_8023EA2C, dest, &size);
        fn_8015DAB0();
        fn_801EB194(0);
        for (i = 0; i < 2; i++) {
            fn_800242B8(handle);
        }
        fn_801AD404(100, 100, 1);
        fn_801AD4B4(0x69, 0, 1, 0);
        while (fn_801AD898() == 0) {
            fn_801A99B4();
        }
        fn_801EF530();
        fn_801EF580(lbl_8064D74C);
        fn_801358C4();
    }

    fn_8020D318(lbl_803040F0, &entry, 1);
    lbl_8030411C = *entry;
    level = lbl_8030411C.level;
    lbl_803003C8.mode_08 = level;
    fn_801E88E4(lbl_8064C52C);
    fn_80139C1C();

    for (j = 0; j < fn_801E88E4(lbl_8064C52C); j++) {
        obj = fn_801E86A0(lbl_8064C52C, j);
        if (obj == NULL) {
            continue;
        }
        for (k = 0; k < j; k++) {
            if (fn_801E86A0(lbl_8064C52C, k) == obj) {
                break;
            }
        }
        if (k != j) {
            continue;
        }
        if (fn_80125788(obj) == NULL) {
            continue;
        }
        other = fn_801E86A0(lbl_8064C530, j);
        if (other == NULL) {
            continue;
        }
        fn_80138994(other, j);
    }

    switch (level) {
    case 0:
    case 12:
    case 16:
        if (fn_801E79FC(lbl_8064C4E0, 0x313) != 0 || level == 12) {
            fn_800DBF3C(0x66);
        } else {
            fn_800DBF3C(0x65);
        }
        break;
    case 5:
    case 9:
        fn_800DBF3C(0x65);
        break;
    case 2:
    case 6:
        fn_800DBF3C(0x63);
        break;
    case 1:
    case 4:
    case 8:
    case 11:
        fn_800DBF3C(0x12);
        break;
    case 3:
    case 7:
    case 10:
    case 15:
        fn_800DBF3C(0x64);
        break;
    case 13:
        fn_800DBF3C(0x66);
        break;
    }

    fn_801F5A04(lbl_80332500, 0x33, lbl_80606328, lbl_80606318);
    fn_801F5A04(lbl_80332520, 0x31, lbl_80606328, lbl_80606318);
    lbl_8064C4E4 = 0;
}
