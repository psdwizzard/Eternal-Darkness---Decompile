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
    u8 bytes[0x98];
    FirstDescriptor first;
    SecondDescriptor second;
} WorkDescriptor;
#pragma pack()

extern Vec3 lbl_8023A738;
extern float lbl_8064CF04;
extern const float lbl_806504F8;
extern const float lbl_806504FC;
extern const float lbl_80650500;
extern void* lbl_8064C4E0;
extern int lbl_802FC5BC[];

extern void fn_8012B690(void*, Vec3*, Vec3*);
extern int fn_800FBFB0(void);
extern void fn_8017EA58(u8*);
extern int fn_801E79FC(void*, int);
extern void* fn_80148008(Vec3*, Vec3s*, u8*, void (*)(void));
extern void *fn_80156938();
extern void fn_8017FF1C(void*, int);
extern void fn_80183DD4(u8*);
extern void fn_8017EAA8(void);
extern void fn_80183EE0(void);

void fn_8014CCB0(void* context, int* source, unsigned int packed)
{
    Vec3s range;
    Vec3 position;
    Vec3 basis = lbl_8023A738;
    Vec3 first_position;
    Vec3 second_position;
    WorkDescriptor work;
    void* object;
    unsigned int kind;

    if (!(lbl_8064CF04 >= lbl_806504F8)) {
        fn_8012B690(context, &basis, &position);
        range.x = 8 - (fn_800FBFB0() & 0xF);
        range.y = 8 - (fn_800FBFB0() & 0xF);
        range.z = 8;
        fn_8017EA58(work.bytes);
        work.first.source = *source;
        if (fn_801E79FC(lbl_8064C4E0, 0x2ED) != 0)
            work.first.source = lbl_802FC5BC[9];

        if (lbl_8064CF04 >= lbl_806504FC) {
            kind = (packed >> 2) & 0x3F;
            kind = (int)kind > 0 ? kind : packed & 0xFF;
        } else if (lbl_8064CF04 >= lbl_80650500) {
            kind = (packed >> 1) & 0x7F;
            kind = (int)kind > 0 ? kind : packed & 0xFF;
        } else {
            kind = packed & 0xFF;
        }

        work.bytes[0] = kind;
        first_position = position;
        object = fn_80148008(&first_position, &range, work.bytes, fn_8017EAA8);
        if (object != 0)
            fn_8017FF1C(fn_80156938(object), 4);
        fn_80183DD4(work.bytes);

        work.second.source = *source;
        if (fn_801E79FC(lbl_8064C4E0, 0x2ED) != 0)
            work.second.source = lbl_802FC5BC[9];
        work.bytes[0] = 1;
        second_position = position;
        object = fn_80148008(&second_position, &range, work.bytes, fn_80183EE0);
        if (object != 0)
            fn_8017FF1C(fn_80156938(object), 4);
    }
}
