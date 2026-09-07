typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Actor {
    u8 pad0[4];
    void* field4;
    u8 pad8[0x30];
    u32 position[3];
} Actor;

typedef struct Effect {
    u8 byte0;
    u8 byte1;
    u8 pad2[2];
    u16 half4;
    u16 half6;
    u8 pad8[0xC];
    u8 byte14;
    u8 pad15;
    u8 byte16;
    u8 byte17;
    u8 byte18;
    u8 pad19;
    u8 byte1A;
    u8 byte1B;
    u8 pad1C[8];
    u32 field24;
    u16 half28;
    u8 pad2A[2];
    void* field2C;
    u8 pad30[4];
    u32 position[3];
    u8 pad40[0x68];
    void* fieldA8;
    u8 padAC[0x10];
    u8 byteBC;
    u8 padBD[3];
    void* fieldC0;
} Effect;

extern void* fn_80149E04(Actor*);
extern void fn_80147E88(Effect*);
extern void fn_80149590(Effect*, void*);
extern void fn_80149B0C(void*, u32, u32);
extern void fn_80191360(Effect*);
extern u8 fn_801CEB2C(void*);
extern u16 fn_801D3A34(void*, u32);
extern void fn_801E8328(u32, Effect*);

void fn_801E2CF4(Actor* actor, Effect* effect, void* fieldA8, u32 arg4,
                 u32 arg5, u32 arg6, u8 child_byte, u32 arg8,
                 u8 byte17, u8 byte1B, u8 byte1, u16 half6)
{
    effect->fieldC0 = fn_80149E04(actor);
    if (effect->fieldC0 != 0) {
        fn_80147E88(effect);
        fn_80149590(effect, effect->fieldC0);
        effect->byteBC = 4;
        effect->fieldA8 = fieldA8;
        *(u8*)effect->fieldC0 = child_byte;
        fn_80149B0C(effect->fieldC0, arg4, arg5);
        fn_80191360(effect);
        effect->byte0 = fn_801CEB2C(actor->field4);
        effect->half4 = fn_801D3A34(actor->field4, arg6);
        effect->byte1 = byte1;
        effect->half6 = half6;
        effect->byte14 = 1;
        effect->byte16 = arg8;
        effect->byte17 = byte17;
        effect->byte18 = 8;
        effect->byte1A = 15;
        effect->field24 = 0;
        effect->position[0] = actor->position[0];
        effect->position[1] = actor->position[1];
        effect->position[2] = actor->position[2];
        effect->byte1B = byte1B;
        effect->half28 = 250;
        effect->field2C = fieldA8;
        fn_801E8328(0x11, effect);
    }
}
