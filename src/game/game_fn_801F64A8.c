typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Entry {
    u16 type;
    u16 field_2;
    u16 field_4;
    u16 field_6;
    void* animation;
} Entry;

typedef struct Animation {
    unsigned char pad_0[0x102];
    u16 count;
    unsigned char pad_104[8];
    u16* values;
} Animation;

extern u16 lbl_8064D788;
extern Entry* lbl_8064D790;
extern u32 fn_801E741C(void*);

#pragma use_lmw_stmw on

void fn_801F64A8(u32 key, int index, u16 value)
{
    u16 i;
    Entry* current;

    if (lbl_8064D790 != 0) {
        current = lbl_8064D790;
        i = 0;
        while (i < lbl_8064D788) {
            if (current->type == 1) {
                Animation* animation = current->animation;
                if (fn_801E741C((unsigned char*)animation + 2) == key &&
                    index < animation->count) {
                    animation->values[index] = value;
                }
            }
            i++;
            current++;
        }
    }
}
