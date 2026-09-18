typedef unsigned char u8;
typedef unsigned short u16;
typedef struct Job { u8 bytes[0x70]; } Job;
typedef struct State {
    int unk0;
    int initial;
    u8 pad08[4];
    int final;
    int step;
    u8 pad14[8];
    int placement2;
    int placement3;
    int placement4;
    int value;
    u8 pad2C[10];
    u8 flag36;
    u8 pad37;
    u8 kind38;
    u8 pad39[15];
    void (*callback48)(void);
    u8 pad4C[24];
    void* owner;
    void (*callback68)(void);
} State;

extern float lbl_806504D8;
extern float lbl_806504DC;
extern void fn_8014B768(void);
extern void fn_8014C7C0(void);
extern void fn_8014C87C(void);
extern void *fn_80201814();
extern Job* fn_80149D98(void (*)(void));
extern void fn_80149D64(void);
extern void *fn_80201BC8();
extern int fn_8011F6A4(void*, int, int, int, void*, int);
extern void fn_8014CBC0(void*);
extern void fn_801FE8DC(void*, float, float, float);
extern int fn_801E8328();

void* fn_8014C68C(void* owner, int start, int finish, int* value,
                  int initial, int final, u16 count)
{
    Job* job = 0;
    int placement[11];
    void* runtime = fn_80201814(owner);
    State* state;

    if (runtime != 0) {
        job = fn_80149D98(fn_8014B768);
        if (job != 0) {
            fn_80149D64();
            fn_8011F6A4(fn_80201BC8(runtime), start, finish, -1, placement, 1);
            state = (State*)(job->bytes + 8);
            fn_8014CBC0(state);
            state->initial = initial;
            state->placement2 = placement[2];
            state->placement3 = placement[3];
            state->placement4 = placement[4];
            state->value = *value;
            state->callback48 = fn_8014C7C0;
            state->flag36 = 0xFF;
            state->final = final;
            state->step = (final - initial) / count;
            state->kind38 = 4;
            state->owner = owner;
            state->callback68 = fn_8014C87C;
            state->unk0 = 0;
            fn_801FE8DC(&state->initial, lbl_806504D8, lbl_806504D8,
                        lbl_806504DC);
            fn_801E8328(19, state);
        }
    }
    return job;
}
