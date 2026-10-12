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

void fn_80129FD0(register Owner* input_owner, register int input_amount, register int input_flag)
{
    float value;
    /* Declaration order preserves MWCC register allocation across both loops. */
    register Object* object;
    register int result;
    register int amount;
    register Owner* owner;
    register int count;
    register int i;
    register TransformChannel* channel;
    register int flag;
    register Definition* definition;
    register int j;
    register int list_offset;
    register int state_offset;
    register int value_offset;

    /* ASM: mr/li preserves entry register allocation and assignment order;
     * MWCC reallocates the C locals and moves the definition load ahead of li. */
    asm {
        mr owner, input_owner
        mr amount, input_amount
        mr flag, input_flag
        li result, 0
    }
    definition = owner->definition;
    object = fn_80128E30(owner)->animation->object;
    count = definition->count;
    channel = object->channels;

    if (fn_8012927C(owner) != 0xFFFF) {
        count++;
    }
    for (i = 0; i < count; channel++, i++) {
        if (channel->translation_count || channel->rotation_count) {
            fn_80127658(owner, i, (void*)amount, flag);
        }
    }
    for (j = 0, value_offset = 0, state_offset = 0, list_offset = 0;
         j < 32; j++, value_offset += 0x28, state_offset += 0x18, list_offset += 8) {
        Object* current = (Object*)((u32)object + list_offset);
        if (current->lists[0].count) {
            if (!owner->states) {
                break;
            }
            result |= fn_80126A00(&current->lists[0],
                                 (SearchState*)((u8*)owner->states + state_offset),
                                 amount, &value);
            if (result == 0 &&
                !(((ValueChannel*)((u8*)owner->values + value_offset))->flags & 8)) {
                fn_80124664(owner, j, 0, value);
            }
        }
    }
}
