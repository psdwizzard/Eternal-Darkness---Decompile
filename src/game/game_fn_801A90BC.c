typedef signed long s32;

extern void fn_801ECF50(s32);
extern void GXSetArray(s32, void*, s32);

void fn_801A90BC(void* image, void* mask)
{
    fn_801ECF50(5);
    GXSetArray(9, mask, 6);
    GXSetArray(13, image, 4);
}
