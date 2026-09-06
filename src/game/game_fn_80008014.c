typedef unsigned char u8;
typedef int s32;
typedef unsigned int u32;

#pragma use_lmw_stmw on

/* Each cinematic slot is 760 bytes; only the leading handle is written here. */
typedef struct Slot {
    void* handle;
    u8 pad04[0x2F4];
} Slot;

extern void* lbl_8064C524;
extern void* lbl_8064C528;
extern void* lbl_8064C534;
extern Slot* lbl_8064CFF8;

char lbl_8023BEBC[] = "chars/cin%04d/cin%04d.bin";

extern u8 fn_80054BC4(s32);
extern void fn_80138894(void);
extern s32 fn_800F9D4C(char*, const char*, ...);
extern s32 fn_8021302C(const char*);
extern void* fn_80138B90(const char*, s32, s32);
extern void fn_801E85A8(void*);
extern void* fn_801E86A0(void*, u32);
extern u32 fn_801E88E4(void*);
extern void* fn_80125788(void*);
extern void fn_8012B954(void*);
extern void fn_8014B928(s32);

void fn_80008014(s32 arg0, s32 arg1)
{
    char path[32];
    Slot* slots;
    u32 offset;
    u8 index;
    void* savedGroup;
    void* savedArchive;
    s32 i;
    void* entry;
    void* inst;

    index = fn_80054BC4(arg0) + 1;
    lbl_8064C534 = 0;
    fn_80138894();

    fn_800F9D4C(path, lbl_8023BEBC, (u8)arg1, (u8)arg1);
    if (fn_8021302C(path) == -1) {
        return;
    }

    savedArchive = lbl_8064C524;
    savedGroup = lbl_8064C528;

    lbl_8064C524 = fn_80138B90(path, 1, 1);
    fn_801E85A8(lbl_8064C524);
    lbl_8064C528 = fn_801E86A0(lbl_8064C524, 0);
    lbl_8064C534 = fn_801E86A0(lbl_8064C524, index);
    if (lbl_8064C534 != 0) {
        fn_801E85A8(lbl_8064C534);
    }

    if (lbl_8064C528 != 0) {
        fn_801E85A8(lbl_8064C528);
        for (i = 0, offset = 0; i < fn_801E88E4(lbl_8064C528);
                offset += sizeof(Slot), i++) {
            slots = (Slot*)((u8*)lbl_8064CFF8 + offset);
            entry = fn_801E86A0(lbl_8064C528, i);
            if (entry != 0) {
                inst = fn_80125788(entry);
                if (inst != 0) {
                    fn_8012B954(inst);
                    slots->handle = inst;
                }
            }
        }
    }

    lbl_8064C524 = savedArchive;
    lbl_8064C528 = savedGroup;
}

void fn_80008134(s32 arg0)
{
    fn_8014B928(arg0);
}
