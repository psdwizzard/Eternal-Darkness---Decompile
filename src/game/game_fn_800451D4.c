typedef unsigned char u8;

typedef struct GameState {
    u8 pad[0x1919];
    u8 flags;
} GameState;

extern GameState lbl_803003C8;

u8 fn_800451D4(void)
{
    return lbl_803003C8.flags;
}
