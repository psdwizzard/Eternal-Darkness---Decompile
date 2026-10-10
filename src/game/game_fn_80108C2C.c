typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Frame {
    int data;
    u32 time;
    u8 state;
} Frame;

typedef struct Decoder {
    u8 pad0[0xA0];
    u8 ctx[0x138 - 0xA0];
    Frame* frames[6];
    u8 pad150[0x164 - 0x150];
    void* input;
    u8 pad168[0x170 - 0x168];
    u32 base;
    u32 current;
    u8 pad178[0x1AC - 0x178];
    u8 mode;
} Decoder;

extern void fn_80106F98(void*, void*, int);
extern void fn_801078C0(void*, void*, int, int);
extern void fn_801078E4(void*, void*, int, int, int);

int fn_80108C2C(Decoder* dec, int type, u32 time)
{
    int bias;
    u8 i;
    Frame* tmp;
    u32 cur;
    int found = 0;

    cur = dec->current;
    bias = cur != 0;

    switch (type) {
    case 0x10:
    case 0x20:
        for (i = 2; i < 6; i++) {
            if (dec->frames[i]->state != 1 || cur > dec->frames[i]->time) {
                found = 1;
                tmp = dec->frames[i];
                dec->frames[i] = dec->frames[0];
                dec->frames[0] = dec->frames[1];
                dec->frames[1] = tmp;
                break;
            }
        }
        if (!found) {
            return 2;
        }
        dec->frames[1]->state = 0;
        if (cur + bias > time + dec->base) {
            return 3;
        }
        if ((u32)type == 0x10) {
            fn_80106F98(dec->ctx, dec->input, dec->frames[1]->data);
        } else {
            if (dec->frames[0]->state == 0) {
                return 3;
            }
            fn_801078C0(dec->ctx, dec->input, dec->frames[1]->data, dec->frames[0]->data);
        }
        dec->frames[1]->time = time + dec->base;
        if (dec->mode == 4) {
            return 0;
        }
        dec->frames[1]->state = 1;
        break;
    case 0x30:
        if (dec->frames[0]->state == 0 || dec->frames[1]->state == 0) {
            return 3;
        }
        if (cur + bias > time + dec->base) {
            return 3;
        }
        for (i = 2; i < 6; i++) {
            if (dec->frames[i]->state != 1 || cur > dec->frames[i]->time) {
                dec->frames[i]->state = 0;
                fn_801078E4(dec->ctx, dec->input, dec->frames[i]->data,
                            dec->frames[0]->data, dec->frames[1]->data);
                dec->frames[i]->time = time + dec->base;
                if (dec->mode == 4) {
                    return 0;
                }
                dec->frames[i]->state = 1;
                return 0;
            }
        }
        return 2;
    default:
        return 1;
    }
    return 0;
}
