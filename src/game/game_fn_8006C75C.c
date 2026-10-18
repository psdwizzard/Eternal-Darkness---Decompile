typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct Entry {
    void *value;
    u8 level;
    u8 pad_05[5];
    u16 state;
    u8 pad_0C[12];
    u32 flags;
    u8 pad_1C[8];
} Entry;

typedef struct Object {
    u8 pad[8];
    s32 type;
} Object;
extern Entry *lbl_8064C8D4;
extern s32 lbl_8064CBC0;
extern s32 lbl_8064B528;
extern const float lbl_8064E7F8;
extern u32 rand(void);
extern s32 fn_80070AD0(void);
extern void *fn_80201B9C(void);
extern Object *fn_80204844(Object *, s32);
extern s32 fn_80201B54(s32 *);
extern void fn_8020104C(s32, s32, s32, s32, float);

Entry *fn_8006C75C(u8 count, u8 level)
{
    u8 candidates[44];
    u8 *next = candidates;
    s32 i = 0;
    s32 candidateCount = 0;
    Entry *selected = 0;
    Entry *entry = lbl_8064C8D4;

    for (; i < count; entry++, i++) {
        if (entry->state == 3 && !(entry->flags & 8) && entry->level <= level) {
            *next++ = i;
            candidateCount++;
        }
    }
    if (candidateCount > 0) {
        s32 choice = (s32)rand() % candidateCount;
        selected = &lbl_8064C8D4[candidates[choice]];
        if (lbl_8064CBC0 != 0) {
            s32 index = fn_80070AD0();
            lbl_8064B528 = index;
            if (index > 0 && index < 44) {
                selected = &lbl_8064C8D4[index];
                if (selected->state != 3) {
                    return 0;
                }
                if (index == 15) {
                    Object *object = fn_80204844(fn_80201B9C(), 0x20);
                    fn_8020104C(0x54, 0, fn_80201B54((s32 *)object), 0, lbl_8064E7F8);
                }
            }
        }
        if (selected->state != 3) {
            selected = 0;
        }
    }
    return selected;
}
