typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;

/* Rune-entry state. inputCount is signed: retail sign-extends it (extsb)
 * before comparing. game_fn_8007D94C.c calls the same byte u8 flag497. */
typedef struct MenuState {
    u8 pad0[0x490];
    s8 inputs[7]; /* 0x490 */
    s8 inputCount; /* 0x497 */
} MenuState;

typedef struct VolumeTable {
    u16 values[2][4];
} VolumeTable;

typedef struct SoundTable {
    int ids[3];
} SoundTable;

/* lbl_80239208 is 0x1A4 bytes in symbols.txt, so the fields from 0x260 on
 * really belong to the following object (lbl_8023945C at +0xC). Retail
 * addresses them from the lbl_80239208 pool base, so they are reached here
 * past the end of that symbol, as elsewhere in the project. */
typedef struct SoundData {
    u8 pad0[0x260];
    VolumeTable volumes; /* 0x260 */
    SoundTable success; /* 0x270 */
    SoundTable failure; /* 0x27C */
} SoundData;

typedef struct ByteVolumes {
    u8 values[2];
} ByteVolumes;

extern SoundData lbl_80239208;
extern s16 lbl_80244870[7];
extern MenuState lbl_8031CD84;
extern int lbl_8064D18C;
extern ByteVolumes lbl_8064EAC0;

extern int fn_801A98F4(int index, void *object);
extern void fn_8007D744(int event);
extern void fn_8016B400(int id, void *context, void *value);

void fn_800836BC(s16 rune)
{
    VolumeTable volumes;
    ByteVolumes bytes;
    SoundTable success;
    SoundTable failure;
    int matched;
    int sound;
    int row;
    int i;
    SoundData *data;

    row = 0;
    data = &lbl_80239208;
    volumes = data->volumes;
    bytes = lbl_8064EAC0;
    if (lbl_8064D18C == 0x51) {
        row = 1;
    }

    if (lbl_8031CD84.inputCount < 7) {
        fn_801A98F4(volumes.values[row][rune], (void *)bytes.values[row]);
        lbl_8031CD84.inputs[lbl_8031CD84.inputCount] = rune;
        lbl_8031CD84.inputCount++;
        fn_8007D744(2);
        if (lbl_8031CD84.inputCount == 7) {
            matched = 1;
            sound = 0;
            success = data->success;
            failure = data->failure;
            switch (lbl_8064D18C) {
            case 0x51:
                sound = 1;
                break;
            case 0x1B:
            case 0x159:
                sound = 2;
                break;
            }
            for (i = 0; i < 7; i++) {
                if (lbl_8031CD84.inputs[i] != lbl_80244870[i]) {
                    matched = 0;
                    break;
                }
            }
            if (matched) {
                fn_8016B400(success.ids[sound], 0, 0);
            } else {
                fn_8016B400(failure.ids[sound], 0, 0);
            }
        }
    }
}
