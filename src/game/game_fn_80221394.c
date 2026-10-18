typedef unsigned short u16;
typedef signed int s32;
typedef void (*CardCallback)(s32 channel, s32 result);

extern u16 OSGetFontEncode(void);
extern s32 __CARDFormatRegionAsync(s32 channel, u16 format, CardCallback callback);

/* Start formatting a memory card using the current font encoding. */
s32 CARDFormatAsync(s32 channel, CardCallback callback)
{
    return __CARDFormatRegionAsync(channel, OSGetFontEncode(), callback);
}
