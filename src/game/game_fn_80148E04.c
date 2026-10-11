typedef unsigned char u8;
typedef unsigned int u32;

typedef struct InstanceList {
    u8 count;
    u8 pad[5];
    unsigned short state;
    u32 indices[32];
    void* instances[32];
} InstanceList;

extern void* fn_80156938(void*);
extern int fn_801800F8(void*);
extern int fn_80180114(void*);
/* This wrapper forwards the bit-test result from fn_80180430. */
extern int fn_80180138(void*, u8);
extern int fn_80180170(void*, u32);
extern int fn_8017FED4(void*);
extern int fn_8015C9F0(void);
extern u8 fn_8017FDFC(void*);
extern u32 fn_8017FF7C(void*, int, int);
extern void fn_80185008(u8*, void*);
extern void fn_801850E4(u8*);
extern void fn_801850CC(u8*);
extern u8 fn_80185494(const u8*);
extern void fn_801853F0(u8*, const void*, u8);
extern int lbl_8064D18C;

void fn_80148E04(void* object, void* other)
{
    InstanceList* target;
    int count;
    int j;
    u8 index;
    int otherCount;
    int i;
    u8* otherList;
    InstanceList* list;
    InstanceList* current;

    list = fn_80156938(object);
    otherList = fn_80156938(other);
    count = list->count;
    i = 0;
    otherCount = *otherList;
    target = (InstanceList*)otherList;
    /* Advance the parallel index and instance arrays together. */
    for (; i < otherCount; target = (InstanceList*)((u8*)target + 4), i++) {
        if (fn_801800F8(target->instances[0])) {
            current = list;
            j = 0;
            for (; j < count; current = (InstanceList*)((u8*)current + 4), j++) {
                index = current->indices[0];
                if (fn_80180138(target->instances[0], index)) {
                    fn_80185008(current->instances[0], target->instances[0]);
                    if (fn_80180170(target->instances[0], index) ||
                        fn_8017FED4(target->instances[0])) {
                        fn_801850E4(current->instances[0]);
                    } else if (lbl_8064D18C != 0x53 && !fn_8015C9F0() &&
                               fn_8017FDFC(target->instances[0])) {
                        u32 color;
                        u32 sourceColor;
                        sourceColor = fn_8017FF7C(target->instances[0], index, 0);
                        color = fn_8017FF7C(current->instances[0], 0, 0);
                        if (((u8*)&sourceColor)[3] != ((u8*)&color)[3]) {
                            u8 amount;
                            ((u8*)&color)[3] = ((u8*)&sourceColor)[3];
                            amount = fn_80185494(current->instances[0]);
                            fn_801853F0(current->instances[0], &color, amount);
                        }
                    }
                } else {
                    u8 amount;
                    u32 color = fn_8017FF7C(current->instances[0], 0, 0);
                    ((u8*)&color)[3] = 0;
                    amount = fn_80185494(current->instances[0]);
                    fn_801853F0(current->instances[0], &color, amount);
                }
            }
            list->state = 2;
        }
        if (fn_80180114(target->instances[0])) {
            list->state = 1;
            current = list;
            j = 0;
            for (; j < count; current = (InstanceList*)((u8*)current + 4), j++) {
                fn_801850CC(current->instances[0]);
            }
        }
    }
}
