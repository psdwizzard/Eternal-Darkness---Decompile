typedef signed int s32;
typedef unsigned int u32;

extern s32 CARDCheckExAsync(s32 chan, u32 *xferBytes,
                     void (*callback)(s32, s32));

/* CARDCheckAsync */
s32 CARDCheckAsync(s32 chan, void (*callback)(s32, s32))
{
    u32 size;

    return CARDCheckExAsync(chan, &size, callback);
}
