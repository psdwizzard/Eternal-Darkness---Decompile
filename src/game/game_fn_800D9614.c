typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Actor {
    u8 pad0[0x84];
    u16 flags;
    u8 pad86[0x22];
    void *handle;
    u8 position[12];
    u8 direction[12];
} Actor;

typedef struct Runtime {
    u8 pad0[0x64];
    Actor *actor;
    u8 pad68[0x2C];
    void *resource;
} Runtime;

extern void *fn_80201B8C();
extern void *fn_801D5898(void *, void *, void *, int, int, int, int, int, int, int,
                         int, int, int, int, int, int, int);

int fn_800D9614(void *unused, void *object)
{
    Runtime *runtime = ((Runtime *)fn_80201B8C(object));
    Actor *actor;

    (void)unused;
    if (runtime != 0) {
        actor = runtime->actor;
        if ((actor->flags & 8) == 0) {
            actor->flags |= 8;
            actor->handle = fn_801D5898(actor->position, actor->direction,
                runtime->resource, 0, 0, 6, 0x40, 0x20, 16, 4, 1, 17, 10, 30, 4,
                8, 0x30000);
        }
    }
    return 1;
}
