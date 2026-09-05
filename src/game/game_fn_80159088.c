#pragma use_lmw_stmw on
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct RequestState {
    char pad000[0x11C];
    void* queue;
    char pad120[0x10];
    void* value130;
    char pad134[4];
    char data138[0x8000];
    u32 field8138;
    u32 field813C;
    char pad8140[3];
    s8 loaded;
} RequestState;

typedef struct SourceInfo {
    char pad00[4];
    u32 data_offset;
    u32 work_offset;
} SourceInfo;

typedef struct RequestGlobals {
    int current;
    char pad04[8];
    RequestState* volatile states[4];
} RequestGlobals;

extern volatile RequestGlobals lbl_805B6FE0;
extern SourceInfo* lbl_8064D170[2];
extern int lbl_8064D704;
extern void fn_8015DA70(void*, void*, s8*);
extern void fn_801EA7B4(void*, RequestState*);
extern void fn_8015DAB0(void*);
extern u32 fn_8022658C(void);

void fn_80159088(int slot)
{
    RequestState* state = lbl_805B6FE0.states[slot];

    if (lbl_805B6FE0.states[slot]->loaded == 0) {
        SourceInfo* info = lbl_8064D170[slot];
        state->field813C = 0;
        fn_8015DA70(&state->field813C, (char*)lbl_8064D170[slot] + info->work_offset,
                    &lbl_805B6FE0.states[slot]->loaded);
        fn_801EA7B4((char*)lbl_8064D170[slot] + info->data_offset, state);
        lbl_805B6FE0.states[slot]->loaded = 1;
        if (state->queue != 0 && *(u32*)((char*)state->queue + 8) < (u32)state->queue) {
            fn_8015DAB0(state->queue);
        }
        while ((u16)fn_8022658C() == 0xCACE) {
        }
    }
    lbl_8064D704 = 0;
    state->field8138 = 0;
    state->value130 = 0;
}
#pragma use_lmw_stmw off
