typedef signed int s32;
typedef unsigned int u32;

#pragma use_lmw_stmw on

extern void* lbl_8064C4F8;

extern void* fn_80049304(void* object, s32 index);
extern unsigned int rand(void);
#define rand() ((int)rand())
extern u32 fn_80157888(void* object);
extern s32 fn_80157C80(void* object);
extern void fn_801A7680(void* destination, void* object);
extern void* fn_80201C24();

void fn_8004948C(void* object, void* destination, s32 mode)
{
    void* first_entry;
    void* second_entry;
    void* selected;

    selected = lbl_8064C4F8;
    first_entry = fn_80049304(object, 0);
    second_entry = fn_80049304(object, 1);

    if (first_entry != 0 && second_entry != 0) {
        u32 first_state;
        void* first;
        void* second;

        first = fn_80201C24(first_entry);
        first_state = fn_80157888(first) & 2;
        second = fn_80201C24(second_entry);

        if (first_state != 0) {
            selected = first;
            if ((fn_80157C80(first) & 0xA0) != 0 &&
                (fn_80157C80(second) & 0xA0) == 0) {
                selected = second;
            }
        } else if (mode != 0) {
            selected = first;
            if ((rand() & 1) != 0) {
                selected = second;
            }
        } else {
            selected = second;
        }
    } else if (first_entry != 0) {
        selected = fn_80201C24(first_entry);
    }

    fn_801A7680(destination, selected);
}
