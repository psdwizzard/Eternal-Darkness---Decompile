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
    u16 flags;
} Animation;

extern u16 lbl_8064D788;
extern Entry* lbl_8064D790;
extern u32 fn_801E741C(void*);

#pragma use_lmw_stmw on

int fn_801F6228(u32 key, u16 clear, u16 set)
{
    u32 clear_mask;
    int matches = 0;
    u16 i;
    Entry* current;

    if (lbl_8064D790 != 0) {
        clear_mask = ~(u16)clear;
        current = lbl_8064D790;
        i = 0;

        while (i < lbl_8064D788) {
            if (current->type == 1) {
                Animation* animation = current->animation;
                if (fn_801E741C((char*)animation + 2) == key) {
                    animation->flags &= clear_mask;
                    matches++;
                    animation->flags |= set;
                }
            }
            i++;
            current++;
        }
    }
    return matches;
}
