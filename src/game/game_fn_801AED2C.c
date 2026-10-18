typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Entry Entry;
struct Entry {
    u8 state;
    u8 type;
    u8 arg2;
    u8 arg3;
    u8 padding04[4];
    Entry* first;
    Entry* second;
    u8 padding10[64];
    u32 handle;
    u8 padding54[22];
    u8 phase;
    u8 padding6B[25];
};

extern Entry lbl_8060B430[];
extern void fn_801ADC08(void);
extern void fn_801ADBC0(void);
extern u32 fn_801ADAF8(u32);
extern void fn_801AE140(Entry*, u32);
extern int fn_801AE5DC(Entry*);
extern u32 fn_801A9B94(u32, u32);
extern void sndStreamMixParameterEx(u32, u32, u32, u32, u32, u32);

void fn_801AED2C(u32 id)
{
    Entry* entry;
    u32 index;

    if (id != -1) {
        fn_801ADC08();
        index = fn_801ADAF8(id);
        if (index != -1) {
            entry = &lbl_8060B430[index];
            if (entry->first != 0) {
                entry->first->first = 0;
                entry->first->second = 0;
                fn_801AE140(entry->first, 0);
                entry->first = 0;
            }
            if (entry->second != 0) {
                entry->second->first = 0;
                entry->second->second = 0;
                fn_801AE140(entry->second, 0);
                entry->second = 0;
            }
            entry->arg2 = 64;
            entry->arg3 = 0;
            if (entry->state == 3) {
                if (entry->phase == 2 || entry->phase == 3) {
                    entry->phase = 3;
                    entry->state = 5;
                } else {
                    fn_801AE5DC(entry);
                }
            } else {
                u32 value = fn_801A9B94(entry->type, 2);
                sndStreamMixParameterEx(entry->handle, value, entry->arg2, entry->arg3, 0, 0);
            }
        }
        fn_801ADBC0();
    }
}
