typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Descriptor { u8 bytes[0xC0]; } Descriptor;

extern void *fn_80201814();
extern void* fn_80155DB4(void);
extern void* memset(void*, int, u32);
extern void* fn_80149E04(void);
extern void fn_80147E88(Descriptor*);
extern void fn_80154A14(Descriptor*, void*, u8);
extern void fn_801A1AF4(Descriptor*);
extern void fn_80149B0C(void*, void*, void*);
extern void* fn_80148300(void*, Descriptor*, void*);
extern void fn_80149EB8(void*);

void* fn_80154DB4(void* object, void* arg4, void* arg5, u16 value,
                  u8 kind, u8 mode, u8 flag, float scale)
{
    void* result = 0;
    void* owner;
    void* state;
    Descriptor desc;

    if (fn_80201814(object) != 0 && (owner = fn_80155DB4()) != 0) {
        memset(&desc, 0, sizeof(desc));
        state = fn_80149E04();
        if (state != 0) {
            fn_80147E88(&desc);
            fn_80154A14(&desc, state, kind);
            desc.bytes[0xBC] = mode;
            if (value != 0)
                goto initialize;
            if (kind == 0)
                goto initialize;
            if (kind == 0)
                goto initialized;
            if (value != 0)
                goto initialized;
initialize:
            {
                fn_801A1AF4(&desc);
                *(u16*)(desc.bytes + 6) = value;
                *(u32*)(desc.bytes + 0x94) = 0;
                desc.bytes[0x18] = kind;
                *(float*)(desc.bytes + 0x14) = scale;
            }
initialized:
            fn_80149B0C(state, arg4, arg5);
            desc.bytes[0xBE] = flag;
            result = fn_80148300(owner, &desc, state);
            if (result == 0)
                fn_80149EB8(state);
        }
    }
    return result;
}
