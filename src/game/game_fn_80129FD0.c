typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Definition {
    u8 pad0[8];
    u16 count;
} Definition;

typedef struct TransformChannel {
    u16 translation_count;
    u16 pad2;
    void* translations;
    u16 rotation_count;
    u16 padA;
    void* rotations;
} TransformChannel;

typedef struct Entry {
    u32 key;
    float value;
} Entry;

typedef struct EntryList {
    u32 count;
    Entry* entries;
} EntryList;

typedef struct Object {
    TransformChannel* channels;
    u8 pad4[0xC];
    EntryList lists[32];
} Object;

typedef struct Animation {
    u8 pad0[4];
    Object* object;
} Animation;

typedef struct Runtime {
    u8 pad0[0xB8];
    Animation* animation;
} Runtime;

typedef struct SearchState {
    u32 key;
    int direction;
    int distance;
    int span;
    Entry* current;
    Entry* previous;
} SearchState;

typedef struct ValueChannel {
    float value, upper, lower, rise, fall, delta;
    int repeats, delay, timer;
    u32 flags;
} ValueChannel;

typedef struct Owner {
    u8 pad0[0x3C];
    Definition* definition;
    u8 pad40[0x11C];
    SearchState* states;
    u8 pad160[0x13C];
    ValueChannel* values;
} Owner;

extern Runtime* fn_80128E30(Owner*);
extern u16 fn_8012927C(Owner*);
extern void fn_80127658(Owner*, int, void*, int);
extern int fn_80126A00(EntryList*, SearchState*, int, float*);
extern void fn_80124664(Owner*, int, u32, float);

void fn_80129FD0(Owner* owner, int amount, int flag)
{
    float value;
    Object* object;
    int result = 0;
    int i;
    int count;
    TransformChannel* channel;
    Definition* definition;
    int j;

    definition = owner->definition;
    object = fn_80128E30(owner)->animation->object;
    count = definition->count;
    channel = object->channels;

    if (fn_8012927C(owner) != 0xFFFF) {
        count++;
    }
    for (i = 0; i < count; i++) {
        if (channel[i].translation_count || channel[i].rotation_count) {
            /* The updater currently declares its numeric value as void*. */
            fn_80127658(owner, i, (void*)amount, flag);
        }
    }
    j = 0;
    do {
        u32 index = j;
        if (object->lists[index].count) {
            if (!owner->states) {
                break;
            }
            result |= fn_80126A00(&object->lists[index], &owner->states[index],
                                 amount, &value);
            if (result == 0 && !(owner->values[index].flags & 8)) {
                fn_80124664(owner, j, 0, value);
            }
        }
        j++;
    } while (j < 32);
}
