#ifndef GAME_STATE_8063C6B8_H
#define GAME_STATE_8063C6B8_H

typedef struct GameState8063C6B8Entry {
    unsigned char pad0[0x68];
    void* field_68;
    unsigned int field_6c;
    unsigned char pad70[0xC];
    unsigned int field_7c;
    unsigned char pad80[8];
} GameState8063C6B8Entry;

extern GameState8063C6B8Entry lbl_8063C6B8[];
extern GameState8063C6B8Entry lbl_8063CD18[];

#endif
