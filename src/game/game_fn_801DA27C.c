typedef unsigned int u32;

extern void* fn_80201814(u32);
extern void* fn_80201B8C(void*);

int fn_801DA27C(u32 value)
{
    int result = -1;
    void* node = fn_80201814(value);
    if (node != 0) {
        void* object = fn_80201B8C(node);
        result = *(int*)((char*)*(void**)((char*)object + 0x8C) + 0x24);
    }
    return result;
}
