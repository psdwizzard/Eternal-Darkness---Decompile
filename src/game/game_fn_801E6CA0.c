typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct TextDescriptor {
    float scale;
    u32 color;
    s16 x;
    s16 y;
    u32 reserved;
    u32 flags;
    s16 width;
    u16 phase;
    s8 align;
    u8 font;
    s8 text[1510];
} TextDescriptor;

extern TextDescriptor lbl_80633440[];
extern char lbl_80264994[];

extern void* memset(void*, int, unsigned long);
extern void* memcpy(void*, const void*, unsigned long);
extern void fn_8015CBB0(void*, u32, void*);
extern void fn_801E5920(char*);
extern void fn_801E6A8C(TextDescriptor*);
extern void fn_801E7DCC(const char*, ...);
extern void* fn_801E880C(void*, u32, u32);
extern u32 fn_801E8878(void*, u32, u32);

TextDescriptor* fn_801E6CA0(void* resource, u32 group, u32 index, u32 flags,
                             int compressed)
{
    TextDescriptor* text_ptr;
    void* source;
    int slot;

    text_ptr = lbl_80633440;
    slot = 0;
    while (slot < 10 && (text_ptr->text[0] != 0 || text_ptr->text[1] != 0)) {
        slot++;
        if (slot < 10) {
            text_ptr++;
        }
    }
    if (text_ptr->text[0] != 0 || text_ptr->text[1] != 0) {
        fn_801E7DCC(lbl_80264994);
    }
    memset(text_ptr, 0, sizeof(*text_ptr));
    source = fn_801E880C(resource, group, index);
    if (compressed) {
        fn_8015CBB0((u8*)source + 4,
                    fn_801E8878(resource, group, index) - 4, text_ptr);
        text_ptr->flags = *(u32*)source;
        *(u32*)source |= 0x4000;
    } else {
        memcpy(text_ptr, source, fn_801E8878(resource, group, index));
        ((TextDescriptor*)source)->flags |= 0x4000;
    }
    text_ptr->flags |= flags;
    text_ptr->phase = 0;
    if (text_ptr->flags & 0x40) {
        ((u8*)text_ptr)[7] = 0;
    }
    fn_801E5920((char*)text_ptr->text);
    fn_801E6A8C(text_ptr);
    return text_ptr;
}
