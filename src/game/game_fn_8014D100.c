typedef unsigned char u8;
typedef unsigned short u16;

typedef signed short s16;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Vec3s {
    s16 x, y, z;
} Vec3s;

#pragma pack(1)
typedef struct FirstDescriptor {
    u8 pad[0x1D];
    int source;
} FirstDescriptor;

typedef struct SecondDescriptor {
    u8 pad[0x1C];
    int source;
} SecondDescriptor;

typedef union WorkDescriptor {
    u8 bytes[0x90];
    FirstDescriptor first;
    SecondDescriptor second;
} WorkDescriptor;
#pragma pack()

typedef struct SearchResult {
    u8 pad00[8];
    Vec3 position;
    Vec3 offset;
    u8 pad20[8];
} SearchResult;

extern Vec3 lbl_8023A744;
extern float lbl_8064CF04;
extern const float lbl_806504F8;
extern const float lbl_806504FC;
extern const float lbl_80650500;
extern const float lbl_80650504;
extern void* lbl_8064C4E0;
extern int lbl_802FC5BC[];
extern Vec3s lbl_80651BF0;

extern int fn_8011F6A4(void*, int, int, int, SearchResult*, int);
extern void fn_8012B690(void*, Vec3*, Vec3*);
extern unsigned int fn_800FBFB0(void);
#define fn_800FBFB0() ((int)fn_800FBFB0())
extern void fn_8017EA58(u8*);
extern void fn_80183DD4(u8*);
extern int fn_801E79FC(void*, int);
extern void* fn_80148008(Vec3*, Vec3s*, u8*, void (*)(void));
extern void fn_8017EAA8(void);
extern void fn_80183EE0(void);
extern void *fn_80156938();
extern void fn_8017FF1C(void*, int);
extern void* fn_80201A84(void*);
extern void *fn_80201814();
extern void *fn_80201B8C();
extern int fn_800676C8(u8);
extern int fn_80052310(int, const s16*);

/*
 * Honest NonMatching reconstruction of both effect-spawn paths. The generated
 * code is byte-identical; its remaining difference is the relocation identity
 * for the trailing halfword of the aggregate range initializer.
 */
void fn_8014D100(void* context, int* source, int first_kind, int second_kind)
{
    Vec3s range;
    Vec3s sound_position;
    Vec3 position;
    Vec3 basis = lbl_8023A744;
    Vec3 first_position;
    Vec3 second_position;
    SearchResult search;
    WorkDescriptor work;
    void* object;
    void* owner;
    int reduced;
    unsigned int kind;
    int sound;

    range = lbl_80651BF0;

    if (lbl_8064CF04 >= lbl_806504F8)
        return;

    if (fn_8011F6A4(context, 0x12, 0, -1, &search, 1) != -1) {
        position = search.position;
        range.x = (short)(lbl_80650504 * search.offset.x);
        range.y = (short)(lbl_80650504 * search.offset.y);
        range.z = (short)(lbl_80650504 * search.offset.z);
    } else {
        fn_8012B690(context, &basis, &position);
        range.x = 1 - (fn_800FBFB0() & 3);
        range.y = 1 - (fn_800FBFB0() & 3);
        range.z = -3;
    }

    fn_8017EA58(work.bytes);
    work.first.source = *source;
    if (fn_801E79FC(lbl_8064C4E0, 0x2ED) != 0)
        work.first.source = lbl_802FC5BC[9];
    if (lbl_8064CF04 >= lbl_806504FC) {
        reduced = (first_kind >> 2) & 0x3F;
        kind = first_kind & 0xFF;
        if (reduced > 0)
            kind = reduced;
    } else if (lbl_8064CF04 >= lbl_80650500) {
        reduced = (first_kind >> 1) & 0x7F;
        kind = first_kind & 0xFF;
        if (reduced > 0)
            kind = reduced;
    } else {
        kind = first_kind & 0xFF;
    }
    work.bytes[0] = kind;
    first_position = position;
    object = fn_80148008(&first_position, &range, work.bytes, fn_8017EAA8);
    if (object != 0)
        fn_8017FF1C(fn_80156938(object), 4);

    if ((fn_800FBFB0() & 1) != 0) {
        sound = 50;
        owner = fn_80201B8C(fn_80201814(fn_80201A84(context)));
        range.y = 0;
        range.x = 0;
        range.z = -1;
        fn_80183DD4(work.bytes);
        work.second.source = *source;
        if (fn_801E79FC(lbl_8064C4E0, 0x2ED) != 0)
            work.second.source = lbl_802FC5BC[9];
        if (lbl_8064CF04 >= lbl_806504FC) {
            reduced = (second_kind >> 2) & 0x3F;
            kind = second_kind & 0xFF;
            if (reduced > 0)
                kind = reduced;
        } else if (lbl_8064CF04 >= lbl_80650500) {
            reduced = (second_kind >> 1) & 0x7F;
            kind = second_kind & 0xFF;
            if (reduced > 0)
                kind = reduced;
        } else {
            kind = second_kind & 0xFF;
        }
        work.bytes[0] = kind;
        second_position = position;
        object = fn_80148008(&second_position, &range, work.bytes, fn_80183EE0);
        if (object != 0)
            fn_8017FF1C(fn_80156938(object), 4);
        sound_position.x = (short)position.x;
        sound_position.y = (short)position.y;
        sound_position.z = (short)position.z;
        if (fn_800676C8(*(u8*)((char*)owner + 0x9F)) != 0)
            sound = 84;
        fn_80052310(sound, (s16*)&sound_position);
    }
}
