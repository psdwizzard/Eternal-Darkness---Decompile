extern void *fn_80156938();
extern int fn_801800F8(void*);
extern void fn_80188268(void*);

#pragma use_lmw_stmw on

typedef struct InstanceList {
    unsigned char count;
    unsigned char pad1[3];
    unsigned short mask;
    unsigned char pad6[0x82];
    void* instances[1];
} InstanceList;

#pragma opt_propagation off
#pragma opt_common_subs off
void fn_80148730(void* object)
{
    unsigned char* current;
    int count;
    unsigned short current_bit;
    int bit;
    int i;
    InstanceList* list;

    list = fn_80156938(object);
    count = list->count;
    bit = 1;
    i = 0;
    current = (unsigned char*)list;

    for (; i < count; current += 4, i++) {
        current_bit = bit;
        if ((list->mask & current_bit) != 0) {
            if (fn_801800F8(*(void**)(current + 0x88)))
                fn_80188268(*(void**)(current + 0x88));
        }
        bit = (current_bit & 0x7FFF) << 1;
    }
}
#pragma opt_propagation reset
#pragma opt_common_subs reset
