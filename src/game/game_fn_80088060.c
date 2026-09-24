typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Owner {
    u8 pad[0x160];
    u16 count;
} Owner;
typedef struct Work {
    u8 pad38[0x38];
    int object_id;
    u8 pad3C[0xC4 - 0x3C];
    Owner* owner;
} Work;

typedef struct Slot {
    u8 first;
    u8 second;
    u8 pad[0x2A];
} Slot;

typedef struct SlotView {
    u8 pad[0x6A];
    Slot slots[1];
} SlotView;

extern void* fn_80201814(int);
extern int lbl_8064C824;
extern void fn_801A6E04(int);
extern void* fn_8004918C(void);
extern void* fn_801A7778(void*);
extern int fn_801A7780(void*);
extern int fn_801A76B8(void*);
extern unsigned int fn_801578AC(void*);
extern unsigned int fn_800FBFB0(void);
extern void fn_8006ED3C(void*, int, int*);
extern void fn_80088D04(void);
extern void* lbl_8064C8C4;
extern u8 lbl_8064C91C;
extern u8 lbl_8064C91D;

/* The static pool is externalized to the existing rows at lbl_8031D3B8. */
static u16 row_first[10];
static u16 row_second[10];
static u16 row_third[10];

int fn_80088060(void* argument)
{
    SlotView* slot_view;
    u16* first;
    u16* second;
    u16* third;
    void* object;
    int kind;
    int index;
    Work* work = argument;

    slot_view = (SlotView*)work;
    fn_80201814(work->object_id);
    fn_801A6E04(lbl_8064C824);
    object = fn_8004918C();
    kind = fn_801578AC(fn_801A7778(object));
    lbl_8064C91C = 1;
    if (fn_801A7780(object) & 8) {
        switch (kind) {
        case 0x40: {
            int object_count = fn_801A76B8(object);

            lbl_8064C91C = 5;
            if ((u8)object_count > 1)
                lbl_8064C91C = 10;
            break;
        }
        default:
            lbl_8064C91C = 5;
            break;
        }
    } else {
        switch (kind) {
        case 2:
        case 0x80:
            if (work->owner->count > 1)
                lbl_8064C91C = 2;
            break;
        case 3:
            break;
        case 4:
        case 8:
            if (work->owner->count > 2)
                lbl_8064C91C = 3;
            break;
        }
    }
    if (work->owner->count != 0) {
        int i = 1;
        int limit;

        first = row_first;
        second = row_second;
        third = row_third;
        limit = lbl_8064C91C;

        first++;
        second++;
        third++;
        for (; i < limit; i++) {
            *first = (int)fn_800FBFB0() % 0x200;
            *second = (int)fn_800FBFB0() % 0x160;
            *third = 0x80 - ((int)fn_800FBFB0() & 0x3F);
            first++;
            second++;
            third++;
        }
    }
    fn_8006ED3C(work, 7, &index);
    lbl_8064C8C4 = fn_80088D04;
    if (lbl_8064C91D & 1) {
        slot_view->slots[index].first = 1;
        slot_view->slots[index].second = 4;
    } else {
        slot_view->slots[index].first = 2;
        slot_view->slots[index].second = 2;
    }
    return 1;
}
