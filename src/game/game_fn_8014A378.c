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

extern SlotSet* fn_80156938(void*);
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
extern unsigned int fn_800FBFB0(void);
#define fn_800FBFB0() ((int)fn_800FBFB0())
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

void fn_8014A378(void* left, void* right)
{
    if (left == 0) {
        return;
    }
    if (right == 0) {
        return;
    }

    {
    u16 slotBit;
    int rightFlags;
    u16 bit;
    int i;
    int count;
    SlotSet* leftSet;
    SlotSet* rightSet;

    rightSet = fn_80156938(right);
    leftSet = fn_80156938(left);
    rightFlags = rightSet != 0 ? fn_80193860(rightSet) : 0x40000;
    count = leftSet->count;

    for (bit = 1, i = 0; i < count; bit = slotBit << 1, i++) {
        void* object;
        u32 flags;

        slotBit = bit;
        if ((leftSet->mask & slotBit) == 0 || (object = leftSet->objects[i]) == 0) {
            continue;
        }
        flags = fn_80193860(object);

        if (rightFlags & 0x40000) {
            leftSet->active = 1;
            fn_801938C8(object, 0);
            if (fn_8017FD98(object)) {
                fn_801938D8(object, (flags | 0x40000) & ~0x200);
            } else {
                fn_8017FD6C(object);
                leftSet->mask &= ~slotBit;
            }
        } else if (!fn_801562DC(left)) {
            u8 lower = fn_80193870(rightSet);
            u8 upper = fn_80193888(rightSet);
            if (lower >= upper) {
                u8 state = fn_80193878(object);
                if (state == 0) {
                    state = fn_80193868(object);
                    if (state == 0) {
                        if (flags & 1) {
                            fn_801938B8(object, 0);
                            fn_801938B0(object, 2);
                        } else if (flags & 2) {
                            int random = fn_800FBFB0();
                            int span = (u8)upper - 4;
                            u8 first = random % span;
                            int remainder;
                            fn_801938B8(object, first);
                            remainder = span - first;
                            fn_801938B0(object, first + (fn_800FBFB0() % remainder) + 2);
                        } else if (flags & 4) {
                            fn_801938B8(object, (u8)(upper - 5));
                            fn_801938B0(object, (u8)(upper - 3));
                        }
                        fn_8017FE1C(object, fn_801939DC);
                        state = fn_80193890(object);
                    } else {
                        state--;
                    }
                    fn_801938C0(object, state);
                    fn_801938C8(object, fn_80193898(object));
                } else {
                    fn_801938C8(object, state - 1);
                }
            }
        }

        if (rightSet != 0 && fn_8017FD98(object)) {
            fn_8014B454(rightSet, fn_8017FDE4(object), fn_80193858(object), 0, 0);
            fn_8014B454(rightSet, fn_801938A8(object), fn_80193850(object), 0, 0);
        }
    }

    if (fn_80157034(right)) {
        leftSet->active = 1;
        for (bit = 1, i = 0; i < count; bit = slotBit << 1, i++) {
            void* object;
            slotBit = bit;
            if ((leftSet->mask & slotBit) != 0 && (object = leftSet->objects[i]) != 0) {
                fn_8017FD6C(object);
                leftSet->mask &= ~slotBit;
            }
        }
    }
    }
}
