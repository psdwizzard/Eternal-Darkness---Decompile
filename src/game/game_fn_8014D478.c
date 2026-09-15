typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern float lbl_8064CF04;
extern float lbl_806504F8;
extern float lbl_806504FC;
extern float lbl_80650500;
extern void* lbl_8064C4E0;
extern int lbl_802FC5BC[];

extern void fn_8014D650(void);
extern void* fn_80149D98(void (*)(void));
extern void fn_80149D64(void*);
extern int fn_80201A84(void*);
extern int fn_801E79FC(void*, int);
extern void fn_80179904(void*, int);

/*
 * Honest NonMatching reconstruction. The behavior and all field writes are
 * recovered; remaining differences are temporary-register selection in the
 * two packed-kind blocks and floating-point load scheduling.
 */
void fn_8014D478(void* owner, Vec3* position, float* rotation,
                 int first_kind, int second_kind, int* source, int flags)
{
    void* state;
    u8 kind;

    if (((flags & 4) != 0 || !(lbl_8064CF04 >= lbl_806504F8)) && flags != 0) {
        state = fn_80149D98(fn_8014D650);
        if (state != 0) {
            fn_80149D64(state);
            *(u8*)((char*)state + 0x1328) = 4;
            *(int*)((char*)state + 0x38C) = flags;

            if (lbl_8064CF04 >= lbl_806504FC) {
                int packed = (first_kind >> 2) & 0x3F;
                kind = first_kind & 0xFF;
                if (packed > 0)
                    kind = packed;
            } else if (lbl_8064CF04 >= lbl_80650500) {
                int packed = (first_kind >> 1) & 0x7F;
                kind = first_kind & 0xFF;
                if (packed > 0)
                    kind = packed;
            } else {
                kind = first_kind & 0xFF;
            }
            *(u8*)((char*)state + 0x398) = kind;

            if (lbl_8064CF04 >= lbl_806504FC) {
                int packed = (second_kind >> 2) & 0x3F;
                kind = second_kind & 0xFF;
                if (packed > 0)
                    kind = packed;
            } else if (lbl_8064CF04 >= lbl_80650500) {
                int packed = (second_kind >> 1) & 0x7F;
                kind = second_kind & 0xFF;
                if (packed > 0)
                    kind = packed;
            } else {
                kind = second_kind & 0xFF;
            }
            *(u8*)((char*)state + 0x399) = kind;
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
