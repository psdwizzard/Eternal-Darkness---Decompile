extern void* fn_801A717C(void);
extern void fn_801A7470(void*, int);
extern void fn_8020123C(int, int, int, void*);
extern void fn_801A7228(void*);

void fn_801DE7A0(int value)
{
    void* object = fn_801A717C();
    fn_801A7470(object, 0x8a);
    fn_8020123C(0x35, value, value, object);
    fn_801A7228(object);
}
