typedef unsigned short u16;
typedef signed int s32;
typedef void (*CardCallback)(s32 channel, s32 result);

extern u16 OSGetFontEncode(void);
extern s32 __CARDFormatRegionAsync(s32 channel, u16 format, CardCallback callback);
extern void __CARDSyncCallback(s32 channel, s32 result);
extern signed long __CARDSync(signed long channel);

/* Format a memory card and wait for completion. */
s32 CARDFormat(s32 channel)
{
    s32 result = __CARDFormatRegionAsync(channel, OSGetFontEncode(), __CARDSyncCallback);

    if (result < 0) {
        return result;
    }
    return __CARDSync(channel);
}
