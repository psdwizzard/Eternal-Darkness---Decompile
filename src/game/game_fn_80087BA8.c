typedef unsigned char u8;

typedef struct Owner {
    u8 pad[0x14C];
    float position[3];
    u8 pad158;
    u8 active;
    u8 pad15A[2];
    int* data;
} Owner;

typedef struct Work {
    u8 bytes[0xC4];
    Owner* owner;
} Work;

extern void *fn_8006ED3C(void*, int, int*);
extern int fn_8006D548(int, int, int, float*, int, int, int);
extern void *fn_80201814(int);
extern void *fn_80201BC8(void*);
extern u8 fn_8012B8A8(void*, float*);
extern int lbl_8064C824;
extern int fn_801A6D94(int);
extern void fn_8006DEF8(Work*, int, void*, void*, int);
extern void fn_8006EA4C(void);
extern void fn_8006BEE4(void*, void (*)(void));

int fn_80087BA8(void* argument)
{
    int success = 0;
    int index;
    void* state;
    Work* work = argument;
    Owner* owner;
    float* position;
    int* data;
    int placed;
    int i;
    int j;

    state = fn_8006ED3C(work, 6, &index);
    owner = work->owner;
    position = owner->position;
    data = owner->data;
    if (owner->active == 0) {
        placed = 0;
        for (i = 0; i < 20; i++) {
            data[0x1780 / 4] = fn_8006D548(2, 2, 3, position, 0, 0,
                                         data[0x1780 / 4]);
            if (data[0x1780 / 4] != -1) {
                void* object = fn_80201814(*(int*)(work->bytes + 0x38));
                object = fn_80201BC8(object);
                if (fn_8012B8A8(object, position)) {
                    ((u8*)position)[0xD] = 1;
                    placed = 1;
                    success = 1;
                    break;
                }
                data[0x1780 / 4]++;
            }
        }
        if (placed == 0 && fn_8006D548(2, 2, 4, position, 0, 0, 0) >= 0) {
            ((u8*)position)[0xD] = 1;
            success = 1;
        }
    } else {
        ((u8*)position)[0xD] = 0;
    }
    if (fn_801A6D94(lbl_8064C824)) {
        work->bytes[index * 0x2C + 0x68] = 4;
        fn_8006DEF8(work, 6, 0, 0, 0);
        for (j = 0; j < 4; j++) {
            work->bytes[index * 0x2C + 0x68] = j;
            fn_8006DEF8(work, 6, 0, 0, 0);
        }
        work->bytes[index * 0x2C + 0x68] = 0;
        ((u8*)position)[0xD] = 0;
        fn_8006BEE4(state, fn_8006EA4C);
    }
    return success;
}
