typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SlotSet {
    u8 count;
    u8 pad1[3];
    u16 mask;
    u16 active;
    u8 pad8[0x80];
    void* objects[16];
} SlotSet;

extern void* fn_80156938();
extern u32 fn_80193860(void*);
extern void fn_801938C8(void*, u8);
extern u32 fn_8017FD98(void*);
extern void fn_801938D8(void*, u32);
extern void fn_8017FD6C(void*);
extern int fn_801562DC(void*);
extern u8 fn_80193870(void*);
extern u8 fn_80193888(void*);
extern u8 fn_80193878(void*);
extern u8 fn_80193868(void*);
extern void fn_801938B8(void*, u8);
extern void fn_801938B0(void*, u8);
extern int rand(void);
extern void fn_8017FE1C(void*, void*);
extern void fn_801939DC(void);
extern u8 fn_80193890(void*);
extern void fn_801938C0(void*, u8);
extern u8 fn_80193898(void*);
extern u32 fn_80193858(void*);
extern void* fn_8017FDE4(void*);
extern void fn_8014B454(void*, void*, u8, int, int);
extern u32 fn_80193850(void*);
extern void* fn_801938A8(void*);
extern int fn_80157034(void*);

void fn_8014A6BC(void* left, void* right)
{
    SlotSet* right_set = fn_80156938(right);
    SlotSet* left_set = fn_80156938(left);
    void* source = right_set->objects[0];
    int sourceFlags = source ? fn_80193860(source) : 0x40000;
    u8 count = left_set->count;
    u16 bit;
    int i;

    for (bit = 1, i = 0; i < count; i++, bit = bit << 1) {
        void* object;
        u32 flags;

        if (!(left_set->mask & bit)) {
            continue;
        }
        object = left_set->objects[i];
        if (!object) {
            continue;
        }
        flags = fn_80193860(object);
        if (sourceFlags & 0x40000) {
            left_set->active = 1;
            fn_801938C8(object, 0);
            if (fn_8017FD98(object)) {
                fn_801938D8(object, (flags | 0x40000) & ~0x200);
            } else {
                fn_8017FD6C(object);
                left_set->mask &= ~bit;
            }
        } else if (!fn_801562DC(left)) {
            u8 low = fn_80193870(source);
            u8 high = fn_80193888(source);
            u8 state = fn_80193878(object);

            if (!state) {
                state = fn_80193868(object);
                if (!state) {
                    int changed = 0;

                    if (flags & 1) {
                        fn_801938B8(object, 0);
                        fn_801938B0(object, 2);
                        changed = 1;
                    } else if (flags & 2) {
                        int random = rand();
                        int span = (u8)high - 4;
                        u8 first = random % span;

                        if (low >= first) {
                            fn_801938B8(object, first);
                            fn_801938B0(object, first + rand() % (span - first) + 2);
                            changed = 1;
                        }
                    } else if (flags & 4) {
                        u8 first = (u8)(high - 5);

                        if (low >= first) {
                            fn_801938B8(object, first);
                            fn_801938B0(object, (u8)(high - 3));
                            changed = 1;
                        }
                    }
                    if (changed) {
                        fn_8017FE1C(object, fn_801939DC);
                        state = fn_80193890(object);
                    }
                } else {
                    state--;
                }
                fn_801938C0(object, state);
                fn_801938C8(object, fn_80193898(object));
            } else {
                fn_801938C8(object, state - 1);
            }
        }
        if (source && fn_8017FD98(object)) {
            u8 value = fn_80193858(object);

            fn_8014B454(source, fn_8017FDE4(object), value, 0, 0);
            value = fn_80193850(object);
            fn_8014B454(source, fn_801938A8(object), value, 0, 0);
        }
    }

    if (fn_80157034(right)) {
        left_set->active = 1;
        for (i = 0, bit = 1; i < count; i++, bit = bit << 1) {
            void* object;

            if (left_set->mask & bit) {
                object = left_set->objects[i];
                if (object) {
                    fn_8017FD6C(object);
                    left_set->mask &= ~bit;
                }
            }
        }
    }
}
