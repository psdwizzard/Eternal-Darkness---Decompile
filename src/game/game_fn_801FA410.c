typedef unsigned char u8;

typedef struct MotionState {
    u8 pad00[0x70];
    struct MotionState* source;
    u8 pad74[0x14];
} MotionState;

typedef struct MotionGlobals {
    MotionState first[12];
    MotionState second[12];
    MotionState current_first;
    MotionState current_second;
} MotionGlobals;

extern MotionGlobals lbl_8063C6B8;
extern int lbl_8064C3A8;

int fn_801FA410(int index)
{
    int previous = lbl_8064C3A8;

    lbl_8064C3A8 = index;
    lbl_8063C6B8.current_first.source = &lbl_8063C6B8.second[index];
    lbl_8063C6B8.current_second.source = &lbl_8063C6B8.first[index];
    return previous;
}
