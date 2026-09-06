typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct GlobalState80093264 {
    u32 pad00[2];
    int mode;
} GlobalState80093264;

extern GlobalState80093264 lbl_803003C8;
extern int lbl_8064D18C;
extern u32 lbl_8064EC80;
extern u16 lbl_8064EC84;
extern u8 lbl_8064EC86;

extern void fn_800DE354(void);
extern void *fn_80201814();
extern int fn_80201EB8();
extern void *fn_80201BC8();
extern u16 fn_8012DBE8(void*, int, u32*);
extern int fn_800CB098(int, int, int, int, int, int);
extern int fn_80201B44();
extern int fn_80036E50(void);

int fn_80093264(void)
{
    u32 info;
    struct {
        u32 first;
        u16 second;
        u8 last;
    } types;
    u8* type;
    int result = 0;
    u32 i;
    int objectId;

    types.first = lbl_8064EC80;
    types.second = lbl_8064EC84;
    types.last = lbl_8064EC86;

    if (lbl_803003C8.mode == 9) {
        void* object;
        fn_800DE354();
        object = fn_80201814();
        objectId = fn_80201EB8();
        if (object != 0 && objectId == lbl_8064D18C) {
            if (!fn_8012DBE8(fn_80201BC8(object), 15, &info) ||
                ((u8*)&info)[3] >= 25) {
                return -1;
            }
        }
    }

    type = (u8*)&types;
    for (i = 0; i < 7 && result == 0; type++, i++) {
        result += fn_800CB098(2, (signed char)*type, -1,
                              lbl_8064D18C, 1, 0);
    }

    fn_80201B44();
    if (fn_80201814() != 0) {
        switch (fn_80036E50()) {
        case 3:
        case 4:
        case 6:
            result++;
        }
    }
    return result;
}
