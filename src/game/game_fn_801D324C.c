typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct GameObject {
    u8 pad00[4];
    void* owner;
    u32 type;
    u8 pad0C[0x24];
    void* link30;
    u8 pad34[0x10];
    void* resource44;
    u8 pad48[0xFA8];
    u8 flagsFF0;
    u8 padFF1[3];
    u16 stateFF4;
} GameObject;

extern u32 lbl_8064D18C;
extern void fn_801FE22C(void*);
extern void fn_801D31E0(GameObject*);

/*
 * Effect-object state callback.  The non-current-type teardown path and the
 * state discriminator are recovered.  The four particle-construction arms
 * still require their large stack-local descriptor layouts to be typed.
 */
void fn_801D324C(GameObject* object)
{
    if (object->type != lbl_8064D18C) {
        fn_801FE22C(object->resource44);
        fn_801D31E0(object);
        return;
    }

    switch (object->stateFF4) {
    case 0:
    case 0x2E:
    case 0x42:
    case 0x56:
        break;
    }
}
