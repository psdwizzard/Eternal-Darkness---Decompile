typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef float f32;

typedef struct Vec3f { f32 x, y, z; } Vec3f;
typedef struct Object { u8 bytes[0x1000]; } Object;

extern void fn_801CEF74(void);
extern Object* fn_801D0D78(u32, u32, u32, void*, void (*)(void), u32, u32, u32, u32, u32);
extern void fn_8011F114(Vec3f*, void*);
extern void fn_801D0CA4(Object*);
extern void* lbl_8064C4E4;
extern const f32 lbl_80651040;

void fn_801CE594(u32 valueCC, u32 kind, const Vec3f* position, u16 valueC4,
                 u8 valueC0, u16 valueC2, u16 valueC6, u8 valueC1,
                 const Vec3f* direction, u16 valueC8, u8 valueBC,
                 u16 height, u32 value264, u32 value284, const u32* value288)
{
    Vec3f adjusted;
    Vec3f base;
    Object* object = fn_801D0D78(0, valueCC, kind, (void*)position,
                                  fn_801CEF74, 0, 0, 0, 0, 1);
    if (object != 0) {
        int converted;
        fn_8011F114(&base, lbl_8064C4E4);
        adjusted = base;
        fn_801D0CA4(object);
        object->bytes[0xFF1] = 6;
        *(Vec3f*)(object->bytes + 0xEC) = *position;
        ((Vec3f*)(object->bytes + 0xEC))->z += lbl_80651040;
        converted = (int)(adjusted.z + height);
        *(u16*)(object->bytes + 0xC4) = valueC4;
        *(u16*)(object->bytes + 0xC6) = valueC6;
        *(u16*)(object->bytes + 0xC2) = valueC2;
        object->bytes[0xC0] = valueC0;
        object->bytes[0xC1] = valueC1;
        object->bytes[0xBD] = 0;
        object->bytes[0xBF] = 0;
        *(u32*)(object->bytes + 0x288) = *value288;
        object->bytes[0xBE] = 45;
        *(u32*)(object->bytes + 0xCC) = valueCC;
        *(u32*)(object->bytes + 0x264) = value264;
        *(u32*)(object->bytes + 0x284) = value284;
        *(Vec3f*)(object->bytes + 0xF8) = *direction;
        *(u16*)(object->bytes + 0xC8) = valueC8;
        *(u16*)(object->bytes + 0xCA) = converted;
        object->bytes[0xBC] = valueBC;
    }
}
