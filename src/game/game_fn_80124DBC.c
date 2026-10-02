typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Shape {
    u8 data[0x3c];
} Shape;

typedef struct Hit {
    u8 pad00[8];
    float height;
    u8 pad0C[0xC];
} Hit;

typedef struct Table {
    u8 pad00[0x1E];
    u16 count;
} Table;

typedef struct Target {
    u32 flags;
} Target;

typedef struct Owner {
    u8 pad00[8];
    float base;
    u8 pad0C[8];
    float height;
    u8 pad18[0x24];
    Table* table;
    u8 pad40[0x124];
    void* first_buffers[2];
    void* second_buffers[2];
    u8 pad174[0xE0];
    u32 flags;
    u8 pad258[0x48];
    Target* target;
    u8 pad2A4[8];
    float frame;
    u8 pad2B0[0x20];
    u16 state;
    u8 pad2D2[0xC];
    u8 timer;
    u8 step;
} Owner;

extern u8 lbl_8063D378[];
extern float lbl_80650110;
extern float lbl_80650138;
extern float lbl_80650180;
extern s32 lbl_8064D738;
extern u8 lbl_804F3650[];

extern float fn_8017968C(void*, void*);
extern s32 fn_80126050(void*);
extern void fn_80120B58(void*);
extern void fn_801248FC(void*);
extern void fn_80124180(void*, s32);
extern void fn_801243A8(void*);
extern s32 fn_80130998(u16, float);
extern void* fn_80120744(void*, s32, float);
extern void* fn_801208AC(void*, s32, float);
extern void fn_80124A40(void*, void*, u32*, u32*);
extern void fn_80125300(void*, void*, u32, u32, void*, void*, void*, s32,
                       s32, float);
extern s32 fn_8011F134(void*);
extern void fn_80127F90(void*, s32, Vec3*);
extern void* fn_8012AB2C(void*);
extern void fn_8013F3C0(Shape*, Vec3*, Vec3*, float);
extern void* fn_8013FBE4(void*, Shape*, Hit*, s32, s32);
extern void DCFlushRange(void*, u32);

void fn_80124DBC(Owner* owner)
{
    s32 first_count;
    s32 second_count;
    Table* table;
    float frame;
    float scale;
    u32 first;
    u32 second;
    s32 triple;
    Vec3 position;
    Vec3 lowered;
    Shape shape;
    Hit hit;
    void* collision;

    table = owner->table;
    scale = fn_8017968C(owner, lbl_8063D378);
    frame = owner->frame;

    if (owner->target == 0 || lbl_80650110 == frame) {
        return;
    }
    if (!fn_80126050(owner)) {
        return;
    }

    if (owner->flags & 0x10000000) {
        owner->target->flags &= ~2u;
    } else {
        owner->target->flags &= ~2u;
    }
    fn_80120B58(owner);
    if (owner->timer != 0) {
        if (owner->timer < owner->step) {
            owner->timer = 0;
        } else {
            owner->timer -= owner->step;
        }
    }

    if ((owner->flags & 0x80000) == 0) {
        return;
    }

    fn_801248FC(owner);
    fn_80124180(owner, 0);
    fn_801243A8(table);
    first_count = fn_80130998(table->count, frame);
    second_count = fn_80130998(table->count, frame);
    triple = owner->flags & 0x400000;
    if (triple) {
        second_count *= 3;
    }

    owner->first_buffers[lbl_8064D738] = fn_80120744(owner, first_count, frame);
    owner->second_buffers[lbl_8064D738] = fn_801208AC(owner, second_count, frame);

    if (owner->first_buffers[lbl_8064D738] != 0 && owner->second_buffers[lbl_8064D738] != 0) {
        fn_80124A40(owner, table, &first, &second);
        fn_80125300(owner, table, first, second, owner->first_buffers[lbl_8064D738],
                    owner->second_buffers[lbl_8064D738], lbl_804F3650, first_count, triple, scale);
    } else {
        owner->flags &= ~0x80000u;
        owner->first_buffers[lbl_8064D738] = 0;
        owner->second_buffers[lbl_8064D738] = 0;
    }

    DCFlushRange(owner->first_buffers[lbl_8064D738], first_count * 6);
    DCFlushRange(owner->second_buffers[lbl_8064D738], second_count * 6);

    if (owner->state & 0x2000) {
        s32 index = fn_8011F134(owner);
        if (index == 0xFFFF) {
            fn_80127F90(owner, 0, &position);
        } else {
            fn_80127F90(owner, index, &position);
        }

        collision = fn_8012AB2C(owner);
        lowered = position;
        lowered.z -= lbl_80650180;
        fn_8013F3C0(&shape, &position, &lowered, lbl_80650138);
        if (collision != 0) {
            if (fn_8013FBE4(collision, &shape, &hit, 0, 0) != 0) {
                owner->height = hit.height;
                owner->flags |= 0x100;
            } else {
                owner->flags &= ~0x100u;
            }
        } else {
            owner->height = owner->base;
        }
    }
}
