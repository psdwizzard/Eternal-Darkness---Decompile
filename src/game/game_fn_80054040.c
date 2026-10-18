typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;

#pragma use_lmw_stmw on

typedef struct SetupInfo {
    u8 pad_00[4];
    s32 resource;
    u8 pad_08[8];
    u32 flags;
    u8 pad_14[0x2C];
    s16 type40;
    s16 type42;
    s16 value44;
    u8 pad_46[0x5C];
    s16 valueA2;
    u8 pad_A4[0x25];
    u8 valueC9;
} SetupInfo;

typedef struct CreateInfo {
    float x;
    float y;
    float z;
    u8 pad_0C[8];
    s32 value14;
    u8 pad_18[4];
    s32 value1C;
    s32 value20;
    s32 value24;
    s32 value28;
    u8 pad_2C[8];
    u16 value34;
} CreateInfo;

typedef struct ChildObject {
    u32 flags;
    u8 pad_04[0x142];
    u16 value146;
    u16 value148;
    u16 value14A;
    u8 pad_14C[0x15];
    u8 selector161;
} ChildObject;

typedef struct ParentObject {
    u8 pad_00[0x8C];
    ChildObject* child;
    s32 resource;
    s32 value94;
    u16 value98;
    u16 value9A;
    u16 angle9C;
    u8 type9E;
    u8 type9F;
} ParentObject;

extern void* lbl_8064C74C;
extern void* lbl_8064C750;
extern s8 lbl_8064C550;
extern const unsigned long long lbl_8064DC90;

extern void* fn_8017CDB4(void*);
extern void* fn_80204410(void);
extern void* fn_802016CC(void*);
extern void fn_80201DC8(void*, void*);
extern void fn_80201D4C(void*, void*);
extern void fn_80202054(void*, u16);
extern void fn_80201DF8(void*, s16);
extern void fn_80201DE0(void*, s32);
extern void fn_80201E60(void*, s32);
extern void fn_80035534(ChildObject*, SetupInfo*);
extern s32 fn_80072368(s32);
extern unsigned int rand(void);
#define rand() ((int)rand())
extern void fn_80201D3C(void*, s32);
extern void fn_80201D44(void*, s32);
extern void fn_80138614(s32);
extern void* fn_8011EE04(float, float, float);
extern void fn_80201DD0(void*, void*);
extern u32 fn_8011FAEC(void*);
extern void fn_8012A23C(void*, s16);
extern void fn_8011FADC(void*, u32);

void* fn_80054040(register void* callback, register SetupInfo* setup,
                  register CreateInfo* create)
{
    ParentObject* parent = fn_8017CDB4(lbl_8064C74C);
    void* context = fn_80204410();
    void* result = fn_802016CC(callback);
    ChildObject* child;
    u32 flags;
    u32 setup_flags;
    u32 child_flags;

    fn_80201DC8(result, context);
    fn_80201D4C(result, parent);
    fn_80202054(result, create->value34);
    fn_80201DF8(context, setup->value44);
    fn_80201DE0(context, create->value24);
    fn_80201E60(context, 0);

    child = fn_8017CDB4(lbl_8064C750);
    parent->child = child;
    fn_80035534(parent->child, setup);

    parent->child->value146 = create->value1C;
    parent->child->value148 = create->value20;
    parent->child->value14A = 150;
    parent->child->selector161 = ((const u8*)&lbl_8064DC90)[lbl_8064C550];
    lbl_8064C550 = lbl_8064C550 >= 3 ? 0 : lbl_8064C550 + 1;

    parent->resource = fn_80072368(setup->resource);
    parent->value98 = setup->resource;
    parent->value9A = create->value14;
    parent->type9E = setup->type40;
    parent->type9F = setup->type42;
    parent->value94 = setup->valueC9;
    parent->angle9C = (rand() & 0x3FF) + 0x400;

    fn_80201D3C(result, 2);
    fn_80201D44(result, create->value28);
    parent->child->flags = 0;
    if (setup->flags & 0x20) {
        child_flags = parent->child->flags | 1;
    } else {
        child_flags = parent->child->flags & 0xFFFFFFFE;
    }
    parent->child->flags = child_flags;

    fn_80138614(create->value14);
    create = fn_8011EE04(create->x, create->y, create->z);
    fn_80201DD0(result, create);
    flags = fn_8011FAEC(create);
    setup_flags = setup->flags;

    flags = (setup_flags & 2) ? flags | 0x40 : flags & 0xFFFFFFBF;
    flags = (setup_flags & 1) ? flags | 0x80 : flags & 0xFFFFFF7F;
    flags = (setup_flags & 4) ? flags & 0xFFFFF7FF : flags | 0x800;
    flags = (setup_flags & 8) ? flags & 0xFFFFFFFD : flags | 2;
    flags = (setup_flags & 0x40) ? flags | 0x100000 : flags & 0xFFEFFFFF;
    if (parent->type9E == 3) {
        flags &= 0xFFFFFEFF;
    } else {
        flags = (setup_flags & 0x10) ? flags | 0x100 : flags & 0xFFFFFEFF;
    }

    fn_8012A23C(create, setup->valueA2);
    fn_8011FADC(create, flags);
    return result;
}
