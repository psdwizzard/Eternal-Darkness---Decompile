/* The body matches retail. Existing compiler settings emit GPR save/restore
 * helper calls instead of the retail stmw/lmw pair. */
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
extern void fn_800FBE38(void*, size_t, size_t, CompareProc);
extern u32 fn_8011FAF4(void*);
extern int fn_801209DC(Entry*, Entry*);
extern void fn_80121114(Owner*, u32, s32, s32, s32, s32);
extern void fn_801ECC4C(void);
extern s32 fn_801ED59C(s32, s32);
extern void fn_801ED5F4(s32, s32, s16, float*, Mtx, float);
extern s32 fn_801EF384(void);
extern void fn_801F47F8(void);
extern void fn_8020B9D8(void);
extern void fn_8020B9E4(s32);
extern void fn_80226378(void);
extern void fn_80226D28(s32);
extern void fn_8022A044(s32, s32, s32, s32, s32);
extern void fn_8022A6DC(u8);
extern void fn_8022A71C(u8);
extern void fn_8022A75C(u8, s32, u8);

void fn_80120BFC(s32 translucent)
{
    s32 special = fn_800473A4();
    s32 deferred = 0;
    s32 outline = fn_801EF384();
    float* distance;
    s32 i;
    s32 draw_index;
    Entry* entry;

    fn_8022A044(4, 4, 0, 3, 0xFF);
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
        fn_800FBE38(lbl_804ED180, lbl_8064CEE4, sizeof(Entry),
                    (CompareProc)fn_801209DC);
        fn_8020B9D8();
        fn_8020B9E4(0);
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
                fn_80226D28(1);
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
                fn_80226D28(1);
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
                fn_80226D28(1);
                fn_80121114(entry->object, entry->count, entry->mode, 0, outline, 1);
                entry++;
            }
            for (draw_index = 0, entry = lbl_804ED180;
                 draw_index < (s32)lbl_8064CEE4; draw_index++) {
                if (fn_8011FAF4(entry->object) & 0x40) {
                    entry++;
                    continue;
                }
                fn_80226D28(1);
                fn_80121114(entry->object, entry->count, entry->mode, 1, outline, 1);
                entry->object->flags &= ~0x80000u;
                entry++;
            }
        }
    } else {
        fn_80226D28(1);
        fn_8022A71C(0);
        fn_8022A6DC(0);
        fn_8022A75C(1, 4, 1);
        for (draw_index = 0, entry = lbl_804ED180;
             draw_index < (s32)lbl_8064CEE4; entry++, draw_index++) {
            if (fn_8011FAF4(entry->object) & 0x40) {
                fn_80121114(entry->object, entry->count, entry->mode, 0, outline, 0);
                fn_80121114(entry->object, entry->count, entry->mode, 1, outline, 0);
            }
        }
        fn_8022A75C(1, 3, 1);
        fn_8022A71C(0);
        fn_8022A6DC(1);
        fn_801ED59C(1, 1);
        for (draw_index = 0, entry = lbl_804ED180;
             draw_index < (s32)lbl_8064CEE4; entry++, draw_index++) {
            if (fn_8011FAF4(entry->object) & 0x40) {
                fn_80121114(entry->object, entry->count, entry->mode, 0, outline, 1);
            }
        }
        fn_80226D28(1);
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
    fn_80226378();
    fn_8022A044(7, 0, 0, 3, 0xFF);
    fn_801ED59C(1, 1);
}
