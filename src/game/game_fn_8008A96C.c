typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Vec3 {
    u32 x, y, z;
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
    void* field90;
} ObjectInfo;

extern void *fn_80201B8C();
extern void* fn_80201B94();
extern int fn_80201B54();
extern void *fn_80201BC8(void*);
extern void* fn_80201C48(void*);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern void *fn_80201814();
extern void fn_8011F114(Vec3*, void*);
extern int fn_80128EE4(void*);
extern int fn_8008A808(void*, int);
extern void *fn_801294DC(void *, int, int, int);
extern void* fn_801A717C(void);
extern void fn_801A7460(void*, int);
extern void fn_801A74A0(void*, void*);
extern void fn_801A74A8(void*, void*);
extern void fn_801A74C8(void*, int);
extern void fn_801A7560(void*, int);
extern void fn_801A7538(void*, int);
extern void fn_801A7518(void*, int);
extern void fn_801A7550(void*, int);
extern void fn_801A7558(void*, int);
extern void fn_801A764C(void*, Vec3*);
extern void* fn_80072354(void*);
extern void fn_801292E0(void*, int*, Entry**);
extern void fn_801287C4(void*, void*, void*, int);
extern void fn_80128C28();
extern void fn_80128C44(void*, void*, void*);
extern void fn_8003B8A0(void);
extern void fn_8003BD48(void);
extern void fn_80204230(void);
extern void fn_802042A4(void);

/* NonMatching: behavior-complete effect setup and callback registration. The
 * remaining differences are one temporary-preservation instruction, two
 * commutative add operand orders, and nearby instruction scheduling. */
int fn_8008A96C(void* object, void* resource, void* unused)
{
    ObjectInfo* info = ((ObjectInfo*)fn_80201B8C(object));
    void* related;
    int offset;
    void* object2 = fn_80201B94(object);
    Vec3 positionCopy;
    Vec3 position;
    int flags;
    void* owner;
    int success;
    int i;
    int selection;
    void* effect;
    void* config;
    void* table;
    Entry* entries;
    int count;

    fn_8011F114(&position, resource);
    positionCopy = position;
    flags = fn_80128EE4(resource);
    related = fn_80201C48(object2);
    owner = ((void*)fn_80201B54(object));
    success = 0;

    if ((flags & 0x20) == 0) {
        void* relatedPosition;
        Vec3 temp;
        relatedPosition = fn_80201814(related);
        if (relatedPosition != 0) {
            fn_8011F114(&temp, fn_80201BC8(relatedPosition));
            selection = fn_8008A808(object, 1);
            if (selection != -1) {
                effect = fn_801294DC(resource, selection, 0, 6);
                if (effect != 0) {
                    config = fn_801A717C();
                    table = fn_80072354(info->field90);
                    fn_801A7460(config, selection);
                    fn_801A74A0(config, owner);
                    fn_801A74A8(config, related);
                    fn_801A74C8(config, 1);
                    fn_801A7560(config, 0x84);
                    offset = (selection != 4) << 3;
                    fn_801A7538(config, *((u8*)table + offset + 0x2B));
                    fn_801A7518(config, *((u8*)table + offset + 0x2A));
                    fn_801A7550(config, 0xC);
                    fn_801A7558(config, 7);
                    fn_801A764C(config, &positionCopy);
                    fn_801292E0(resource, &count, &entries);
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
                    fn_80128C28(effect, fn_80204230, config);
                    fn_80128C44(effect, fn_802042A4, config);
                    fn_80201D2C(object, 6);
                    fn_80201D14(object, 1);
                    success = 1;
                }
            }
        }
    }
    return success;
}
