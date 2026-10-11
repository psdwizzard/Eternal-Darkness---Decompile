typedef unsigned short u16;
typedef signed short s16;

typedef struct SceneHeader {
    s16 objectCount;
    s16 nodeCount;
    unsigned int messageFlags;
    s16 effectCount;
    u16 resourceCount;
    unsigned char reserved[8];
} SceneHeader;

typedef struct EffectRecord {
    u16 unknown;
    u16 kind;
    s16 position[3];
    s16 reserved;
} EffectRecord;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern void *memcpy(void *, const void *, unsigned int);
extern int fn_8004527C(void);
extern int fn_80201B44(void);
extern void *fn_80201814(int);
extern void *fn_80201BC8(void *);
extern void *fn_80204A8C(void);
extern u16 fn_800BB1EC(void *, int, void *, void *);
extern void fn_800449EC(int, int);
extern void *fn_800BA6D4(void *, int, u16 *, int, int);
extern u16 fn_800BB3F8(void *, unsigned int);
extern void fn_80179DB0(float *, s16 *);
extern void *fn_800CF3D4(Vec3 *, int, int, int);

u16 fn_800BB270(void *input)
{
    SceneHeader header;
    EffectRecord effect;
    Vec3 position;
    u16 resource;
    u16 size;
    u16 offset;
    int i;
    int j;
    int k;
    int mode;
    void *context;

    mode = fn_8004527C();
    fn_80201BC8(fn_80201814(fn_80201B44()));
    context = fn_80204A8C();
    memcpy(&header, input, sizeof(header));
    offset = 0x14;
    offset += fn_800BB1EC((char *)input + 0x14, header.objectCount,
                         context, (void *)-1);
    for (i = 0; i < header.resourceCount; i++) {
        memcpy(&resource, (char *)input + offset, sizeof(resource));
        offset += 2;
        fn_800449EC(resource, mode);
    }
    for (j = 0; j < header.nodeCount; j++) {
        fn_800BA6D4((char *)input + offset, -1, &size, 0, 1);
        offset += size;
    }
    if (header.messageFlags != 0) {
        /* The serialized byte offset wraps at 16 bits. */
        offset = (offset & 0xFFFF) + fn_800BB3F8((char *)input + offset, header.messageFlags);
    }
    if (header.effectCount != 0) {
        for (k = 0; k < header.effectCount; k++) {
            memcpy(&effect, (char *)input + offset, sizeof(effect));
            offset += 12;
            fn_80179DB0(&position.x, effect.position);
            fn_800CF3D4(&position, 0, 0, effect.kind);
        }
    }
    return (offset + 31) & 0xFFE0;
}
