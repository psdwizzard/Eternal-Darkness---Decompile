typedef signed char s8;
typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Event800A78E0 {
    int kind;
    u32 field4;
    int timer;
    u8 padC[0x36];
    s8 index;
} Event800A78E0;

extern u32 lbl_8023975C[3];
extern int lbl_8064B81C;
extern int fn_800CA6DC(void*, int, u32, void*, int);
extern int fn_800CD84C(void*);
extern u32 fn_800A7860(void*);

int fn_800A78E0(void* context, Event800A78E0* event, void* extra)
{
    u32 values[3];
    u32 mapped;

    values[0] = lbl_8023975C[0];
    values[1] = lbl_8023975C[1];
    values[2] = lbl_8023975C[2];
    mapped = values[event->index - 1];

    if (lbl_8064B81C == 0) {
        event->kind = 0;
        event->timer = event->timer >= 200 ? event->timer : 200;
    }

    switch (event->kind) {
    case 0x500:
        return fn_800CA6DC(context, 0x500, mapped, 0, 0);
    case 0x1010:
        return fn_800CA6DC(context, 0x1010, mapped, extra, 0);
    case 0x410:
        if (fn_800CD84C(context) < 3) {
            return fn_800CA6DC(context, 0x410, mapped, 0, 0);
        }
        return 0;
    case 0x300:
        return fn_800CA6DC(context, 0x300, mapped, extra, 0);
    case 0x810:
        return fn_800CA6DC(context, 0x810, fn_800A7860(extra), extra, 0);
    default:
        return 0;
    }
}
