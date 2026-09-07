typedef unsigned int u32;

extern unsigned long strlen(const char*);
extern u32 fn_801E7454(const char*, u32);

u32 fn_801E741C(const char* text)
{
    return fn_801E7454(text, strlen(text));
}
