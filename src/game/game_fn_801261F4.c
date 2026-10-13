typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* Keep the object opaque for callees that use their own layout views. */
typedef struct Object Object;

typedef struct Definition {
    u8 pad_00[8];
    u16 count;
} Definition;

typedef struct Channel {
    u8 pad_00[4];
    u32 value;
    u8 pad_08[8];
    u32 accum;
    u32 scale;
    u8 pad_18[0x14];
    u32 target;
    u32 target_scale;
    u8 pad_34[0x18];
} Channel;

/* Pooled working storage for objects with up to three channels. */
typedef struct SmallSlot {
    int flags;
    u32 frame;
    struct Owner* owner;
    Channel channels[4];
    u8 entries[0x30];
    u8 links[0x40];
    u8 nodes[0x500];
    u8 states[0x300];
    u8 active[4];
    u8 runtimes[0x888];
} SmallSlot;

/* Pooled working storage for large objects. */
typedef struct LargeSlot {
    int flags;
    u32 frame;
    struct Owner* owner;
    Channel channels[0x89];
    u8 entries[0x66C];
    u8 links[0x890];
    u8 nodes[0x500];
    u8 states[0x300];
    u8 active[0x8C];
    u8 runtimes[0x888];
} LargeSlot;

typedef struct Owner {
    u8 pad_000[0x3C];
    Definition* definition;
    u8* runtimes;
    u8 pad_044[0x110];
    u8* entries;
    u8* links;
    u8* states;
    Channel* channels;
    u8 pad_164[0xF0];
    u32 flags;
    u8 pad_258[0x44];
    u8* nodes;
    void* slot;
    u8 pad_2A4[4];
    u8* active;
} Owner;

/* Owner storage comes from the small-slot pool. */
#define OWNER_SMALL_SLOT 0x10000000U

extern void* memset(void*, int, unsigned long);
extern void fn_8011F7E0(void*, int);
extern void fn_80125ECC(Owner*);
extern void fn_80126680(Object*);
extern void fn_80126880(void*);
extern void fn_8012BFE4(u8*);

extern LargeSlot lbl_80514AE0[20];
extern SmallSlot lbl_8056FA80[48];
extern LargeSlot lbl_805A6500;
extern int lbl_8064CF20;
extern int lbl_8064CF24;
extern u32 lbl_8064D5A8;

static void clear_buffers(Owner* owner)
{
    memset(owner->entries, 0, owner->definition->count * 0xC);
    memset(owner->links, 0, owner->definition->count * 0x10);
    memset(owner->states, 0, 0x300);
    memset(owner->nodes, 0, 0x500);
    fn_80126680((Object*)owner);
}

int fn_801261F4(Owner* owner)
{
    LargeSlot* large = 0;
    SmallSlot* small;
    int i;
    int j;

    if (owner == 0) {
        return 0;
    }
    if (owner->slot == 0 || owner->slot == &lbl_805A6500) {
        if (owner->definition->count <= 3 && lbl_8064CF20 < 48) {
            for (i = 0; i < 48; i++) {
                if (lbl_8056FA80[i].flags == 0) {
                    owner->flags |= OWNER_SMALL_SLOT;
                    small = &lbl_8056FA80[i];
                    owner->channels = small->channels;
                    owner->entries = small->entries;
                    owner->links = small->links;
                    owner->nodes = small->nodes;
                    owner->states = small->states;
                    owner->active = small->active;
                    owner->runtimes = small->runtimes;
                    owner->slot = small;
                    small->owner = owner;
                    small->flags = 3;
                    small->frame = lbl_8064D5A8;
                    lbl_8064CF20++;
                    clear_buffers(owner);

                    for (j = 0; j < 3; j++) {
                        lbl_8056FA80[i].channels[j].value = 0;
                        lbl_8056FA80[i].channels[j].accum = 0;
                        lbl_8056FA80[i].channels[j].scale = 0x60000;
                        lbl_8056FA80[i].channels[j].target = 0;
                        lbl_8056FA80[i].channels[j].target_scale = 0x60000;
                        lbl_8056FA80[i].active[j] = 0;
                    }
                    fn_80125ECC(owner);
                    fn_8012BFE4((u8*)owner);
                    return 1;
                }
            }
        } else {
            for (i = 0; i < 20; i++) {
                if (lbl_80514AE0[i].flags == 0) {
                    large = &lbl_80514AE0[i];
                    break;
                }
            }
            if (large == 0) {
                large = &lbl_805A6500;
                if (large->flags != 0 && large->owner != owner) {
                    fn_8011F7E0(large->owner, 0);
                    fn_80126880(large->owner);
                }
            }

            owner->flags &= ~OWNER_SMALL_SLOT;
            owner->channels = large->channels;
            owner->entries = large->entries;
            owner->links = large->links;
            owner->nodes = large->nodes;
            owner->states = large->states;
            owner->active = large->active;
            owner->runtimes = large->runtimes;
            owner->slot = large;
            large->owner = owner;
            large->frame = lbl_8064D5A8;
            large->flags = 3;
            if (large == &lbl_805A6500) {
                large->flags |= 4;
            }
            lbl_8064CF24++;
            clear_buffers(owner);

            for (i = 0; i < 0x89; i++) {
                large->channels[i].value = 0;
                large->channels[i].accum = 0;
                large->channels[i].scale = 0x60000;
                large->channels[i].target = 0;
                large->channels[i].target_scale = 0x60000;
                large->active[i] = 0;
            }
            fn_80125ECC(owner);
            fn_8012BFE4((u8*)owner);
            return 1;
        }
    }
    return 0;
}
