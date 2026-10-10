typedef struct ItemRecord {
    float time;      /* 0x00 */
    short unk04;     /* 0x04 */
    int unk08;       /* 0x08 */
    int unk0C;       /* 0x0C */
    int unk10;       /* 0x10 */
    short unk14;     /* 0x14 */
    short unk16;     /* 0x16 */
    short unk18;     /* 0x18 */
    short unk1A;     /* 0x1A */
    unsigned char unk1C; /* 0x1C */
    char unk1D;      /* 0x1D */
    char unk1E;      /* 0x1E */
    char unk1F;      /* 0x1F */
    char unk20;      /* 0x20 */
    unsigned char flags; /* 0x21 */
    short unk22;     /* 0x22 */
} ItemRecord;

extern int fn_80201B54(void *);
extern void *fn_80201BC8(void *);
extern void *fn_80155DB4(void *);
extern short fn_80157A08(void *, int);
extern int fn_80157C80(void *);
extern short fn_8015821C(void *);
extern unsigned char fn_80157AB8(void *);
extern char fn_80157918(void *);
extern int fn_80200614(int, int, int);
extern float fn_80200534(int, int, int);
extern int fn_80117E58(void);
extern float fn_80200BDC(void);
extern short fn_801578E8(void *);
extern short fn_801578F4(void *);
extern short fn_80157900(void *);
extern char fn_80157BD0(void *);
extern char fn_80157BDC(void *);
extern char fn_80157BC4(void *);
extern int fn_801578AC(void *);
extern unsigned int fn_80156930(void *);
extern unsigned int fn_80156928(void *);
extern unsigned int fn_80156920(void *);
extern int fn_801579F4(void *);
extern void *fn_80158598(void *, int);
extern int fn_801586FC(int, void *);
extern int fn_80158550(void *, int);
extern void *memcpy(void *, const void *, unsigned long);
extern int fn_800B9578(void *, void *, int, int);
extern void *fn_80201814(int);
extern void *fn_80201C24(void *);

extern float lbl_8064F010;

static inline float GetTimerValue(int obj) {
    float t = lbl_8064F010;
    if (fn_80200614(obj, -1, 0x4B) != 0) {
        t = fn_80200534(obj, -1, 0x4B);
        t += fn_80200BDC() - fn_80117E58();
    }
    return t;
}

int fn_800B9D20(void *output, void *arg, void *item, void *type, int last) {
    ItemRecord rec;
    int size;
    int obj;
    void *info;
    void *sub;

    obj = fn_80201B54(type);
    fn_80201BC8(type);
    info = fn_80155DB4(type);
    rec.flags = 0;
    rec.unk18 = fn_80157A08(item, 1);
    rec.unk1A = fn_80157A08(item, 2);
    rec.unk08 = fn_80157C80(item);
    rec.unk04 = fn_8015821C(item);
    rec.unk1C = fn_80157AB8(item);
    rec.unk1D = fn_80157918(item);
    if (rec.unk1C != 0) {
        rec.time = GetTimerValue(obj);
    }
    rec.unk14 = fn_801578E8(item);
    rec.unk16 = fn_801578F4(item);
    rec.unk22 = fn_80157900(item);
    rec.unk1E = fn_80157BD0(item);
    rec.unk1F = fn_80157BDC(item);
    rec.unk20 = fn_80157BC4(item);
    rec.unk10 = fn_801578AC(item);
    if (fn_80156930(info) == 0) {
        rec.flags |= 2;
    }
    if (fn_80156928(info) == 0) {
        rec.flags |= 4;
    }
    if (fn_80156920(info) == 0) {
        rec.flags |= 8;
    }
    if (fn_801579F4(item) != 0) {
        rec.flags |= 0x10;
    }
    if ((int)arg == -1) {
        rec.unk0C = 0;
    } else {
        void *entry = fn_80158598(arg, 0);
        if (fn_801586FC(obj, arg) != 0) {
            rec.flags |= 1;
        }
        rec.unk0C = fn_80158550(entry, obj);
    }
    memcpy(output, &rec, sizeof(ItemRecord));
    size = fn_800B9578((char *)output + sizeof(ItemRecord), type, last, 1) + sizeof(ItemRecord);
    if (rec.flags & 0x10) {
        sub = fn_80201814(fn_801579F4(item));
        size += fn_800B9D20((char *)output + (unsigned short)size, arg, fn_80201C24(sub), sub, last);
    }
    return size;
}
