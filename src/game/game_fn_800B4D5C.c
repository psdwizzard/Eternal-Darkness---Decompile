typedef unsigned char u8;
typedef unsigned long long u64;

typedef struct SaveRect {
    int values[7];
} SaveRect;

typedef struct SaveData {
    int header;
    SaveRect rect;
    u8 rest[0x1B8 - 0x20];
} SaveData;

typedef struct SaveInfo {
    int header;
    int pad04[4];
    u8 flags;
    u8 pad15[7];
    int mask;
    u8 rest[0x1B8 - 0x20];
} SaveInfo;

typedef struct SaveCard {
    u8 pad00[8];
    int busy;
    u8 slot;
} SaveCard;

typedef struct SaveSlot {
    u8 pad00[0x20];
    int index;
    u8 rest[0x1B8 - 0x24];
} SaveSlot;

typedef struct SaveBuffer {
    u8 data[0x1B8];
} SaveBuffer;

extern void *memcpy(void *, const void *, unsigned int);
extern int fn_800B6908(void);
extern void fn_800B25AC(void);
extern int fn_800B1944(void);
extern void fn_800B1974(int);
extern void fn_800B2548(int, int);
extern void fn_800B261C(int);
extern void fn_800B2624(int, int, void *, int, void (*)(void));
extern void fn_800B5D94(int);
extern void fn_800B5F78(int, int);
extern void fn_800B63C0(int, int);
extern void fn_800B669C(int, int);
extern void fn_800B6960(int, int);
extern void fn_800B6A48(int);
extern int fn_800BBE04(void *);
extern void fn_800BBF6C(int, void *);
extern void fn_800AFBA8(void *);
extern u8 fn_80045230(void);
extern void fn_80045220(u8);
extern void fn_8017B294(int);
extern u64 fn_8017B440(int);
extern int fn_8017B7B8(void);
extern void fn_8017B864(int);
extern void fn_8017B914(int);
extern void *fn_8017BA44(void);
extern void fn_8017BBD0(int, int, int, int, int);
extern void fn_800B5828(void);

extern u8 lbl_80247434[];
extern u8 lbl_803003C8[];
extern SaveRect lbl_80302400;
extern SaveSlot lbl_80320738;
extern SaveInfo lbl_80320978;
extern int lbl_8064C670;
extern int lbl_8064C6BC[2];
extern int lbl_8064CA58;
extern int lbl_8064CA5C;
extern int lbl_8064CA60;
extern int lbl_8064CA64;
extern int lbl_8064CA6C;

void fn_800B4D5C(SaveCard *card)
{
    u64 id;
    int busy;
    int mode = fn_800B6908();

    fn_800B25AC();
    lbl_8064CA60 = 0x14;

    switch (fn_800B1944()) {
    case 0:
        busy = card->busy;
        if (busy == 0) {
            if (fn_8017B7B8() != 0) {
                SaveSlot slot;
                void *src;
                src = fn_8017BA44();
                memcpy(&slot, src, 0x1B8);
                if (fn_800BBE04(&slot) != 0) {
                    lbl_80320738 = slot;
                    mode = lbl_80320738.index;
                    fn_800B6960(mode, 1);
                    fn_800B6A48(mode);
                    fn_800B261C(0);
                    lbl_8064CA6C = 1;
                    fn_800B2548(3, card->slot);
                } else {
                    fn_800B2548(0x18, card->slot);
                }
            } else {
                fn_800B2548(0x18, card->slot);
            }
        } else {
            fn_800B63C0(card->slot, card->busy);
        }
        break;
    case 1: {
        id = 0;
        if (mode == 1) {
            id = fn_8017B440(card->slot);
            fn_8017B294(card->slot);
            fn_8017BBD0(2, card->slot, 0, 0, 0);
        }
        busy = card->busy;
        if (busy == 0) {
            if (fn_8017B7B8() != 0) {
                SaveData data;
                void *src;
                src = fn_8017BA44();
                memcpy(&data, src, 0x1B8);
                if (fn_800BBE04(&data) != 0) {
                    if (mode == 1) {
                        lbl_80302400 = data.rect;
                        lbl_8064C670 = 1;
                        lbl_8064CA5C = id;
                        lbl_8064CA58 = id >> 32;
                        fn_800B1974(1);
                    } else {
                        SaveInfo *info;
                        u8 flags;
                        int mask;
                        lbl_80320978 = *(SaveInfo *)&data;
                        info = &lbl_80320978;
                        flags = info->flags;
                        mask = info->mask;
                        fn_800AFBA8(&info->pad04);
                        info->flags = flags | fn_80045230();
                        info->mask = *(int *)(lbl_803003C8 + 0x191C) | mask;
                        fn_80045220(info->flags);
                        *(int *)(lbl_803003C8 + 0x191C) = info->mask;
                        fn_800BBF6C(card->slot, &lbl_80320978);
                        fn_8017B864(0x2000);
                        fn_8017B914(0);
                        fn_800B261C(0);
                        lbl_8064CA64 = 1;
                        lbl_8064CA60 = 0;
                        fn_800B2624(6, card->slot, lbl_80247434, 3, fn_800B5828);
                    }
                } else if (mode == 1) {
                    fn_800B5D94(card->slot);
                } else {
                    fn_800B2548(0x11, card->slot);
                }
            } else if (mode == 1) {
                fn_800B5D94(card->slot);
            } else {
                fn_800B2548(0x11, card->slot);
            }
        } else if (mode == 1) {
            fn_800B5D94(busy);
        } else {
            fn_800B5F78(card->slot, busy);
        }
        break;
    }
    case 2:
        if (card->busy == 0) {
            if (fn_8017B7B8() != 0) {
                SaveBuffer buffer;
                void *src;
                src = fn_8017BA44();
                memcpy(&buffer, src, 0x1B8);
                if (fn_800BBE04(&buffer) != 0) {
                    lbl_8064C6BC[card->slot] = 3;
                    fn_800B669C(card->slot, 1);
                } else {
                    fn_800B2548(0x18, card->slot);
                }
            } else {
                fn_800B2548(0x18, card->slot);
            }
        } else {
            fn_800B63C0(card->slot, card->busy);
        }
        break;
    }
}
