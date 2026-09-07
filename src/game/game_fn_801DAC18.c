typedef unsigned char u8;
typedef unsigned int u32;

extern u32 fn_80201814(void*);
extern u8* fn_80201B8C(void);

int fn_801DAC18(void* object, int flag)
{
    int result = 0;

    if (fn_80201814(object) != 0) {
        u8* manager = fn_80201B8C();
        if (fn_80201814(*(void**)(*(u8**)(manager + 0x8C) + 0x24)) != 0) {
            u8* state = *(u8**)(*(u8**)(fn_80201B8C() + 0x24) + 0xBC);
            u32 value = state[0];
            if (flag != 0)
                state[0] = value | 4;
            else
                state[0] = value | 2;
            result = 1;
        }
    }

    return result;
}
