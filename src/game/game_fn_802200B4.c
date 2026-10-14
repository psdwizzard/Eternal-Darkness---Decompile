typedef signed int s32;
typedef unsigned int u32;

extern s32 fn_8021FB24(s32 chan, u32 *xferBytes,
                     void (*callback)(s32, s32));

/* CARDCheckAsync */
s32 fn_802200B4(s32 chan, void (*callback)(s32, s32))
{
    u32 size;

    return fn_8021FB24(chan, &size, callback);
}
