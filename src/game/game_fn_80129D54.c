typedef unsigned char u8;
typedef struct Item { int packed; int kind; int value; } Item;

extern void fn_801287C4(void*, void*, unsigned short, int);
extern int fn_801A9FA4(void*, unsigned int);

void fn_80129D54(void* owner, int count, Item* item)
{
    Item* current = item;
    int i;
    for (i = 0; i < count; current++, i++) {
        switch (current->kind) {
        case 1:
            break;
        case 0:
            fn_801287C4(owner, fn_801A9FA4, (unsigned short)current->value,
                        current->packed >> 17);
            break;
        default:
            break;
        }
    }
}
