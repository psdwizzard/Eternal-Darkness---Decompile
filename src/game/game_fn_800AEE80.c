typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Event {
    u8 pad00[8];
    short counter;
} Event;

typedef struct Entry {
    u32 callbacks[4];
    u32 arguments[4];
    u16 ids[4];
    u8 index;
    u8 lastIndex;
    u8 resetIndex;
    u8 limit;
} Entry;

typedef struct Owner {
    u8 pad00[0x40];
    Entry entries[3];
} Owner;

extern Event *fn_8006ED3C(Owner *, int, int *);
extern void fn_8006BEE4(int *, int);
extern int fn_8006EA4C(Owner *);
extern void fn_8006DEF8(Owner *, u32, u32, u32, u16);
extern int fn_80070CD8(int);
extern void fn_801A9A40(int, int, int);
extern void fn_800AEFF4(void);
extern void (*lbl_8064C8C4)(void);
extern int lbl_8064C9D4, lbl_8064C9D8, lbl_8064C9DC, lbl_8064C9E0;

int fn_800AEE80(Owner *owner)
{
    int index;
    Event *event;
    int ready;
    int result = 0;
    int i;

    event = fn_8006ED3C(owner, 0x1F, &index);
    lbl_8064C8C4 = fn_800AEFF4;
    ready = fn_80070CD8(2);
    if (--lbl_8064C9D8 < 0) {
        lbl_8064C9D8 = 0;
    }
    if ((lbl_8064C9D4 -= 2) < 0) {
        lbl_8064C9D4 = 0;
    }
    fn_801A9A40(5, lbl_8064C9D4, lbl_8064C9D4);
    event->counter++;
    if (event->counter > 60) {
        fn_8006BEE4((int *)event, (int)fn_8006EA4C);
        lbl_8064C8C4 = 0;
        lbl_8064C9D8 = 20;
        fn_801A9A40(5, lbl_8064C9E0, lbl_8064C9DC);
        result = 1;
    }
    if (ready == 0) {
        lbl_8064C8C4 = 0;
        fn_8006BEE4((int *)event, (int)fn_8006EA4C);
        lbl_8064C9D8 = 20;
        i = 0;
        do {
            owner->entries[index].index = i;
            fn_8006DEF8(owner, 0x1F, 0, 0, 1);
            i++;
        } while (i < 4);
        fn_801A9A40(5, lbl_8064C9E0, lbl_8064C9DC);
        result = 1;
    }
    return result;
}
