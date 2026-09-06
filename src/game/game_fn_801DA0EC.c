typedef unsigned int u32;

extern void* fn_80201814(u32);
extern void* fn_80201B8C(void*);

u32 fn_801DA0EC(u32 value)
{
    u32 result = 0;
    void* node = fn_80201814(value);
    if (node != 0) {
        void* object = fn_80201B8C(node);
        if (object != 0) {
            void* nested = *(void**)((char*)object + 0x8C);
            if (nested != 0)
                result = *(u32*)((char*)nested + 0x24);
        }
    }
    return result;
}
