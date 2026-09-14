typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3s {
    short x, y, z;
} Vec3s;

typedef struct Vec3f {
    float x, y, z;
} Vec3f;

typedef struct CommandDescriptor {
    u32 value00;
    u8 pad04[0x14];
    Vec3f position;
    u8 bytes24[4];
    u8 pad28[0xB];
    u8 byte33;
    u8 byte34;
    u8 pad35[0xF];
    int (*callback)(void*);
    u8 pad48[0x28];
} CommandDescriptor;

typedef struct ResourceRef {
    u32 value;
} ResourceRef;

extern int fn_8016A598(void*);
extern double fn_8016A694(void*, int);
extern Vec3s* fn_8016A784(void*, int);
extern void fn_80163BB4(void*, const char*, ...);
extern void fn_8014CBC0(ResourceRef*);
extern void fn_8014C37C(int, ResourceRef*);
extern void fn_801FE8DC(CommandDescriptor*, float, float, float);
extern int fn_801754D0(void*);
extern const char lbl_8024FF00[];
extern const float lbl_806506B8;
extern const float lbl_80650704;
extern int lbl_8064D1E8;

static inline void set_value00(CommandDescriptor* descriptor, double value)
{
    descriptor->value00 = (u16)value;
}

int fn_801752B0(void* state)
{
    ResourceRef resource;
    Vec3s* source;
    CommandDescriptor command;

    if (fn_8016A598(state) != 6) {
        fn_80163BB4(state, lbl_8024FF00, 6, fn_8016A598(state));
        return 0;
    }

    fn_8014CBC0(&resource);
    source = fn_8016A784(state, 1);
    command.bytes24[0] = fn_8016A694(state, 2);
    command.bytes24[1] = fn_8016A694(state, 3);
    command.bytes24[2] = fn_8016A694(state, 4);
    command.bytes24[3] = fn_8016A694(state, 5);
    set_value00(&command, fn_8016A694(state, 6));
    command.position.x = source->x;
    command.position.y = source->y;
    command.position.z = source->z;
    command.byte34 = 2;
    command.callback = fn_801754D0;
    command.byte33 = 0;
    fn_801FE8DC(&command, lbl_806506B8, lbl_806506B8, lbl_80650704);
    fn_8014C37C(0, &resource);
    lbl_8064D1E8 = 1;
    return 0;
}
