typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3f;

typedef struct SpawnParams {
    Vec3f pos;
    float facing;
    int unk10;
    int unk14;
    int unk18;
    int unk1C;
    int unk20;
    int unk24;
    int unk28;
    int unk2C;
    int unk30;
    s16 unk34;
} SpawnParams;

/* Serialized object record (0x24 bytes). */
typedef struct ObjRecord {
    u8 type;
    u8 subtype;
    s16 pos[3];
    s16 rot[3];
    s16 pad0E;
    s16 unk10;
    u16 unk12;
    u32 flags;
    u16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    s16 pad22;
} ObjRecord;

typedef struct OwnerInfo {
    char pad0[0xEA];
    s16 unkEA;
    char padEC[0xEE - 0xEC];
    s16 unkEE;
    s16 unkF0;
    char padF2[0x14E - 0xF2];
    s16 unk14E;
    char pad150[0x152 - 0x150];
    s16 unk152;
    s16 unk154;
} OwnerInfo;

typedef struct ObjExtra {
    char pad0[0x2C];
    int unk2C;
} ObjExtra;

typedef struct ObjData {
    char pad0[0x68];
    ObjExtra *unk68;
    char pad6C[0x8C - 0x6C];
    OwnerInfo *unk8C;
    int unk90;
} ObjData;

typedef struct HalfPair {
    s16 a;
    s16 b;
} HalfPair;

typedef struct ByteFlags {
    u8 bits;
    u8 pad[3];
} ByteFlags;

/* Opaque types used by the separately compiled object interfaces. */
typedef struct Entry Entry;
typedef struct Entry80201814 Entry80201814;
typedef struct SpawnRequest SpawnRequest;
typedef struct VertexData VertexData;
typedef struct VertexAttribute VertexAttribute;
typedef struct Object Object;
typedef struct Object802015A4 Object802015A4;
typedef struct Object80201C2C Object80201C2C;
typedef struct Object80201CCC Object80201CCC;
typedef struct Object80201CE8 Object80201CE8;
typedef struct Object80201D14 Object80201D14;
typedef struct Object80201D2C Object80201D2C;
typedef struct Object80201D44 Object80201D44;
typedef struct Object80201D54 Object80201D54;
typedef struct Object80201E50 Object80201E50;
typedef struct Object80204C2C Object80204C2C;
typedef struct ListNode80204C2C ListNode80204C2C;

extern void *memcpy(void *, const void *, unsigned int);
extern void fn_80029358(void);
extern int fn_80034708(void *);
extern void *fn_80036D5C(void *);
extern void fn_80036DA4(void *, void *);
extern int fn_800389E0(void *, int, s16, int);
extern void fn_80043F44(SpawnRequest *);
extern Entry *fn_80072354(int);
extern u16 fn_800BADEC(void *, void *);
extern u16 fn_800BB1EC(void *, int, void *, void *);
extern u16 fn_800BB4C4(void *, void *);
extern u16 fn_800BB6A0(void *, void *);
extern u16 fn_800BB8AC(void *, void *);
extern u16 fn_800BBA84(void *, void *);
extern u16 fn_800BBBC4(void *, void *);
extern int fn_800CCA44(void *);
extern void fn_8011F0E8(Vec3f *, Vec3f *);
extern void *fn_8011FE34(void *);
extern void fn_8012811C(VertexData *, VertexAttribute *);
extern int fn_8012F8CC(const u8 *, Object *);
extern void fn_80179DB0(float *, s16 *);
extern int fn_801E8328(u32, u32);
extern unsigned long long fn_8020123C(int, int, int, int);
extern void fn_802015A4(Object802015A4 *);
extern Entry80201814 *fn_80201814(int);
extern int fn_80201B44(void);
extern int fn_80201B54(int *);
extern void *fn_80201B8C(u8 *);
extern void *fn_80201B94(u8 *);
extern void *fn_80201BC8(void *);
extern void *fn_80201C2C(Object80201C2C *);
extern u32 fn_80201CCC(Object80201CCC *);
extern void fn_80201CE8(Object80201CE8 *, u32, u32);
extern void fn_80201D14(Object80201D14 *, u8);
extern void fn_80201D2C(Object80201D2C *, int);
extern void fn_80201D44(Object80201D44 *, int);
extern void fn_80201D54(Object80201D54 *, void *);
extern u32 fn_80201E50(Object80201E50 *, u32);
extern ListNode80204C2C *fn_80204C2C(Object80204C2C *);

extern int lbl_8064C544;
extern int lbl_8064D18C;

int fn_800BA6D4(char *data, int arg1, u16 *outSize, int readModel, int place)
{
    ObjRecord rec;
    SpawnParams params;
    Vec3f pos;
    HalfPair halves;
    ByteFlags bits;
    HalfPair value;
    ObjExtra *extra;
    ObjData *objData;
    ObjData *info;
    void *other;
    void *obj;
    int id;
    void *model;
    OwnerInfo *owner;
    int mask;
    u16 offset;

    extra = 0;
    memcpy(&rec, data, sizeof(rec));
    offset = sizeof(rec);
    if (rec.unk12 == 0x130) {
        /* ASM: nop -- a lone breakpoint anchor; an empty C body emits no code
         * at all, so the nop (and its compare) can only come from asm. */
        asm { nop }
    }
    fn_80043F44((SpawnRequest *)&params);
    params.unk2C = rec.unk18;
    params.unk10 = rec.unk1A;
    params.unk14 = rec.unk12;
    params.unk28 = rec.type;
    fn_80179DB0(&params.pos.x, rec.pos);
    if (rec.flags & 1) {
        params.unk34 = 1;
    } else {
        params.unk34 = 0;
    }

    if (!(rec.flags & 4)) {
        params.unk1C = rec.unk1E;
        params.unk20 = rec.unk20;
        params.unk18 = arg1;
        params.unk24 = rec.unk10;
        obj = (void *)fn_80034708(&params);
        objData = fn_80201B8C(obj);
        extra = objData->unk68;
        fn_80072354(objData->unk90);
        id = fn_80201B54(obj);
        model = fn_80201BC8(obj);
        fn_801E8328(1, (u32)obj);
        fn_80029358();
        if (rec.type == 0x1D || rec.type == 0x33 || rec.type == 0x2E) {
            if (rec.type == 0x33 && (int)rec.subtype == 0xC) {
                fn_80201CE8(obj, 0, 0x400000);
            }
            if ((rec.type == 0x1D || rec.type == 0x2E) && (int)rec.subtype == 0xD) {
                fn_80201CE8(obj, 0, 0x80);
            }
            if (rec.flags & 0x400) {
                fn_80201CE8(obj, 0, 0x100000);
            }
            if (rec.flags & 0x800) {
                fn_80201CE8(obj, 0, 0x200000);
            }
        }
        if (place) {
            fn_80201D54(obj, (void *)(u32)rec.unk18);
        }
        fn_80201D44(obj, rec.type);
        fn_802015A4(obj);
        if (rec.subtype == 0x24) {
            fn_80201D2C(obj, rec.subtype);
            fn_80201D14(obj, 1);
            fn_8020123C(0x3B, id, id, 0);
        }
        if ((int)rec.type == 0x4A && (int)rec.subtype != 0x72) {
            fn_80201D2C(obj, 1);
            fn_80201D14(obj, 1);
            fn_8020123C(0x3B, id, id, 0);
        }
        fn_800CCA44(obj);
    } else {
        arg1 = fn_80201B44();
        obj = fn_80201814(arg1);
        id = arg1;
        model = fn_80201BC8(obj);
        objData = fn_80201B8C(obj);
        offset += fn_800BADEC(data + offset, obj);
        if (place) {
            lbl_8064D18C = rec.unk18;
        }
    }

    if (place) {
        fn_80179DB0(&pos.x, rec.pos);
        fn_8011F0E8(model, &pos);
        fn_8012811C((VertexData *)rec.rot, fn_8011FE34(model));
        fn_80201D54(obj, (void *)(u32)rec.unk18);
    }
    fn_800389E0(obj, 0, rec.unk1C, 0);
    if (readModel && (rec.flags & 2)) {
        offset += fn_8012F8CC((const u8 *)data + offset, model);
    }
    if (rec.flags & 0x10000) {
        fn_80201CE8(obj, 0, 0x1000000);
    }
    if (rec.flags & 8) {
        offset = offset + fn_800BB4C4(data + offset, obj);
    }
    if (rec.flags & 0x20000) {
        offset = offset + fn_800BB6A0(data + offset, obj);
    }
    if (rec.flags & 0x10) {
        offset = offset + fn_800BB8AC(data + offset, obj);
    }
    if (rec.flags & 0x20) {
        offset = offset + fn_800BBBC4(data + offset, obj);
    }
    if (rec.flags & 0x40) {
        offset = offset + fn_800BBA84(data + offset, obj);
    }
    if (rec.flags & 0x80) {
        fn_80036DA4(obj, (void *)((u32)fn_80036D5C(obj) | 0x8));
    }
    if (rec.flags & 0x80000) {
        fn_80036DA4(obj, (void *)((u32)fn_80036D5C(obj) | 0x20000));
    }
    if (rec.flags & 0x100) {
        fn_80036DA4(obj, (void *)((u32)fn_80036D5C(obj) | 0x80));
    }
    if (rec.flags & 0x200) {
        fn_80036DA4(obj, (void *)((u32)fn_80036D5C(obj) | 0x8000));
    }
    if (rec.flags & 0x400000) {
        fn_80036DA4(obj, (void *)((u32)fn_80036D5C(obj) | 0x800000));
    }
    if (rec.flags & 0x800000) {
        lbl_8064C544 = id;
    }
    if ((rec.flags & 0x100) || (rec.flags & 0x200)) {
        memcpy(&halves, data + offset, sizeof(halves));
        offset += 4;
        objData->unk8C->unk152 = halves.a;
        objData->unk8C->unk154 = halves.b;
    }
    if (extra != 0) {
        if (rec.flags & 0x1000) {
            extra->unk2C |= 0x20;
        }
        if (rec.flags & 0x2000) {
            extra->unk2C |= 0x40;
        }
        if (rec.flags & 0x4000) {
            extra->unk2C |= 0x80;
        }
        if (rec.flags & 0x8000) {
            extra->unk2C |= 0x100;
        }
        if (rec.flags & 0x100000) {
            extra->unk2C |= 0x400;
        }
        if (rec.flags & 0x200000) {
            extra->unk2C |= 0x80;
        }
    }
    if (rec.unk12 == 5 && rec.unk1A == 0xC) {
        owner = ((ObjData *)fn_80201B8C(obj))->unk8C;
        memcpy(&bits, data + offset, sizeof(bits));
        offset += 4;
        if (bits.bits != 0) {
            other = fn_80201B94(obj);
            mask = fn_80201CCC(other);
            if (bits.bits & 1) {
                mask |= 0x100;
                owner->unkF0 = 0;
            }
            if (bits.bits & 2) {
                mask |= 0x200;
                owner->unkEE = 0;
            }
            if (bits.bits & 4) {
                mask |= 0x400;
                owner->unkEA = 0;
            }
            if (bits.bits & 8) {
                mask |= 0x100000;
            }
            fn_80201E50(other, mask);
            if ((int)rec.subtype == 8) {
                fn_80201D2C(obj, rec.subtype);
                fn_80201D14(obj, 1);
            }
        }
    }
    if (rec.unk12 == 0x89 && rec.unk1A == 0x84) {
        info = fn_80201B8C(obj);
        memcpy(&value, data + offset, sizeof(value));
        offset += 4;
        info->unk8C->unk14E = value.a;
    }
    if (!(rec.flags & 0x40000)) {
        int count = rec.flags >> 24;
        void *target = fn_80201C2C(obj);
        if (target == 0) {
            target = fn_80204C2C(obj);
        }
        offset += fn_800BB1EC(data + offset, count, target, (void *)id);
    }
    *outSize = offset;
    return (int)obj;
}
