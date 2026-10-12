typedef unsigned int u32;

typedef struct GameState {
    int unk0;
    int unk4;
    int mode;
    int index;
} GameState;

typedef struct LevelFilename {
    char text[13];
} LevelFilename;

extern LevelFilename lbl_80238DF8;
extern GameState lbl_803003C8;
extern u32* lbl_8064C4E0;
extern u32 lbl_8064D11C;
extern void* lbl_8064D1CC;

extern int fn_801E79FC(u32* set, u32 index);
extern void fn_800DBF3C(void* value);
extern int fn_801391AC(void);
extern int fn_80042808(void);
extern void* fn_80138CD4(void* object, u32 size);
extern void* fn_8016B3A4(void* value, int alternate);

void fn_80042818(int level)
{
    LevelFilename filename = lbl_80238DF8;

    if (level == 16) {
        level = 0;
    }
    if (level == 0) {
        if (fn_801E79FC(lbl_8064C4E0, 0x313) != 0) {
            level = 12;
        }
        if (fn_801E79FC(lbl_8064C4E0, 0x313) != 0) {
            lbl_803003C8.unk4 = 0;
        }
    }
    if (level == 12) {
        fn_800DBF3C((void*)0x66);
    }
    if (level == 19) {
        filename.text[6] = level / 10 + '0';
        filename.text[7] = '6';
    } else {
        filename.text[6] = level / 10 + '0';
        filename.text[7] = level % 10 + '0';
    }
    if (fn_801391AC() != 0 && level == fn_80042808()) {
        lbl_8064D1CC = fn_80138CD4((void*)0xF69340, lbl_8064D11C);
    } else {
        fn_8016B3A4(filename.text, 1);
    }
}
