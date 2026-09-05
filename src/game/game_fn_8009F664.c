typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;

typedef struct Entry8009F664 {
    u8 field_00;
    u8 pad01;
    u8 field_02;
    u8 field_03;
    u8 pad04[0x28];
} Entry8009F664;

typedef struct State8009F664 {
    u8 pad00[0x68];
    Entry8009F664 entries[1];
    u8 pad94[0x30];
    u8* owner;
} State8009F664;

typedef struct Context8009F664 {
    u8 pad00[8];
    s16 counter;
} Context8009F664;

extern void *fn_8006ED3C();

int fn_8009F664(register State8009F664* state)
{
    int index;
    int result = 0;
    Context8009F664* context;
    u8* owner;

    context = fn_8006ED3C(state, 10, &index);
    owner = state->owner;
    if (context->counter == 0) {
        context->counter++;
    }
    if (*(u32*)(owner + 0x20) & 0x2000) {
        state->entries[index].field_02 = 1;
        result = 1;
        state->entries[index].field_03 = 1;
        *(u32*)(owner + 0x20) &= ~0x2000u;
    }
    return result;
}
