typedef unsigned int u32;
typedef unsigned char u8;

typedef struct Entry Entry;
typedef struct TextDescriptor TextDescriptor;

typedef struct MenuEntry {
    char pad0[0x12];
    short enabled;
    char pad14[0xC];
} MenuEntry;

typedef struct TaskDesc {
    char pad0[0x2C];
    TextDescriptor *text;
} TaskDesc;

extern u32 lbl_8023A414[];
extern MenuEntry lbl_8024DEF8[];
extern TaskDesc lbl_8024DE38;
extern u32 *lbl_8064C4E0;
extern void *lbl_8064C504;
extern u32 lbl_8064CD34;
extern int lbl_8064CD44;
extern u32 lbl_8064CD5C;
extern u32 lbl_8064CD60;
extern Entry *lbl_8064CDC0;

extern Entry *fn_80144628(int, int, int);
extern void fn_80144680(Entry *);
extern void fn_80144C40(void);
extern TextDescriptor *fn_801E6CA0(void *, u32, u32, u32, int);
extern void fn_801E7974(u8 *, u32);
extern int fn_801E79FC(u32 *, u32);

void fn_80111E10(short enable, u32 *result)
{
    u32 flags = lbl_8064CD5C | (lbl_8064CD60 |
                    (lbl_8023A414[lbl_8064CD34] & 0x1FF0));

    if (lbl_8064CD44 != 0x1C) {
        if (enable != 0) {
            *result = flags;
        } else {
            *result = 0;
        }
        lbl_8024DEF8[0].enabled = 0;
        lbl_8024DEF8[1].enabled = 0;
        lbl_8024DEF8[2].enabled = 0;
        lbl_8024DEF8[3].enabled = 0;
        lbl_8024DEF8[4].enabled = 0;
        if (lbl_8064CD44 == 0x1B) {
            if (fn_801E79FC(lbl_8064C4E0, 0x258) != 0) {
                lbl_8064CD44 = 0xE;
                fn_80144680(lbl_8064CDC0);
                lbl_8064CDC0 = fn_80144628(8, (int)lbl_8024DEF8, 0);
            } else {
                fn_801E7974((u8 *)lbl_8064C4E0, 0x257);
                lbl_8064CD44 = 0x1C;
                lbl_8024DE38.text = fn_801E6CA0(lbl_8064C504, 0xF, 0x1B, 0, 1);
            }
        } else {
            lbl_8064CD44 = 0xE;
        }
        fn_80144C40();
    }
}
