typedef unsigned char u8;
typedef signed short s16;

#pragma use_lmw_stmw on

typedef struct Entry {
    u8 pad[0x28];
    u8 active;
    u8 flags;
    s16 value;
    u8 pad2;
    u8 type;
} Entry;

extern Entry* lbl_8063EA00[12];
extern int lbl_8064D18C;

extern int fn_8015E4E8(void);
extern void* fn_80201B3C(void);
extern void* fn_80201BC8(void);
extern int fn_8011FB4C(void);

int fn_801FD258(void)
{
    Entry* entry;
    int i;
    int count = 0;

    for (i = 0; i < 12; i++) {
        entry = lbl_8063EA00[i];
        if (entry->active && entry->value == lbl_8064D18C &&
            (!fn_8015E4E8() || entry->type == 7)) {
            int valid = 1;
            if (fn_80201B3C() && (entry->flags & 8)) {
                fn_80201BC8();
                if (entry->value != fn_8011FB4C()) {
                    valid = 0;
                }
            }
            if (valid) {
                count++;
            }
        }
    }
    return count;
}
