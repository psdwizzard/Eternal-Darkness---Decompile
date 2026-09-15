extern void* memset(void*, int, unsigned long);
extern void* lbl_8064C4E4;
extern const float lbl_80651458;
extern const float lbl_8065145C;
extern const float lbl_80651460;
extern const float lbl_80651464;
extern const float lbl_80651468;

typedef struct MotionState {
    unsigned char pad0[0x24];
    unsigned int unk24;
    float unk28;
    float unk2C;
    float unk30;
    float unk34;
    float unk38;
    unsigned int unk3C;
    unsigned char pad40[4];
    unsigned int unk44;
    unsigned char pad48[0x20];
    void* unk68;
} MotionState;

void fn_801F7034(MotionState* state, int clear)
{
    if (clear != 0) {
        memset(state, 0, 0x88);
        state->unk68 = lbl_8064C4E4;
    }

    state->unk24 = 0;
    state->unk28 = lbl_80651458;
    state->unk2C = lbl_8065145C;
    state->unk3C = 0;
    state->unk30 = lbl_80651460;
    state->unk38 = lbl_80651464;
    state->unk34 = lbl_80651468;
    state->unk44 = 0;
}
