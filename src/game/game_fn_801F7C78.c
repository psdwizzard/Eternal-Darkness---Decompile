typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef void (*Callback)(void*);

typedef struct Obj {
    float value;
    unsigned char pad04[0x44];
    Vec3 vector;
    unsigned char pad54[0x18];
    Callback callback;
    void* target;
    void* link;
    unsigned char pad78[0x10];
} Obj;

extern Obj lbl_8063C6B8[];
extern unsigned char lbl_8023B7E4[];
extern int lbl_8064C3A0;
extern int lbl_8064C3A4;
extern int lbl_8064D798;
extern int lbl_8064D79C;
extern int lbl_8064D7BC;
extern float lbl_80651464;
extern float lbl_8065148C;
extern float lbl_80651490;
extern float lbl_80651494;
extern float lbl_80651498;
extern float lbl_8065149C;

extern void fn_801F7034(void*, int);
extern void fn_801FA410(int);
extern void fn_801F76D8(int, int, int, float);
extern void fn_801F7804(void*);
extern void fn_801F7AD4(void*);

#define PTR(p, o) (*(void**)((unsigned char*)(p) + (o)))
#define FLT(p, o) (*(float*)((unsigned char*)(p) + (o)))
#define CB(p, o) (*(Callback*)((unsigned char*)(p) + (o)))
#define VEC(p, o) (*(Vec3*)((unsigned char*)(p) + (o)))

#pragma use_lmw_stmw on
#pragma opt_lifetimes off
void fn_801F7C78(void)
{
    Vec3 initial = *(Vec3*)lbl_8023B7E4;
    Obj* base = lbl_8063C6B8;
    Obj* first;
    Obj* second;
    float zero;
    int i;

    lbl_8064C3A0 = 2;
    lbl_8064D798 = 0;
    lbl_8064C3A4 = 2;
    lbl_8064D79C = 0;
    fn_801F7034(&base[24], 1);
    fn_801F7034(&base[25], 1);
    base[25].value = lbl_8065148C;
    base[24].link = &base[25];
    fn_801FA410(2);
    fn_801F76D8(0, 0, 0, lbl_80651464);
    base[24].callback = fn_801F7804;
    base[25].callback = fn_801F7804;
    zero = lbl_8065148C;
    lbl_8064D7BC = 0;

    first = base;
    second = &base[12];
    for (i = 0; i < 12; i++) {
        fn_801F7034(second, 1);
        fn_801F7034(first, 1);
        first->value = zero;
        second->link = first;
        first->vector = initial;
        second->vector = initial;
        first++;
        second++;
    }

    if (base[24].target != 0) {
        base[24].vector = ((Obj*)base[24].target)->vector;
    }

    second = &base[12];
    FLT(second, 0x440) = lbl_80651490;
    FLT(second, 0x444) = lbl_80651494;
    FLT(second, 0x448) = lbl_8065148C;
    CB(second, 0x6C) = fn_801F7AD4;
    CB(second, 0xF4) = fn_801F7804;
    FLT(second, 0x474) = lbl_80651498;
    VEC(base, 0x440) = VEC(second, 0x440);
    FLT(base, 0x440) = lbl_8065149C;
}
#pragma use_lmw_stmw off
#pragma opt_lifetimes reset
