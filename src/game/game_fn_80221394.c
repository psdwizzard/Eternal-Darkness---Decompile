typedef unsigned short u16;
typedef signed int s32;
typedef void (*CardCallback)(s32 channel, s32 result);

extern u16 fn_8020C918(void);
extern s32 fn_80220D3C(s32 channel, u16 format, CardCallback callback);

/* Start formatting a memory card using the current font encoding. */
s32 fn_80221394(s32 channel, CardCallback callback)
{
    return fn_80220D3C(channel, fn_8020C918(), callback);
}
