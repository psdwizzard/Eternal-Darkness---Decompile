typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Owner {
    u8 pad[0x159];
    u8 state;
    u8 pad15A[2];
    void* data;
    u16 value160;
} Owner;

typedef struct WorkEntry {
    u8 mode;
    u8 pad01;
    u8 enabled_a;
    u8 enabled_b;
    u8 pad04[0x28];
} WorkEntry;

typedef struct Work {
    u8 pad18[0x18];
    u8 resource;
    u8 pad19[0x68 - 0x19];
    WorkEntry entries[2];
    u8 padC0[4];
    Owner* owner;
} Work;

extern void *fn_8006ED3C();
extern void fn_8006EB60(void);
extern void fn_8006BEE4(void*, void (*)(void));
extern void fn_8006DEF8(Work*, int, void (*)(void), Work*, int);
extern void fn_80087BA8(void);
extern void fn_80087D64(void);
extern void fn_80087EC4(void);
extern void fn_80088298(void);
extern char* fn_800FD40C(void*, void*);
extern int lbl_8064C8C4;
extern u8 lbl_8064C91C;
extern u8 lbl_8064C91D;
extern u8 lbl_80245090[];

void fn_80087A24(Work* work)
{
    int index;
    void* callback;

    callback = fn_8006ED3C(work, 6, &index);
    ((u16*)callback)[4] = 0;
    ((int*)work->owner->data)[0x1780 / 4] = 0;
    fn_8006BEE4(callback, fn_8006EB60);

    work->owner->state = 0;
    work->owner->value160 = 0;
    work->entries[index].enabled_a = 1;
    work->entries[index].enabled_b = 1;
    work->entries[index].mode = 4;
    fn_8006DEF8(work, 6, fn_80087BA8, work, 1);

    work->entries[index].mode = 0;
    fn_8006DEF8(work, 6, fn_80087D64, work, 1);

    work->entries[index].mode = 1;
    fn_8006DEF8(work, 6, fn_80087EC4, work, 1);

    work->entries[index].mode = 2;
    fn_8006DEF8(work, 6, fn_80088298, work, 1);

    work->entries[index].mode = 0;
    lbl_8064C8C4 = 0;
    lbl_8064C91D = 3;
    fn_800FD40C(&work->resource, lbl_80245090);
    lbl_8064C91C = 1;
}
