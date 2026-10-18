typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long size_t;
typedef float Mtx[3][4];

typedef struct Owner {
    u8 pad00[0x174];
    struct Owner* parent;
    u8 pad178[0xDC];
    u32 flags;
} Owner;

typedef struct Entry {
    Owner* object;
    u32 count;
    s32 mode;
    float distance_squared;
} Entry;

typedef int (*CompareProc)(const void*, const void*);

extern Entry lbl_804ED180[];
extern u32 lbl_8064CEE4;
extern float lbl_806500A0;

extern s32 fn_800473A4(void);
extern void qsort(void*, size_t, size_t, CompareProc);
extern u32 fn_8011FAF4(void*);
extern int fn_801209DC(Entry*, Entry*);
extern void fn_80121114(Owner*, u32, s32, s32, s32, s32);
extern void fn_801ECC4C(void);
extern s32 fn_801ED59C(s32, s32);
extern void fn_801ED5F4(s32, s32, s16, float*, Mtx, float);
extern s32 fn_801EF384(void);
extern void fn_801F47F8(void);
extern u32 LCQueueLength(void);
extern void LCQueueWait(s32);
extern void GXFlush(void);
extern void GXSetCullMode(s32);
extern void GXSetAlphaCompare(s32, s32, s32, s32, s32);
extern void GXSetColorUpdate(u8);
extern void GXSetAlphaUpdate(u8);
extern void GXSetZMode(u8, s32, u8);

void fn_80120BFC(s32 translucent)
{
    s32 special = fn_800473A4();
    s32 deferred = 0;
    s32 outline = fn_801EF384();
    float* distance;
    s32 i;
    s32 draw_index;
    Entry* entry;

    GXSetAlphaCompare(4, 4, 0, 3, 0xFF);
    if (translucent == 0) {
        /* Keep children at their parent's distance before sorting the queue. */
        for (i = 0; i < (s32)lbl_8064CEE4; i++) {
            entry = &lbl_804ED180[i];
            if (entry->object->parent != 0) {
                s32 j;

                distance = &entry->distance_squared;
                for (j = 0; j < (s32)lbl_8064CEE4; j++) {
                    if (lbl_804ED180[i].object->parent == lbl_804ED180[j].object &&
                        *distance != lbl_804ED180[j].distance_squared) {
                        i = 0;
                        *distance = lbl_804ED180[j].distance_squared;
                        break;
                    }
                }
            }
        }
        qsort(lbl_804ED180, lbl_8064CEE4, sizeof(Entry),
                    (CompareProc)fn_801209DC);
        LCQueueLength();
        LCQueueWait(0);
        {
            Entry* primary_entry;

            primary_entry = lbl_804ED180;
            fn_801ED59C(1, 1);
            for (draw_index = 0; draw_index < (s32)lbl_8064CEE4; draw_index++) {
                u32 attr = fn_8011FAF4(primary_entry->object);
                if (special && (primary_entry->object->flags & 0x04000000)) {
                    deferred = 1;
                    primary_entry++;
                    continue;
                }
                if (attr & 0x40) {
                    primary_entry++;
                    continue;
                }
                GXSetCullMode(1);
                fn_80121114(primary_entry->object, primary_entry->count,
                            primary_entry->mode, 0, outline, 1);
                primary_entry++;
            }
            primary_entry = lbl_804ED180;
            fn_801ED59C(0, 1);
            for (draw_index = 0; draw_index < (s32)lbl_8064CEE4; draw_index++) {
                u32 attr = fn_8011FAF4(primary_entry->object);
                if (special && (primary_entry->object->flags & 0x04000000)) {
                    deferred = 1;
                    primary_entry++;
                    continue;
                }
                if (attr & 0x40) {
                    primary_entry++;
                    continue;
                }
                GXSetCullMode(1);
                fn_80121114(primary_entry->object, primary_entry->count,
                            primary_entry->mode, 1, outline, 1);
                primary_entry->object->flags &= ~0x80000u;
                primary_entry++;
            }
        }
        if (deferred) {
            fn_801F47F8();
            for (draw_index = 0, entry = lbl_804ED180;
                 draw_index < (s32)lbl_8064CEE4; draw_index++) {
                if (fn_8011FAF4(entry->object) & 0x40) {
                    entry++;
                    continue;
                }
                GXSetCullMode(1);
                fn_80121114(entry->object, entry->count, entry->mode, 0, outline, 1);
                entry++;
            }
            for (draw_index = 0, entry = lbl_804ED180;
                 draw_index < (s32)lbl_8064CEE4; draw_index++) {
                if (fn_8011FAF4(entry->object) & 0x40) {
                    entry++;
                    continue;
                }
                GXSetCullMode(1);
                fn_80121114(entry->object, entry->count, entry->mode, 1, outline, 1);
                entry->object->flags &= ~0x80000u;
                entry++;
            }
        }
    } else {
        GXSetCullMode(1);
        GXSetAlphaUpdate(0);
        GXSetColorUpdate(0);
        GXSetZMode(1, 4, 1);
        for (draw_index = 0, entry = lbl_804ED180;
             draw_index < (s32)lbl_8064CEE4; entry++, draw_index++) {
            if (fn_8011FAF4(entry->object) & 0x40) {
                fn_80121114(entry->object, entry->count, entry->mode, 0, outline, 0);
                fn_80121114(entry->object, entry->count, entry->mode, 1, outline, 0);
            }
        }
        GXSetZMode(1, 3, 1);
        GXSetAlphaUpdate(0);
        GXSetColorUpdate(1);
        fn_801ED59C(1, 1);
        for (draw_index = 0, entry = lbl_804ED180;
             draw_index < (s32)lbl_8064CEE4; entry++, draw_index++) {
            if (fn_8011FAF4(entry->object) & 0x40) {
                fn_80121114(entry->object, entry->count, entry->mode, 0, outline, 1);
            }
        }
        GXSetCullMode(1);
        fn_801ED59C(0, 1);
        for (draw_index = 0, entry = lbl_804ED180;
             draw_index < (s32)lbl_8064CEE4; entry++, draw_index++) {
            if (fn_8011FAF4(entry->object) & 0x40) {
                fn_80121114(entry->object, entry->count, entry->mode, 1, outline, 1);
            }
            entry->object->flags &= ~0x80000u;
        }
    }
    fn_801ED5F4(0, 0, 0, 0, 0, lbl_806500A0);
    fn_801ECC4C();
    GXFlush();
    GXSetAlphaCompare(7, 0, 0, 3, 0xFF);
    fn_801ED59C(1, 1);
}
