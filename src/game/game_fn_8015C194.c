typedef unsigned char u8;
typedef signed short s16;
typedef struct Shared { int primary; int secondary; s16 requested; u8 pad[2]; u8* slots[2]; } Shared;
typedef struct Item { u8 pad[0x28]; int id; } Item;
extern volatile Shared lbl_805B6FE0;
extern Item* fn_8015C050(void*);
extern void fn_8015C020(int);

void fn_8015C194(void* object)
{
    Item* item = fn_8015C050(object);
    int secondary = lbl_805B6FE0.secondary;
    if (item != 0 && secondary != -1 &&
        item->id != *(s16*)(lbl_805B6FE0.slots[secondary] + 0x8140) &&
        (*(signed char*)(lbl_805B6FE0.slots[lbl_805B6FE0.secondary] + 0x8142) == 1 ||
         *(s16*)(lbl_805B6FE0.slots[lbl_805B6FE0.secondary] + 0x8140) == -1)) {
        *(s16*)(lbl_805B6FE0.slots[lbl_805B6FE0.secondary] + 0x8140) = item->id;
        *(u8*)(lbl_805B6FE0.slots[lbl_805B6FE0.secondary] + 0x8142) = 0;
        *(u8*)(lbl_805B6FE0.slots[lbl_805B6FE0.secondary] + 0x8143) = 0;
        fn_8015C020(0);
    }
}
