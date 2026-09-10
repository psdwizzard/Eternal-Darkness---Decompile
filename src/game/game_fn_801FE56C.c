typedef signed short s16;
typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Record {
    Vec3 position;
    u8 color[4];
    int value;
} Record;

typedef struct Entry {
    u8 pad00[0x18];
    int mode;
    u8 pad1C[0xC];
    u8 active;
    u8 flags;
    s16 value;
    u8 pad2C;
    u8 type;
    u8 pad2E[6];
    Record record;
    u8 pad48[0x18];
    Vec3 vector;
    u8 pad6C[0xC];
} Entry;

extern const u32 lbl_8023B830[];
extern Entry* lbl_8063EA00[];
extern void* lbl_8064C4E4;
extern int lbl_8064D18C;
extern float lbl_80651548;
extern Record lbl_8063F00C;
extern u8 lbl_802FC5BC[];

extern int fn_801EF37C(void);
extern void* fn_80201B3C(void);
extern void* fn_80201BC8(void);
extern int fn_80047178(void);
extern int fn_8012FA54(void*, int);
extern void fn_8011F114(Vec3*, void*);
extern void fn_801ECE7C(u32);
extern void fn_801FD6AC(Record*, Vec3*, u8*, u32);
extern void fn_801F0CB0(Record*, Vec3*, void*, int, int, Vec3*, void*);
extern int fn_8015E4E8(void);
extern int fn_8011FB4C(void);
extern void fn_801F10BC(u32, u32, int);

#pragma use_lmw_stmw on

void fn_801FE56C(void)
{
    u32 mask = 0;
    const u32* constants = lbl_8023B830;
    u32 feature_mask = 0;
    int slot = 0;
    int count = fn_801EF37C();
    void* player;
    int allow_hidden = 0;
    int i;
    Entry** cursor;

    if (fn_80201B3C() != 0) {
        player = fn_80201BC8();
    } else {
        player = 0;
    }

    if (fn_80047178() != 0 && fn_8012FA54(player, 15) != 0) {
        allow_hidden = 1;
    }

    if (lbl_8064C4E4 != 0) {
        Vec3 origin = *(Vec3*)&constants[0];
        Vec3 transformed;
        Vec3 position;
        fn_8011F114(&transformed, lbl_8064C4E4);
        position = transformed;
        position.z += lbl_80651548;
        fn_801ECE7C(255);
        fn_801FD6AC(&lbl_8063F00C, &position, lbl_802FC5BC, 20000);
        fn_801F0CB0(&lbl_8063F00C, &origin, 0, 7, 0, 0, 0);
        feature_mask |= 0x80;
    } else {
        Vec3 target = *(Vec3*)&constants[3];
        Vec3 position = *(Vec3*)&constants[6];
        fn_801ECE7C(255);
        fn_801FD6AC(&lbl_8063F00C, &position, lbl_802FC5BC, 20000);
        fn_801F0CB0(&lbl_8063F00C, &target, 0, 7, 0, 0, 0);
        feature_mask |= 0x80;
    }

    cursor = lbl_8063EA00;
    for (i = 0; i < count;) {
        Entry* entry = *cursor;
        Record* record = &entry->record;
        int valid;

        if (slot == 7) {
            break;
        }
        if (!entry->active) {
            goto next;
        }
        if (!allow_hidden && (entry->flags & 2)) {
            goto next;
        }
        if (entry->value != lbl_8064D18C) {
            goto next;
        }
        if (fn_8015E4E8() && entry->type != 7) {
            goto next;
        }

        valid = 1;
        if (fn_80201B3C() != 0 && (entry->flags & 8)) {
            fn_80201BC8();
            if (entry->value != fn_8011FB4C()) {
                valid = 0;
            }
        }
        if (!valid) {
            goto next;
        }

        if (entry->mode == 1) {
            fn_801F0CB0(record, 0, 0, slot, 0, &entry->vector, entry->pad48);
        } else {
            fn_801F0CB0(record, 0, 0, slot, 0, &entry->vector, 0);
        }
        mask |= 1 << slot;
        slot++;
next:
        cursor++;
        i++;
    }
    fn_801F10BC(mask, feature_mask, 1);
}
