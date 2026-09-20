typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern float lbl_8064CF04;
extern const float lbl_806504F8;
extern const float lbl_806504FC;
extern const float lbl_80650500;
extern void* lbl_8064C4E0;
extern int lbl_802FC5BC[];

extern void fn_8014D650(void);
extern void* fn_80149D98(void (*)(void));
extern void fn_80149D64(void*);
extern int fn_80201A84(void*);
extern int fn_801E79FC(void*, int);
extern void fn_80179904(void*, int);

/* Select the packed variant for the current global level. */
static inline u8 packed_kind(int value)
{
    u8 kind;
    int packed;
    if (lbl_8064CF04 >= lbl_806504FC) {
        packed = (value >> 2) & 0x3F;
        kind = value & 0xFF;
        if (packed > 0)
            kind = packed;
    } else if (lbl_8064CF04 >= lbl_80650500) {
        packed = (value >> 1) & 0x7F;
        kind = value & 0xFF;
        if (packed > 0)
            kind = packed;
    } else {
        kind = value & 0xFF;
    }
    return kind;
}

void fn_8014D478(void* owner, Vec3* position, float* rotation,
                 int first_kind, int second_kind, int* source, int flags)
{
    void* state;

    if (((flags & 4) != 0 || !(lbl_8064CF04 >= lbl_806504F8)) && flags != 0) {
        state = fn_80149D98(fn_8014D650);
        if (state != 0) {
            fn_80149D64(state);
            *(u8*)((char*)state + 0x1328) = 4;
            *(int*)((char*)state + 0x38C) = flags;

            *(u8*)((char*)state + 0x398) = packed_kind(first_kind);
            *(u8*)((char*)state + 0x399) = packed_kind(second_kind);
            *(int*)((char*)state + 0x3A4) = *source;
            *(int*)((char*)state + 0x394) = -1;
            if (owner != 0)
                *(int*)((char*)state + 0x394) = fn_80201A84(owner);
            if (fn_801E79FC(lbl_8064C4E0, 0x2ED) != 0)
                *(int*)((char*)state + 0x3A4) = lbl_802FC5BC[9];
            *(Vec3*)((char*)state + 0xA0) = *position;
            *(u16*)((char*)state + 0xAC) = (short)rotation[0];
            *(u16*)((char*)state + 0xAE) = (short)rotation[1];
            *(u16*)((char*)state + 0xB0) = (short)rotation[2];
            fn_80179904((char*)state + 0xAC, 5);
        }
    }
}
