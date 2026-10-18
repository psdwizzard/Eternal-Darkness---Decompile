typedef unsigned short u16;

extern u16 fn_80050728(void);
extern int sndFXStartEx(int, void *, int, int);

int fn_801A98F4(int index, void *object)
{
    int result = -1;

    if ((u16)index < fn_80050728()) {
        result = sndFXStartEx(index, object, 0x3F, 0);
    }

    return result;
}
