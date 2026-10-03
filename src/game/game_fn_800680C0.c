typedef signed int s32;

extern s32 lbl_8064C89C;
extern s32* fn_800681C8(void);
extern void* fn_80201814(s32 id);
extern s32 fn_80201B54(void* object);

s32 fn_800680C0(void* object, s32 excluded_id)
{
    s32* slots = fn_800681C8();
    s32 i;
    s32 count = 0;

    fn_80201B54(object);
    if (++lbl_8064C89C > 12) {
        asm { nop }
    }
    if (slots == 0) {
        asm { nop }
    }
    for (i = 0; slots != 0 && i < 12; i++) {
        if (slots[i] != 0 && slots[i] != excluded_id) {
            void* child = fn_80201814(slots[i]);
            if (child != 0) {
                count++;
                count += fn_800680C0(child, fn_80201B54(object));
            } else {
                slots[i] = 0;
            }
        }
    }
    lbl_8064C89C--;
    return count;
}
