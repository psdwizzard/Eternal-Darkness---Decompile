typedef unsigned char u8;

extern void *fn_80201B3C(void);
extern void *fn_80205288(void *object);
extern void *fn_80201C24(void);
extern u8 fn_80157AB8(void *object);

u8 fn_80205630(void)
{
    u8 result = 0;
    void *object = fn_80201B3C();

    if (object != 0 && fn_80205288(object) != 0) {
        result = fn_80157AB8(fn_80201C24());
    }

    return result;
}
