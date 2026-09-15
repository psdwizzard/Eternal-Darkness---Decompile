typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern int lbl_8064D18C;
extern u32 lbl_8064D5A8;

extern void fn_8017E17C(Vec3*, Vec3*);
extern u32 fn_80179064(int, int, int, int);
extern u16 fn_8011F760(void*);
extern float fn_8011F6F0(void*);
extern void* fn_80201B9C(void);
extern void* fn_80201BC0(void*);
extern void* fn_80201BC8(void*);
extern int fn_80201B4C(void*);
extern void* fn_80201B54(void*);
extern int fn_80201EB8(void*);
extern void fn_80201E78(Vec3*, void*);
extern u64 fn_8020123C(int, int, void*, void*);
extern void* fn_801A717C(void);
extern void fn_801A74A0(void*, int);
extern void fn_801A74A8(void*, void*);
extern void fn_801A7538(void*, int);
extern void fn_801A7518(void*, int);
extern void fn_801A7588(void*, int);
extern void fn_801A764C(void*, Vec3*);
extern void fn_801A7470(void*, int);
extern void fn_801A7668(void*, u32);
extern void fn_801A7228(void*);

int fn_8018F378(u8* self)
{
    u8* entry = *(u8**)(self + 0x4C);

    if (*(u16*)(self + 0xA) < *(u16*)(self + 0xC)) {
        Vec3 position;
        void* iterator;

        position.x = *(s16*)(entry + 0xA);
        position.y = *(s16*)(entry + 0xC);
        position.z = *(s16*)(entry + 0xE);
        fn_8017E17C(&position, (Vec3*)(self + 0x98));
        *(s16*)(entry + 0xA) = position.x;
        *(s16*)(entry + 0xC) = position.y;
        *(s16*)(entry + 0xE) = position.z;

        if (*(u16*)(self + 0xAC) != 0 && (lbl_8064D5A8 & 1) != 0) {
            for (iterator = fn_80201B9C(); iterator != 0;
                 iterator = fn_80201BC0(iterator)) {
                int kind = fn_80201EB8(iterator);
                int state = fn_80201B4C(iterator);
                Vec3 other_position;
                Vec3 entry_position;
                Vec3 fetched_position;
                void* owner;
                void* object;
                u16 bound_x;
                u16 bound_z;
                u32 delta_x;
                u32 delta_z;

                if (self[0xB0] == 2 && state == 0)
                    continue;
                if (kind != lbl_8064D18C)
                    continue;
                if (state != 0 && state != 1)
                    continue;

                fn_80201E78(&fetched_position, iterator);
                other_position = fetched_position;
                owner = fn_80201B54(iterator);
                object = fn_80201BC8(iterator);
                if (object == 0)
                    continue;
                bound_x = fn_8011F760(object);
                bound_z = (u16)fn_8011F6F0(object);
                delta_x = fn_80179064((int)other_position.x,
                                      (int)other_position.y,
                                      *(s16*)(entry + 0xA),
                                      *(s16*)(entry + 0xC));
                delta_z = fn_80179064((int)other_position.x,
                                      (int)other_position.z,
                                      *(s16*)(entry + 0xA),
                                      *(s16*)(entry + 0xE));
                if (delta_x > bound_z || delta_z > bound_x)
                    continue;
                if ((u32)fn_8020123C(0x3B, 0, owner, 0) != 1)
                    continue;

                {
                    void* effect = fn_801A717C();
                    fn_801A74A0(effect, 0);
                    fn_801A74A8(effect, owner);
                    fn_801A7538(effect, 1);
                    fn_801A7518(effect, *(s16*)(self + 0xAC));
                    fn_801A7588(effect, 0x8000);
                    fn_801A764C(effect, &position);
                    fn_801A7470(effect, 0xB);
                    fn_801A7668(effect, *(u32*)(self + 0xA8));
                    entry_position.x = *(s16*)(entry + 0xA);
                    entry_position.y = *(s16*)(entry + 0xC);
                    entry_position.z = *(s16*)(entry + 0xE);
                    fn_801A764C(effect, &entry_position);
                    *(u16*)(self + 0xAC) = 0;
                    fn_8020123C(0xB, 0, owner, effect);
                    fn_801A7228(effect);
                    *(u16*)(self + 0x22) = 8;
                    break;
                }
            }
        }
    } else {
        *(u16*)(self + 0x22) = 8;
    }

    ++*(u16*)(self + 0xA);
    if (lbl_8064D18C != *(int*)(self + 0x38))
        *(u16*)(self + 0x22) = 8;
    return 1;
}
