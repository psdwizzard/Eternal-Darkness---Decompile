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
    u8 pad04[4];
    int value08;
    int value0C;
    u8 pad10[8];
    Vec3f position;
    u8 bytes24[4];
    u16 value28;
    u8 pad2A[9];
    u8 byte33;
    u8 byte34;
    u8 pad35[0xF];
    void (*callback)(void);
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
extern void fn_8014C988(ResourceRef*, int);
extern void fn_8014C37C(int, ResourceRef*);
extern void fn_801FE8DC(CommandDescriptor*, float, float, float);
extern void fn_801FD8F0(void);
extern const char lbl_8024FF00[];
extern const float lbl_806506B8;
extern const float lbl_80650700;

#pragma opt_common_subs off
#pragma opt_propagation off
int fn_80174F2C(void* state)
{
    ResourceRef resource;
    Vec3s* source;
    int resource_id;
    CommandDescriptor* descriptor;
    CommandDescriptor command;
    u16 value00;

    if (fn_8016A598(state) != 10) {
        fn_80163BB4(state, lbl_8024FF00, 10, fn_8016A598(state));
        return 0;
    }

    fn_8014CBC0(&resource);
    source = fn_8016A784(state, 1);
    command.bytes24[0] = fn_8016A694(state, 2);
    command.bytes24[1] = fn_8016A694(state, 3);
    command.bytes24[2] = fn_8016A694(state, 4);
    command.bytes24[3] = fn_8016A694(state, 5);
    resource_id = fn_8016A694(state, 6);
    command.value28 = fn_8016A694(state, 7);
    value00 = fn_8016A694(state, 8);
    descriptor = &command;
    descriptor->value00 = value00;
    descriptor->value08 = fn_8016A694(state, 9);
    descriptor->value0C = fn_8016A694(state, 10);
    command.byte34 = 2;
    command.position.x = source->x;
    command.position.y = source->y;
    command.position.z = source->z;
    command.callback = fn_801FD8F0;
    command.byte33 = 0;
    fn_801FE8DC(descriptor, lbl_806506B8, lbl_806506B8, lbl_80650700);
    fn_8014C988(&resource, resource_id);
    fn_8014C37C(0, &resource);
    return 0;
}
#pragma opt_propagation reset
#pragma opt_common_subs reset
