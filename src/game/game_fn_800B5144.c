typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef union SaveID {
    u64 value;
    struct {
        u32 high;
        u32 low;
    } words;
} SaveID;

typedef struct SaveConfig {
    u32 values[7];
} SaveConfig;

typedef struct SaveData {
    u32 header;
    SaveConfig config;
    u8 rest[0x1B8 - 0x20];
} SaveData;

typedef struct SaveRequest {
    u8 pad00[8];
    int status;
    u8 slot;
} SaveRequest;

extern void fn_800B25AC(void);
extern int fn_8017B7B8(void);
extern void *fn_8017BA24(void);
extern void *fn_8017BA44(void);
extern int fn_800B1244(u8 *);
extern int fn_800B6A24(void);
extern u64 fn_8017B440(int);
extern void fn_8017B294(int);
extern void fn_8017BBD0(int, int, int, int, int);
extern void fn_800451C4(u8);
extern void fn_801F348C(u32 *, u32);
extern void fn_800B9454(int, int);
extern void fn_801AD404(u8, u8, int);
extern void fn_800B2548(int, int);
extern void fn_800B64AC(int, int);

extern SaveData lbl_80320738;
extern SaveConfig lbl_80302400;
extern SaveID lbl_8064CA50;
extern u32 lbl_8064CA54;
extern SaveID lbl_8064CA58;
extern int lbl_8064CA60;
extern const u32 lbl_8064F028;

void fn_800B5144(SaveRequest *request)
{
    u8 *data;
    u8 *entry;
    u64 id;
    u32 timer;
    int status;

    fn_800B25AC();
    status = request->status;
    if (status == 0) {
        if (fn_8017B7B8() != 0) {
            data = fn_8017BA24();
            fn_8017BA44();
            if (fn_800B1244(data) != 0) {
                entry = (u8 *)&lbl_80320738 + ((u8 *)&lbl_80320738)[fn_800B6A24() + 0x1B0] * 0x38 + 0x28;
                id = fn_8017B440(request->slot);
                lbl_8064CA54 = id;
                lbl_8064CA50.words.high = id >> 32;
                fn_8017B294(request->slot);
                fn_8017BBD0(2, request->slot, 0, 0, 0);
                lbl_80302400 = lbl_80320738.config;
                lbl_8064CA58.value = lbl_8064CA50.value;
                fn_800451C4(entry[0x12]);
                timer = lbl_8064F028;
                fn_801F348C(&timer, 0x3C);
                fn_800B9454(2, 0x3E);
                fn_801AD404(0, 0, 0x3C);
            } else {
                fn_800B2548(0x1A, request->slot);
            }
        } else {
            fn_800B2548(0x1B, request->slot);
        }
    } else {
        fn_800B64AC(request->slot, status);
    }
    lbl_8064CA60 = 0x14;
}
