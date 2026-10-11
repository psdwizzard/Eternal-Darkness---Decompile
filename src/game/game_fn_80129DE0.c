typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Definition {
    u8 pad0[8];
    u16 count;
} Definition;

typedef struct Channel {
    u16 translation_count;
    u16 pad2;
    void* translations;
    u16 rotation_count;
    u16 padA;
    void* rotations;
} Channel;

typedef struct Pair {
    u32 count;
    void* entries;
} Pair;

typedef struct Object {
    Channel* channels;
    u8 pad4[0xC];
    Pair pairs[32];
    u8 pad110[0x14];
    void* slot;
} Object;

typedef struct Animation {
    u8 pad0[4];
    Object* object;
} Animation;

typedef struct Runtime {
    u8 pad0[0xB8];
    Animation* animation;
    u8 padBC[0x38];
    u32 flags;
    u8 padF8[4];
    u16 state;
} Runtime;

typedef struct Owner {
    u8 pad0[0x3C];
    Definition* definition;
    u8 pad40[0x134];
    struct Owner* parent;
    u8 pad178[0xDC];
    u32 flags;
} Owner;

typedef struct Item { int packed; int kind; int value; } Item;

extern int fn_80134FF8(void*, Object*);
extern void fn_801292E0(void*, int*, int*);
extern void fn_80129D54(void*, int, Item*);
extern u16 fn_8012927C(Owner*);
extern void fn_80127230(Owner*, int, int, int);
extern void fn_80127178(Owner*, int, int);
extern void fn_80124664(Owner*, int, u32, float);
extern int fn_80201ADC(void);
extern void* fn_80201BC8(void*);
extern int fn_80046104(void);
extern int fn_8011FCE4(void*);
extern void fn_801396A4(int);
extern u32 fn_8011FA8C(void*, u32, u32);
extern const float lbl_806501A8;

void fn_80129DE0(register Owner* input_owner, register Runtime* input_runtime,
                 register int input_update, register int input_process_items)
{
    /* Local ordering preserves MWCC register allocation. */
    int item_count;
    int items;
    register int direction;
    int i;
    int count;
    int context;
    register Object* object;
    Owner* current;
    register Channel* channels;
    register int update;
    Pair* pair;
    register Runtime* runtime;
    register Owner* owner;
    register Definition* definition;
    register int process_items;
    Channel* channel;

    /* ASM: mr/li preserves the incoming argument-save order and initialization;
     * MWCC schedules the equivalent C assignments around the pointer loads. */
    asm {
        mr runtime, input_runtime
        mr owner, input_owner
        mr update, input_update
        mr process_items, input_process_items
        li direction, 1
    }
    definition = owner->definition;
    object = runtime->animation->object;
    fn_80134FF8(owner, object);
    channels = object->channels;
    if (runtime->flags & 2) {
        direction = -1;
    }
    if (process_items) {
        fn_801292E0(owner, &item_count, &items);
        if (item_count > 0) {
            fn_80129D54(runtime, item_count, (Item*)items);
        }
    }
    if (!(owner->flags & 0x400)) {
        update = 0;
    }
    count = definition->count;
    if (fn_8012927C(owner) != 0xFFFF) {
        count++;
    }
    for (i = 0; i < count; i++) {
        channel = &channels[i];
        if (channel->translation_count || channel->rotation_count) {
            fn_80127230(owner, i, direction, update);
        }
    }
    for (i = 0; i < 32; i++) {
        pair = &object->pairs[i];
        if (pair->count) {
            fn_80127178(owner, i, direction);
        } else {
            fn_80124664(owner, i, 0, lbl_806501A8);
        }
    }
    runtime->state = 4;
    owner->flags &= ~4U;
    owner->flags |= 0x400;
    context = fn_80201ADC();
    current = (u32)context != 0 ? fn_80201BC8((void*)context) : 0;
    if ((owner->flags & 0x1000) && owner == current && !fn_80046104()) {
        fn_801396A4(fn_8011FCE4(owner));
    }
    if (owner->parent == owner) {
        fn_8011FA8C(owner, 0x1000, 0);
    } else if (!(owner->parent->flags & 0x1000)) {
        fn_8011FA8C(owner, 0x1000, 0);
    }
}
