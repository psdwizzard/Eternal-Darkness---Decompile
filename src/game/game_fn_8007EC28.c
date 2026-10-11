typedef unsigned char u8;
typedef unsigned int u32;
typedef short s16;

/* The reset state contains five repeated 0x34-byte entries. */
typedef struct MenuSlot {
    u32 values[3];
    u8 padding[0x18];
    s16 scaled[2];
    u8 padding2[4];
    float parameters[2];
} MenuSlot;

typedef struct GameState {
    u8 padding[0x24];
    MenuSlot slots[5];
} GameState;

typedef struct MenuPreset {
    u8 padding[0xac];
    u32 values[3];
} MenuPreset;

extern GameState lbl_8031CBA0;
extern MenuPreset lbl_8031CD84[];
extern float lbl_8064EA14, lbl_8064EA18, lbl_8064EA1C;
extern float lbl_8064EA20, lbl_8064EA24, lbl_8064EA28, lbl_8064EA2C;
extern void *memcpy(void *, const void *, unsigned int);
extern void *memset(void *, int, unsigned int);

void fn_8007EC28(void)
{
    u32 saved0, saved1;
    MenuPreset *preset = lbl_8031CD84;

    memcpy(&saved0, &lbl_8031CBA0.slots[4].parameters[0], 4);
    memcpy(&saved1, &lbl_8031CBA0.slots[4].parameters[1], 4);
    memset((u8 *)&lbl_8031CBA0 + 0x1c, 0, 0x10c);
    memcpy(&lbl_8031CBA0.slots[4].parameters[0], &saved0, 4);
    memcpy(&lbl_8031CBA0.slots[4].parameters[1], &saved1, 4);

    *(float *)((u8 *)&lbl_8031CBA0 + 0x50) = lbl_8064EA18;
    *(float *)((u8 *)&lbl_8031CBA0 + 0x54) = lbl_8064EA14;
    *(float *)((u8 *)&lbl_8031CBA0 + 0x84) = lbl_8064EA1C;
    *(float *)((u8 *)&lbl_8031CBA0 + 0x88) = lbl_8064EA20;
    *(float *)((u8 *)&lbl_8031CBA0 + 0xb8) = lbl_8064EA24;
    *(float *)((u8 *)&lbl_8031CBA0 + 0xbc) = lbl_8064EA28;
    *(s16 *)((u8 *)&lbl_8031CBA0 + 0x7c) = (s16)(lbl_8064EA2C * lbl_8064EA18);
    *(s16 *)((u8 *)&lbl_8031CBA0 + 0x7e) = (s16)(lbl_8064EA2C * lbl_8064EA14);
    *(s16 *)((u8 *)&lbl_8031CBA0 + 0xb0) = (s16)(lbl_8064EA2C * lbl_8064EA1C);
    *(s16 *)((u8 *)&lbl_8031CBA0 + 0xb2) = (s16)(lbl_8064EA2C * lbl_8064EA20);
    *(s16 *)((u8 *)&lbl_8031CBA0 + 0xe4) = (s16)(lbl_8064EA2C * lbl_8064EA24);
    *(s16 *)((u8 *)&lbl_8031CBA0 + 0xe6) = (s16)(lbl_8064EA2C * lbl_8064EA28);
    lbl_8031CBA0.slots[0].values[0] = preset[0].values[0];
    lbl_8031CBA0.slots[0].values[1] = preset[0].values[1];
    lbl_8031CBA0.slots[0].values[2] = preset[0].values[2];
    lbl_8031CBA0.slots[1].values[0] = preset[1].values[0];
    lbl_8031CBA0.slots[1].values[1] = preset[1].values[1];
    lbl_8031CBA0.slots[1].values[2] = preset[1].values[2];
    lbl_8031CBA0.slots[2].values[0] = preset[2].values[0];
    lbl_8031CBA0.slots[2].values[1] = preset[2].values[1];
    lbl_8031CBA0.slots[2].values[2] = preset[2].values[2];
    lbl_8031CBA0.slots[3].values[0] = preset[3].values[0];
    lbl_8031CBA0.slots[3].values[1] = preset[3].values[1];
    lbl_8031CBA0.slots[3].values[2] = preset[3].values[2];
    lbl_8031CBA0.slots[4].values[0] = preset[4].values[0];
    lbl_8031CBA0.slots[4].values[1] = preset[4].values[1];
    lbl_8031CBA0.slots[4].values[2] = preset[4].values[2];
}
