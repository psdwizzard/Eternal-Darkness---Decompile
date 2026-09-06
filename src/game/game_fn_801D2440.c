typedef unsigned char u8;
typedef unsigned short u16;
typedef struct GameObject GameObject;

struct GameObject {
    u8 pad00[4];
    void* owner;
    int type;
    u8 pad0C[4];
    int handle;
    u8 pad14[0x1C];
    void* link30;
    u8 pad34[0x10];
    void* resource44;
    u8 pad48[0x74];
    void* actorBC;
    void* actorC0;
    void* actorC4;
    u8 padC8[0xF28];
    u8 flagsFF0;
    u8 padFF1[3];
    u16 stateFF4;
};

extern int lbl_8064D18C;
extern void* fn_80201814(void*);
extern void* fn_80201C24(void);
extern int fn_80157894(void);
extern void fn_80201ADC(void);
extern void* fn_80201C2C(void);
extern void fn_80204E0C(void*, void*);
extern void fn_80204F54(void*);
extern void fn_8020123C(int, void*, void*, int);
extern void fn_801FE22C(void*);
extern void fn_801B05B0(int, int);
extern void fn_801D2FA4(GameObject*);
extern void fn_801D1318(int);

void fn_801D2440(GameObject* object)
{
    if (object->type != lbl_8064D18C) {
        void* actor = object->actorBC;
        void* actor_info = fn_80201814(actor);
        void* current = fn_80201C24();

        if (fn_80157894() & 1) {
            fn_80201ADC();
            current = fn_80201C2C();
            if (object->stateFF4 <= 80) {
                fn_80204E0C(actor_info, current);
            } else {
                void* other = fn_80201814(object->actorC0);
                fn_80204F54(actor_info);
                fn_8020123C(57, actor, actor, 0);
                fn_80204E0C(other, current);
            }
        }

        fn_801FE22C(object->resource44);
        if (object->handle != -1) {
            fn_801B05B0(object->handle, 10);
        }
        fn_801D2FA4(object);
        if (object->flagsFF0 & 0x10) {
            fn_801D1318(0);
        }
    }
}
