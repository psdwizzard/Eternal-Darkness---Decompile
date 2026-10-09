typedef signed int s32;

extern void *fn_80158598(s32 object_id, s32 index);
extern s32 fn_80157E1C(void *entry);
extern s32 fn_80157E24(void *entry, s32 index);
extern void *fn_80201814(s32 object_id);
extern void *fn_80201BC8(void *object);
extern void fn_8012C478(void *state, s32 index, s32 enabled);

void fn_80046E98(s32 object_id)
{
    s32 i;
    s32 count;
    void *entry;

    entry = fn_80158598(object_id, 0);

    if (entry != 0) {
        count = fn_80157E1C(entry);
        for (i = 0; i < count; i++) {
            void *object = fn_80201814(fn_80157E24(entry, i));

            if (object != 0) {
                void *state = fn_80201BC8(object);
                if (state != 0) {
                    fn_8012C478(state, 15, 0);
                }
            }
        }
    }
}
