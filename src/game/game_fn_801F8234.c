extern void fn_801F8264(void*);

void fn_801F8234(void* state)
{
    void* linked;

    *(int*)((unsigned char*)state + 0x80) = 0;
    *(int*)((unsigned char*)state + 0x20) = 1;
    linked = *(void**)((unsigned char*)state + 0x74);
    *(int*)((unsigned char*)linked + 0x20) = 1;
    *(void (**)(void*))((unsigned char*)state + 0x6C) = fn_801F8264;
    linked = *(void**)((unsigned char*)state + 0x74);
    *(void (**)(void*))((unsigned char*)linked + 0x6C) = fn_801F8264;
}
