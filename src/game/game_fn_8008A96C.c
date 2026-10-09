typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned short u16;
typedef signed short s16;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Entry {
    u32 packed;
    int type;
    u32 unk8;
} Entry;

typedef struct ObjectInfo {
    u8 pad48[0x48];
    void* field48;
    u8 pad4C[0x3C];
    void* field88;
    void* field8C;
    int field90;
} ObjectInfo;

extern void* fn_80201B8C(u8*);
extern void* fn_80201B94(u8*);
extern int fn_80201B54(int*);
extern void *fn_80201BC8(void*);
extern void* fn_80201C48(void*);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void*, u8);
extern void* fn_80201814(int);
extern void fn_8011F114(Vec3*, Vec3*);
extern u8 fn_80128EE4(void*);
extern int fn_8008A808(void*, int);
extern u8* fn_801294DC(void*, int, int, int);
extern void* fn_801A717C(void);
extern void fn_801A7460(void*, u32);
extern void fn_801A74A0(void*, u32);
extern void fn_801A74A8(void*, u32);
extern u32 fn_801A74C8(void*, u32);
extern u32 fn_801A7560(void*, u32);
extern void fn_801A7538(void*, u16);
extern void fn_801A7518(void*, s16);
extern void fn_801A7550(void*, u32);
extern void fn_801A7558(void*, u32);
extern void fn_801A764C(void*, const void*);
extern void* fn_80072354(int);
extern void fn_801292E0(void*, int*, int*);
extern void fn_801287C4(void*, void*, u32, u32);
extern void fn_80128C28(void*, u32, u32);
extern void fn_80128C44(void*, u32, u32);
extern void fn_8003B8A0(void);
extern int fn_8003BD48(void*, void*);
extern int fn_80204230(int, int);
extern int fn_802042A4(int, int);

int fn_8008A96C(void* object, void* resource, void* unused)
{
    ObjectInfo* info = ((ObjectInfo*)fn_80201B8C(object));
    void* related;
    int offset;
    void* object2 = fn_80201B94(object);
    Vec3 positionCopy;
    Vec3 position;
    register u8 flags;
    register int owner;
    register int success;
    int i;
    int selection;
    void* effect;
    u32 config;
    u8 (*table)[0x34];
    Entry* entries;
    int count;

    fn_8011F114(&position, resource);
    positionCopy = position;
    flags = fn_80128EE4(resource);
    related = fn_80201C48(object2);
    owner = fn_80201B54(object);
    success = 0;
    if ((flags & 0x20) == 0) {
        void* relatedPosition;
        Vec3 temp;
        relatedPosition = fn_80201814((int)related);
        if (relatedPosition != 0) {
            effect = fn_80201BC8(relatedPosition);
            fn_8011F114(&temp, effect);
            selection = fn_8008A808(object, 1);
            if (selection != -1) {
                effect = fn_801294DC(resource, selection, 0, 6);
                if (effect != 0) {
                    config = (u32)fn_801A717C();
                    table = (u8 (*)[0x34])fn_80072354(info->field90);
                    fn_801A7460((void*)config, selection);
                    fn_801A74A0((void*)config, owner);
                    fn_801A74A8((void*)config, (u32)related);
                    fn_801A74C8((void*)config, 1);
                    fn_801A7560((void*)config, 0x84);
                    offset = (selection != 4) << 3;
                    fn_801A7538((void*)config, (*table)[offset + 0x2B]);
                    fn_801A7518((void*)config, (*table)[offset + 0x2A]);
                    fn_801A7550((void*)config, 0xC);
                    fn_801A7558((void*)config, 7);
                    fn_801A764C((void*)config, &positionCopy);
                    fn_801292E0(resource, &count, (int*)&entries);
                    for (i = 0; i < count; i++) {
                        switch (entries[i].type) {
                        case 1: {
                            int value = ((int)entries[i].packed) >> 17;
                            fn_801287C4(effect, fn_8003B8A0, config, value - 3);
                            fn_801287C4(effect, fn_8003BD48, config, value);
                            break;
                        }
                        }
                    }
                    fn_80128C28(effect, (u32)fn_80204230, config);
                    fn_80128C44(effect, (u32)fn_802042A4, config);
                    fn_80201D2C(object, 6);
                    fn_80201D14(object, 1);
                    success = 1;
                }
            }
        }
    }
    return success;
}
