typedef unsigned char u8;
typedef unsigned short u16;
typedef struct EffectState {
    u8 pad00[0x1d];
    signed char index;
    u8 count;
    u8 stride;
    u8 pad20[0x1c];
    int types[8];
} EffectState;

extern void fn_801FE22C(int);
extern void fn_801B05B0(int, int);
extern void fn_801E1920(void*);
extern void fn_801FE934(int, int);
extern int fn_801D3A34(int, int);
extern u8 fn_801CEB2C(int);
extern void fn_8014EAA4();
extern void* fn_80201814(int);
extern void* fn_80201BC8(void*);
extern void fn_8012B750(void*);
extern int fn_801DE8B4();
extern int fn_801D38E8(int);
extern void fn_801DE5DC(int, int);

void fn_801DEEBC(void* object)
{
    u8* info = (u8*)(unsigned int)object;
    u8* const state = info + 0xbc;
    if (info[0xff0] & 1) {
        fn_801FE22C(*(int*)(info + 0x44));
        if (*(int*)(info + 0x10) != -1) fn_801B05B0(*(int*)(info + 0x10), 10);
        fn_801E1920(info);
    } else if (state[0x1d] < state[0x1c]) {
        if (*(u16*)(info + 0xff4) == 20) {
            fn_801FE934(*(int*)(info + 0x44), 5);
        } else if (*(u16*)(info + 0xff4) == 40) {
            fn_8014EAA4(info + 0x38, 250, fn_801CEB2C(*(int*)(info + 4)),
                         fn_801D3A34(*(int*)(info + 4), 0x35),
                         fn_801D3A34(*(int*)(info + 4), 0x46),
                         fn_801D3A34(*(int*)(info + 4), 0x4a),
                         fn_801D3A34(*(int*)(info + 4), 0x4e), 4);
        } else if (*(u16*)(info + 0xff4) == state[0x1d] * state[0x1e] + 0x80) {
            void* target = fn_80201814(*(int*)(info + 0xc));
            if (target && (target = fn_80201BC8(target))) {
                fn_8012B750(target);
                fn_801DE8B4(info, 0, 0);
            }
        } else if (*(u16*)(info + 0xff4) == state[0x1d] * state[0x1e] + 0x81) {
            EffectState* effect = (EffectState*)state;
            if (effect->types[(u8)effect->index] == 3 && *(int*)(state + 0x18)) {
                int owner = fn_801D38E8(*(int*)(info + 4));
                fn_801DE5DC(*(int*)(state + 0x24), owner);
            }
            state[0x1d]++;
        }
    } else {
        fn_801E1920(info);
    }
}
