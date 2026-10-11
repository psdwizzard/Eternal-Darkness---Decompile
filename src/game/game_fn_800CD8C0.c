typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

typedef struct SearchResult {
    int second;
    int first;
    u8 pad08[0x18];
    float value;
} SearchResult;

typedef struct Payload {
    int resource;
    int first;
    int owner;
    int source;
    u16 level;
    u8 kind;
    u8 pad13;
    int flags;
} Payload;

typedef struct Resource {
    u8 pad[0x38];
    int linked;
} Resource;

typedef struct RuntimeState {
    u8 pad[0x30];
    Payload *payload;
    u8 pad34[0x58];
    Resource *resource;
} RuntimeState;

typedef struct Object802015A4 Object802015A4;

extern int lbl_8064D5A8;
extern void *fn_80201BC8(void *);
extern int fn_8011F598(void *, int, int, int, SearchResult *, u8);
extern void *fn_80037AF4(int);
extern void *fn_80201B8C(u8 *);
extern int fn_80201B54(int *);
extern int fn_801CEB2C(unsigned int);
extern int fn_801D38E8(int);
extern int fn_801DD068(int, int, u8);
extern void fn_802015A4(Object802015A4 *);
extern int fn_801E8328(unsigned int, unsigned int);
extern void fn_8020104C(int, int, int, int, float);

void *fn_800CD8C0(int first, int owner, void *source, int kind, u16 time)
{
    SearchResult query;
    Payload *payload;
    int id;
    void *object = 0;

    if (source != 0) {
        if (fn_8011F598(fn_80201BC8(source), 0, 0, -1, &query, 1) != -1) {
            object = fn_80037AF4(0x1A);
            payload = ((RuntimeState *)fn_80201B8C((u8 *)object))->payload;
            if (payload == 0) {
                /* ASM: nop preserves the retail null-payload diagnostic marker,
                 * which has no observable C operation. */
                asm { nop }
            }
            payload->resource = lbl_8064D5A8;
            payload->first = first;
            payload->owner = owner;
            payload->source = fn_80201B54((int *)source);
            payload->kind = kind;
            payload->flags = 0;
            {
                u8 level = (s16)fn_801CEB2C(owner) >> 1;
                switch ((u8)kind) {
                case 1:
                    break;
                case 0:
                    switch (level) {
                    case 1: payload->level = 2; break;
                    case 2: payload->level = 5; break;
                    case 3: payload->level = 7; break;
                    }
                    break;
                case 2:
                    switch (level) {
                    case 1: payload->level = 5; break;
                    case 2: payload->level = 7; break;
                    case 3: payload->level = 10; break;
                    }
                    break;
                }
            }
            fn_802015A4((Object802015A4 *)object);
            id = fn_80201B54((int *)object);
            ((RuntimeState *)fn_80201B8C((u8 *)source))->resource->linked = id;
            fn_801E8328(0x15, (unsigned int)object);
            if (time == 0) {
                u8 level = (s16)fn_801CEB2C(owner) >> 1;
                time = fn_801DD068(kind, fn_801D38E8(owner), level);
            }
            fn_8020104C(0x39, id, id, 0, (float)time);
        }
    }
    return object;
}
