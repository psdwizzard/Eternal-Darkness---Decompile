typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern unsigned char lbl_8031F7C0[];
extern int lbl_8064D18C;
extern int lbl_8064CDC4;
extern float lbl_8064F010;
extern void* fn_80201B3C();
extern void *fn_80201BC8();
extern void fn_801F7C78(void);
extern void* memcpy(void*, const void*, unsigned int);
extern void fn_8011F0E8(void*, Vec3*);
extern void fn_8012B7A0(void*, float);
extern void fn_8011FB54(void*, int);
extern u32 fn_800E507C(void*);
extern u32 fn_801F4E94(void*);
extern u32 fn_80028E0C(void*);
extern u32 fn_8016B21C(void*);
extern u32 fn_801FAD4C(void*);
extern u32 fn_801F6794(void*);
extern u32 fn_8012BB34(void*);
extern u32 fn_801E9068(void*);
extern u32 fn_801A8268(void*);
extern u32 fn_8011E98C(void*);
extern u32 fn_801A9A20(void*);
extern void fn_80159440(int, int);
extern void fn_80200EAC(float, int, int, int, int);

int fn_800B002C(void)
{
    unsigned char* buffer = lbl_8031F7C0;
    void* current;
    int oldValue;
    int offset;
    void* object;
    Vec3 position;
    float scale;
    int value;

    current = fn_80201B3C();
    if (buffer != 0 && current != 0) {
        object = fn_80201BC8(current);
        fn_801F7C78();
        memcpy(&position, buffer, 12);
        fn_8011F0E8(object, &position);
        memcpy(&scale, buffer + 12, 4);
        fn_8012B7A0(object, scale);
        memcpy(&value, buffer + 16, 4);
        fn_8011FB54(object, value);
        offset = fn_800E507C(buffer + 20) + 20;
        offset += fn_801F4E94(buffer + (u16)offset);
        oldValue = lbl_8064D18C;
        if (oldValue != value) {
            lbl_8064CDC4 = 0;
        }
        fn_80159440(value, 68);
        if (value != oldValue) {
            fn_80200EAC(lbl_8064F010, 62, 0, 0, value);
        }
        offset += fn_80028E0C(buffer + (u16)offset);
        offset += fn_8016B21C(buffer + (u16)offset);
        offset += fn_801FAD4C(buffer + (u16)offset);
        offset += fn_801F6794(buffer + (u16)offset);
        offset += fn_8012BB34(buffer + (u16)offset);
        offset += fn_801E9068(buffer + (u16)offset);
        offset += fn_801A8268(buffer + (u16)offset);
        offset += fn_8011E98C(buffer + (u16)offset);
        fn_801A9A20(buffer + (u16)offset);
        return 1;
    }
    return 0;
}
