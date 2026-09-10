typedef unsigned int u32;

typedef struct Actor {
    unsigned char pad_000[0x86];
    unsigned short kind;
    unsigned char pad_088[0x1c4];
    void *slots[4];
    unsigned char pad_25c[4];
    unsigned short field_260;
    unsigned char pad_262[0x10];
    unsigned short field_272;
    unsigned char pad_274[0x10];
    unsigned short field_284;
} Actor;

extern float lbl_8064F3D8;
extern int fn_80201B54();
extern unsigned long long fn_8020123C();
extern void fn_8020104C(int, void*, void*, int, float);

void fn_800D6638(Actor *actor, void *object, int action)
{
    switch (action) {
    case 1: {
        u32 i;
        int object_id = fn_80201B54(object);

        for (i = 0; i < 4; i++) {
            int slot = (int)actor->slots[i];
            if (slot != 0) {
                fn_8020123C(8, object_id, slot, 0);
                fn_8020104C(0x43, (void*)object_id, (void*)slot, 0, lbl_8064F3D8);
            }
        }
        break;
    }
    }
    switch (actor->kind) {
    case 0:
        actor->field_272 = 0x22;
        actor->field_260 = 0x23d;
        break;
    case 1:
        actor->field_272 = 3;
        actor->field_260 = 0x168;
        break;
    case 2:
        actor->field_284 = 0xd2;
        actor->field_260 = 0x14a;
        break;
    case 3:
        break;
    }
}
