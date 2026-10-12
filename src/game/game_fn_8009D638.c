typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Context {
    u8 pad00[8];
    short count;
    u8 pad0A[0xE];
    u32 flags;
} Context;

typedef struct EventSlot {
    u8 pad00[0x28];
    u8 count;
    u8 last_index;
    u8 reset_index;
    u8 limit;
} EventSlot;

typedef struct Owner {
    u8 pad00[0x18];
    char name[0x28];
    EventSlot slots[3];
} Owner;

struct CallbackOwner;
extern Context *fn_8006ED3C(Owner *, int, int *);
extern int fn_8006EB60(struct CallbackOwner *);
extern void fn_8006BEE4(int *, int);
extern int fn_8009D760(Owner *);
extern int fn_8009D940(Owner *);
/* The scheduler stores callback and argument addresses as 32-bit words. */
extern void fn_8006DEF8();
extern char *fn_800FD40C(char *, const char *);
extern const char lbl_802453D8[];

void fn_8009D638(Owner *owner)
{
    int index;
    Context *context;
    int i;

    context = fn_8006ED3C(owner, 0x11, &index);
    fn_8006BEE4((int *)context, (int)fn_8006EB60);
    owner->slots[index].reset_index = 0;
    owner->slots[index].limit = 4;
    owner->slots[index].count = 4;
    fn_8006DEF8(owner, 0x11, fn_8009D760, owner, 500);
    for (i = 0; i < 3; i++) {
        owner->slots[index].count = i;
        fn_8006DEF8(owner, 0x11, fn_8009D940, owner, 50);
    }
    owner->slots[index].count = 0;
    fn_800FD40C(owner->name, lbl_802453D8);
    context->flags |= 0x10;
    context->count = 0;
}
