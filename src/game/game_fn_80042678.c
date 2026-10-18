typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Header {
    u32 type;
    u8 pad04[4];
    u32 data08;
    u8 pad0C[4];
    u32 data10;
    u8 pad14[4];
    u32 data18;
    u8 pad1C[4];
    u32 data20;
    u8 pad24[4];
    u32 data28;
} Header;

/* The no-prototype declaration is compatible with its void(void) definition.
 * Retail callers supply a diagnostic value that the empty callee ignores. */
extern void fn_801E7DC8();
extern void* memset(void*, int, unsigned long);
extern int fn_801391AC(void);
extern int fn_80042808(void);
extern void fn_8015E9EC(u32 value, void* destination, u32 size);
extern int sprintf(char* buffer, const char* format, ...);
extern u32 fn_800244C4(void* object, u32 first, u32 second);
extern u32 fn_801E97D4(const u8* source, Header* header);
extern char lbl_8023E9B8[];
extern u32 lbl_8064D0B8;
extern Header* lbl_8064D0BC;

void fn_80042678(u16 id, const char* prefix, Header* destination)
{
    char filename[24];

    fn_801E7DC8(7);
    lbl_8064D0BC = destination;
    memset(destination, 0, lbl_8064D0B8);
    if (fn_801391AC() != 0 && id == fn_80042808()) {
        fn_8015E9EC(0xFA63D0, lbl_8064D0BC, lbl_8064D0B8);
    } else {
        sprintf(filename, lbl_8023E9B8, prefix, id);
        fn_800244C4(filename, (u32)lbl_8064D0BC, lbl_8064D0B8);
    }
    fn_801E97D4((const u8*)lbl_8064D0BC, lbl_8064D0BC);
    fn_801E7DC8(0x100);
}
