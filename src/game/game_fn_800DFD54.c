typedef unsigned char u8;
typedef signed char s8;

typedef struct Payload {
    u8 bytes[4];
} Payload;

typedef struct Delta {
    s8 bytes[4];
} Delta;

#pragma use_lmw_stmw on

extern int lbl_8064D18C;
extern int fn_80201B54();
extern int fn_8011FB4C(void *);
extern int fn_80200C38();
extern unsigned short fn_8012DBE8(void *, int, Payload *);
extern int fn_800DE298(void *);
extern void* fn_8012C62C(void *, int, Payload, Delta, Payload, int);

void fn_800DFD54(int enabled, void *object, void *resource, void *event)
{
    Delta second;
    Payload source;
    Payload first;
    int type;
    int flag;
    int ready;

    fn_80201B54(object);
    type = fn_8011FB4C(resource);
    flag = event != 0 ? fn_80200C38(event) : 1;
    fn_8012DBE8(resource, 15, &source);
    first.bytes[0] = source.bytes[0];
    first.bytes[1] = source.bytes[1];
    first.bytes[2] = source.bytes[2];
    second.bytes[0] = second.bytes[1] = second.bytes[2] = 0;

    if (type == lbl_8064D18C) {
        ready = fn_800DE298(object);
        if (flag != 0) {
            if (ready != 0) {
                second.bytes[3] = 5;
                first.bytes[3] = 0xFB;
                fn_8012C62C(resource, 15, source, second, first, 4);
            }
        } else if (ready != 0 && enabled != 0) {
            second.bytes[3] = -5;
            first.bytes[3] = 0;
            fn_8012C62C(resource, 15, source, second, first, 4);
        }
    }
}
