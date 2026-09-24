typedef unsigned char u8;

typedef struct Vec3s {
    short x;
    short y;
    short z;
} Vec3s;

typedef struct Vec3f {
    float x;
    float y;
    float z;
} Vec3f;

typedef struct EffectDescriptor {
    u8 bytes[144];
} EffectDescriptor;

extern int fn_8016A598(void*);
extern double fn_8016A694(void*, int);
extern void fn_80163BB4(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern int fn_8015C4A4(int, int);
extern Vec3s* fn_80158ABC(int, int, void*);
extern void fn_801839A4(EffectDescriptor*);
extern void fn_801839D8(void);
extern void* fn_80148008(Vec3f*, const Vec3s*, EffectDescriptor*, void (*)(void));
extern void* fn_80156938(void*);
extern void fn_8017FF1C(void*, int);
extern Vec3s lbl_806506EC;
extern const char lbl_8024FF00[];

int fn_80173BDC(void* arg)
{
    void* state = arg;
    int resource;
    int kind;
    Vec3s* source;
    Vec3s rotation;
    Vec3f position;
    Vec3f submit_position;
    EffectDescriptor descriptor;

    rotation = lbl_806506EC;

    if (fn_8016A598(state) != 2) {
        fn_80163BB4(state, lbl_8024FF00, 2, fn_8016A598(state));
        return 0;
    }

    resource = fn_800F5C54(fn_8016A694(state, 1));
    kind = fn_8016A694(state, 2);
    source = fn_80158ABC(fn_8015C4A4(resource, 2), 2, 0);
    position.x = source->x;
    position.y = source->y;
    position.z = source->z;

    fn_801839A4(&descriptor);
    {
        unsigned int x = ((unsigned int*)&position)[0];
        unsigned int y = ((unsigned int*)&position)[1];
        unsigned int z = ((unsigned int*)&position)[2];
        descriptor.bytes[20] = kind;
        ((unsigned int*)&submit_position)[0] = x;
        ((unsigned int*)&submit_position)[1] = y;
        ((unsigned int*)&submit_position)[2] = z;
    }
    {
        void* effect = fn_80148008(&submit_position, &rotation, &descriptor,
                                   fn_801839D8);
        if (effect != 0) {
            fn_8017FF1C(fn_80156938(effect), 4);
        }
    }
    return 0;
}
