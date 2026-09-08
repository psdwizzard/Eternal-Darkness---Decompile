typedef int s32;

typedef struct GameState {
    s32 previous;
    s32 value;
    s32 mode;
} GameState;

extern unsigned char lbl_803003AC[];
extern GameState lbl_803003C8;
extern s32 lbl_8023D5B8[];
extern s32 lbl_8064D18C;

char lbl_8023CC30[] =
    "\nInvalid Num of Args Expecting 1 or 0, and got %i\n";

extern double fn_8016A694(void*, int);
extern int fn_8016A598(void*);
extern void fn_8016A830(void*, double);
extern void fn_800AFBA8(void*);
extern int fn_800AFDA4(void);
extern void fn_80025A78(int);

s32 fn_8001A6C4(void* script)
{
    s32 value;
    s32 mode;
    s32 reset;

    value = (s32)fn_8016A694(script, 1);
    mode = (s32)fn_8016A694(script, 2);
    if (fn_8016A598(script) == 2) {
        reset = 0;
    } else {
        reset = (s32)fn_8016A694(script, 3);
    }

    fn_800AFBA8(lbl_803003AC);
    if (reset != 0) {
        fn_800AFDA4();
    }

    lbl_803003C8.value = lbl_803003C8.previous;
    switch (value) {
    case 0:
        lbl_803003C8.previous = 0;
        break;
    case 1:
        lbl_803003C8.previous = 1;
        break;
    case 2:
        lbl_803003C8.previous = 2;
        break;
    case 3:
        lbl_803003C8.previous = 3;
        break;
    case 4:
        lbl_803003C8.previous = 4;
        break;
    case 5:
        lbl_803003C8.previous = 5;
        break;
    case 6:
        lbl_803003C8.previous = 6;
        break;
    case 7:
        lbl_803003C8.previous = 7;
        break;
    case 8:
        lbl_803003C8.previous = 8;
        break;
    case 9:
        lbl_803003C8.previous = 9;
        break;
    case 10:
        lbl_803003C8.previous = 10;
        break;
    case 11:
        lbl_803003C8.previous = 11;
        break;
    case 12:
        lbl_803003C8.previous = 0;
        break;
    default:
        lbl_803003C8.previous = 0;
        break;
    }

    switch (mode) {
    case 16:
        lbl_803003C8.mode = 16;
        break;
    case 0:
        lbl_803003C8.mode = 0;
        break;
    case 1:
        lbl_803003C8.mode = 1;
        break;
    case 2:
        lbl_803003C8.mode = 2;
        break;
    case 3:
        lbl_803003C8.mode = 3;
        break;
    case 4:
        lbl_803003C8.mode = 4;
        break;
    case 5:
        lbl_803003C8.mode = 5;
        break;
    case 6:
        lbl_803003C8.mode = 6;
        break;
    case 7:
        lbl_803003C8.mode = 7;
        break;
    case 8:
        lbl_803003C8.mode = 8;
        break;
    case 9:
        lbl_803003C8.mode = 9;
        break;
    case 10:
        lbl_803003C8.mode = 10;
        break;
    case 11:
        lbl_803003C8.mode = 11;
        break;
    case 13:
        lbl_803003C8.mode = 13;
        break;
    case 15:
        lbl_803003C8.mode = 15;
        break;
    default:
        lbl_803003C8.mode = 0;
        break;
    }

    lbl_8064D18C = lbl_8023D5B8[lbl_803003C8.mode];
    fn_80025A78(9);
    return 0;
}

s32 fn_8001A9D0(void* script)
{
    s32 mode;

    switch (lbl_803003C8.mode) {
    case 16:
        mode = 16;
        break;
    case 0:
        mode = 0;
        break;
    case 1:
        mode = 1;
        break;
    case 2:
        mode = 2;
        break;
    case 3:
        mode = 3;
        break;
    case 4:
        mode = 4;
        break;
    case 5:
        mode = 5;
        break;
    case 6:
        mode = 6;
        break;
    case 7:
        mode = 7;
        break;
    case 8:
        mode = 8;
        break;
    case 9:
        mode = 9;
        break;
    case 10:
        mode = 10;
        break;
    case 11:
        mode = 11;
        break;
    case 13:
        mode = 13;
        break;
    case 15:
        mode = 15;
        break;
    default:
        mode = 0;
        break;
    }

    fn_8016A830(script, (double)mode);
    return 1;
}
