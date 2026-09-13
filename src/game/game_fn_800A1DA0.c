typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Object800A1DA0 {
    u8 pad000[0x264];
    u8* data;
    u8 pad268[0x37];
    s8 index;
    u16 timer;
} Object800A1DA0;

extern int fn_800FBFB0(void);
extern void* fn_80201B3C();
extern void fn_80201E78(Vec3*, void*);
extern int fn_801AC9F4(u16, int, Vec3*, int);
extern void fn_800A2DBC(Object800A1DA0*);

int fn_800A1DA0(Object800A1DA0* object, u8 chance)
{
    Object800A1DA0* current = object;
    int result = 0;
    u8 threshold = chance;
    Vec3 position;
    Vec3 position_copy;
    u16 sound;
    void* source;

    if (threshold == 0xFF || current->timer == 0) {
        if (current->index >= 0) {
            u8 random = (u8)fn_800FBFB0();
            if (threshold != 0 && random <= threshold) {
                u8* entry = current->data;
                u32 value;
                entry += current->index * 2;
                value = *(u16*)(entry + 8);
                sound = value;
                if (value != 0) {
                    source = fn_80201B3C();
                    if (source != 0) {
                        fn_80201E78(&position_copy, source);
                        position = position_copy;
                        fn_801AC9F4(sound, 100, &position, 5);
                        fn_800A2DBC(current);
                        result = 1;
                    }
                }
            }
        }
    }
    return result;
}
