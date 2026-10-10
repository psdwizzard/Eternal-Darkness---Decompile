typedef unsigned char u8;
typedef signed char s8;
typedef short s16;
typedef unsigned long long u64;

typedef struct EventRequest {
    u8 pad_00[8];
    int status;
    u8 value;
} EventRequest;

typedef struct SaveEntry {
    int state;
    int location[3];
    s16 room;
    u8 chapter;
    u8 pad_13[5];
    u64 playTime;
    u64 saveTime;
    int saveCount;
    int version;
    u8 pad_30[8];
} SaveEntry;

typedef struct SaveSlot {
    u8 pad_00[4];
    u8 header[0x10];
    u8 flags;
    u8 pad_15[7];
    int unlocks;
    int index;
    u8 pad_24[4];
    SaveEntry entries[7];
    u8 slots[8];
} SaveSlot;

typedef struct GameState {
    int location0;
    int location1;
    int pad_08;
    int location2;
    u8 pad_10[0x191A - 0x10];
    u8 saveCount;
    u8 pad_191B;
    int unlocks;
} GameState;

extern SaveSlot lbl_80320738;
extern SaveSlot lbl_80320978;
extern GameState lbl_803003C8;
extern char lbl_80247434[];
extern s8 lbl_8064CA30;
extern s8 lbl_8064CA31;
extern int lbl_8064CA60;
extern int lbl_8064CA64;
extern int lbl_8064D18C;

extern void fn_800B25AC(void);
extern void fn_800B261C(int);
extern void fn_800B2624(int, int, void *, int, void (*)(EventRequest *));
extern int fn_800B6A24(void);
extern void fn_800B6548(int, int);
extern void fn_800B933C(void);
extern u8 fn_800BBF2C(SaveSlot *);
extern void fn_800BBF6C(int, SaveSlot *);
extern u8 fn_800451D4(void);
extern void fn_80045220(u8);
extern u8 fn_80045230(void);
extern void fn_800AFBA8(void *);
extern u64 fn_801E8E2C(void);
extern u64 OSGetTime(void);
extern void fn_8017B864(int);
extern void fn_8017B914(int);
extern void fn_800B5738(EventRequest *);

void fn_800B5438(EventRequest *request)
{
    int index;
    u8 slot;
    u8 flags;
    int unlocks;

    fn_800B25AC();
    if (request->status == 0) {
        index = fn_800B6A24();
        slot = fn_800BBF2C(&lbl_80320738);
        lbl_80320978 = lbl_80320738;
        flags = lbl_80320978.flags;
        unlocks = lbl_80320978.unlocks;
        lbl_80320978.entries[lbl_80320978.slots[index]].state = 2;
        lbl_80320978.slots[index] = slot;
        lbl_80320978.index = index;
        lbl_80320978.entries[slot].state = 1;
        lbl_80320978.entries[slot].location[0] = lbl_803003C8.location0;
        lbl_80320978.entries[slot].location[1] = lbl_803003C8.location1;
        lbl_80320978.entries[slot].location[2] = lbl_803003C8.location2;
        lbl_80320978.entries[slot].room = lbl_8064D18C;
        lbl_80320978.entries[slot].chapter = fn_800451D4();
        lbl_80320978.entries[slot].playTime = fn_801E8E2C();
        lbl_80320978.entries[slot].saveTime = OSGetTime();
        if (lbl_803003C8.saveCount + 1 <= 100) {
            lbl_803003C8.saveCount++;
        }
        lbl_80320978.entries[slot].saveCount = lbl_803003C8.saveCount;
        lbl_80320978.entries[slot].version = 0x6C;
        fn_800AFBA8(lbl_80320978.header);
        lbl_80320978.flags = flags | fn_80045230();
        lbl_80320978.unlocks = lbl_803003C8.unlocks | unlocks;
        fn_80045220(lbl_80320978.flags);
        lbl_803003C8.unlocks = lbl_80320978.unlocks;
        fn_800BBF6C(request->value, &lbl_80320978);
        fn_8017B864(0x2000);
        fn_8017B914(0);
        fn_800B261C(0);
        lbl_8064CA31++;
        lbl_8064CA64 = 1;
        lbl_8064CA60 = 0;
        fn_800B2624(6, request->value, lbl_80247434, 0, fn_800B5738);
        return;
    }
    fn_800B6548(request->value, request->status);
    if (lbl_8064CA31 != 0) {
        fn_800B933C();
        lbl_8064CA31 = 0;
        lbl_8064CA30 = 1;
    }
    lbl_8064CA60 = 0x14;
}
