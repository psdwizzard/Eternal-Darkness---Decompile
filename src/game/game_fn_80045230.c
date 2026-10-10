typedef struct GameState {
    unsigned char pad[0x1918];
    unsigned char flag;
} GameState;

extern GameState lbl_803003C8;

unsigned char fn_80045230(void) {
    return lbl_803003C8.flag;
}
