typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Runtime {
    u8 bytes[0x110];
} Runtime;

typedef struct RuntimeBank {
    Runtime runtime[8];
    u16 selected;
} RuntimeBank;

typedef struct Owner {
    Vec3 position;
    Vec3 velocity;
    u8 pad_18[0x28];
    RuntimeBank* bank;
    u8 pad_44[0x210];
    u32 flags;
} Owner;

extern float lbl_806501DC;
extern float lbl_80650200;
extern float lbl_80650204;

extern void* fn_8011F770(void*);
extern float fn_8011F6F8(void*);
extern void PSVECAdd(const Vec3*, const Vec3*, Vec3*);
extern u16 fn_8017E4E4(Vec3*, Vec3*, float, float, float, float);
extern void PSVECSubtract(const Vec3*, const Vec3*, Vec3*);

int fn_8012EB2C(Owner* owner)
{
    Vec3 vector;
    Vec3* anchor;
    u16 hit;

    if ((owner->flags & 4) == 0) {
        anchor = (Vec3*)fn_8011F770(owner);
        PSVECAdd(&owner->position, anchor, &vector);
        hit = fn_8017E4E4(&vector, &owner->velocity, lbl_806501DC,
                          fn_8011F6F8(owner), lbl_80650200,
                          lbl_80650204);
        PSVECSubtract(&vector, anchor, &owner->position);
        if (hit & 1) {
            owner->flags |= 4;
        }
    }
    return 0;
}
