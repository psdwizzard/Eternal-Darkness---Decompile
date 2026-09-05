typedef unsigned char u8;
typedef unsigned short u16;

extern unsigned int fn_8012927C(void* object);
extern void fn_80127CE4(void* a, void* b, void* c, float value);
extern void fn_80127B90(void* a, void* b, void* c, float value);
extern float lbl_80650068;

#pragma use_lmw_stmw on
#pragma optimization_level 2
#pragma opt_propagation off
void fn_8011ECF8(void* object, void* source)
{
    int slot_offset;
    int record_offset;
    int position_offset;
    u8* slot;
    void* record_list;
    int count;
    int index;
    u8* record;
    count = *(u16*)(*(u8**)((u8*)object + 60) + 8);
    if ((u16)fn_8012927C(object) != 0xFFFF) {
        count++;
    }

    record_list = *(void**)(*(u8**)((u8*)source + 184) + 4);
    slot_offset = 0;
    record_offset = slot_offset;
    index = 0;
    position_offset = slot_offset;

    while (index < count) {
        slot = *(u8**)((u8*)object + 352) + slot_offset + 4;
        record = *(u8**)record_list + record_offset;
        (*(u8**)((u8*)object + 680))[index] = 0;
        if (*(u16*)record != 0 && *(void**)(slot + 20) != 0) {
            fn_80127CE4(*(void**)(slot + 20), *(void**)(slot + 24),
                        *(u8**)((u8*)object + 340) + position_offset, lbl_80650068);
            (*(u8**)((u8*)object + 680))[index] |= 2;
        }
        if (*(u16*)(record + 8) != 0) {
            fn_80127B90(*(void**)(slot + 48), *(void**)(slot + 52),
                        *(u8**)((u8*)object + 344) + record_offset, lbl_80650068);
            (*(u8**)((u8*)object + 680))[index] |= 1;
        }

        slot_offset += 76;
        record_offset += 16;
        position_offset += 12;
        index++;
    }
}
#pragma opt_propagation reset
#pragma optimization_level reset
#pragma use_lmw_stmw reset
