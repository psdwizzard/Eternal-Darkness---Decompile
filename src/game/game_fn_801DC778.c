typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Payload {
    short position[3];
    short pad06[5];
    void* effects[3];
    void* attached;
    u8 pad20[0x9C];
} Payload;

typedef struct Object {
    u8 pad00[4];
    u32 type;
    u32 owner;
    u8 pad0C[0x38];
    void* linked;
    u8 pad48[0x74];
    Payload payload;
    u8 pad178[0xE7C];
    u16 state;
} Object;

extern int lbl_8064D18C;
extern short fn_801CEB2C(u32);
extern void fn_80190500(void*, int);
extern void fn_801FE22C(void*);
extern void fn_801A9E40(int);
extern void fn_801D0E78(Object*);
extern void fn_8017E804(Payload*, short*, int);
extern void fn_8017DC88(Payload*, short*, int);
extern void* fn_8017FDA8(void*, int);
extern void fn_801FDF74(void*, u32);

void fn_801DC778(Object* object)
{
    Payload* payload = &object->payload;
    int count = fn_801CEB2C(object->type);
    int i;

    if (object->owner != lbl_8064D18C) {
        if (object->state <= 0x99) {
            for (i = 0; i < (short)count; i++) {
                if (payload->effects[i] != 0) {
                    fn_80190500(payload->effects[i], 0);
                }
            }
        }
        if (object->linked != 0) {
            fn_801FE22C(object->linked);
        }
        fn_801A9E40(-1);
        fn_801D0E78(object);
        return;
    }

    if (object->state >= 40 && object->state <= 120) {
        fn_8017E804(payload, payload->position, 5 - ((object->state - 40) >> 4));
    } else if (object->state > 140 && object->state < 154) {
        short next[3];
        next[2] = payload->pad06[3];
        fn_8017DC88(payload, next, 2);
        payload->pad06[3] = next[2];
    }

    switch (object->state) {
    case 121:
        payload->pad06[2] -= 200;
        break;
    case 173:
        if (object->linked != 0) {
            fn_801FDF74(object->linked, 0x593E0);
        }
        break;
    case 193:
        fn_801A9E40(-1);
        fn_801D0E78(object);
        break;
    }
}
