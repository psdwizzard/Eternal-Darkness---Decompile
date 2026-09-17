typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Vec4 { u32 word[4]; } Vec4;
typedef struct RuntimeState {
    u8 pad[0xC];
    int ids[4];
    float amount[4];
    u8 pad2[0x10];
    float scale;
    float multiplier;
    int state;
    u8 pad48[0xC];
    u8 flags;
} RuntimeState;
typedef struct Object {
    u8 pad[0x290];
    RuntimeState* runtime;
    u8 pad294[0xC];
    void* active;
} Object;

#pragma use_lmw_stmw on

extern float lbl_806501DC;
extern void fn_80125ECC(void *);
extern void fn_8012CEA4(Object*, int, Vec4*);
extern void fn_8012CF08(Object*, int, Vec4, Vec4, int, int, float);
extern float fn_8017A5A8(const Vec4*, const Vec4*, float);
extern void fn_8017A630(Vec4*);

void fn_80130434(Object* object, int clear)
{
    Vec4 rotation;
    Vec4 vector;
    int i;

    if ((object->runtime->flags & 0x70) == 0) {
        fn_80125ECC(object);
        if (object->active != 0) {
            fn_8017A630(&rotation);
            for (i = 0; i < 4; i++) {
                if (object->runtime->ids[i] != -1) {
                    float scale;

                    fn_8012CEA4(object, object->runtime->ids[i], &vector);
                    scale = fn_8017A5A8(&vector, &rotation,
                                        object->runtime->amount[i] *
                                        object->runtime->scale *
                                        object->runtime->multiplier);
                    fn_8012CF08(object, object->runtime->ids[i], vector,
                                rotation, 0, 0, scale);
                }
            }
        }
        if (clear != 0) {
            object->runtime->state = 0;
            object->runtime->flags &= ~8;
            object->runtime->multiplier = lbl_806501DC;
        }
    }
}
