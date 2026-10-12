typedef signed int s32;
typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct QueryResult {
    s32 word0;
    s32 word4;
    Vec3 position;
    u8 pad14[0x14];
} QueryResult;

typedef struct EffectOwner EffectOwner;

extern void *lbl_8064C4E0;
extern float lbl_8064E384;
extern void *memset(void *, int, u32);
extern s32 fn_801E79FC(void *, s32);
extern void fn_801E7974(void *, s32);
extern s32 fn_80201A84(void *);
extern s32 fn_8011F598(void *, s32, s32, s32, QueryResult *, s32);
extern void fn_801A0450(void);
extern void fn_8019D620(u8 *);
extern void *fn_80152BCC(void *, void *, void *, u8 *, u8, u8, int, u8);
extern void *fn_80154DB4(void *, void *, void *, u16, u8, u8, u8, float);
extern void fn_80047CBC(void **, void **);
extern void fn_8007C22C(EffectOwner *, Vec3 *, void *, u8);
extern s32 fn_801E855C(s32, void *, void *);
extern void fn_801E8328(s32, void *);

void fn_80047DF8(void *object, EffectOwner *effect, u8 enabled)
{
    u8 config[0x90];
    QueryResult query;
    void *first;
    void *second;
    u8 mode;
    s32 owner;

    if (fn_801E79FC(lbl_8064C4E0, 0x467) == 0) {
        owner = fn_80201A84(object);
        if (fn_8011F598(object, 3, 15, -1, &query, 1) != -1) {
            memset(config, 0, sizeof(config));
            fn_801A0450();
            fn_8019D620(config);
            mode = 0x11;
            if (enabled != 0) {
                mode = 0x24;
            }
            first = fn_80152BCC((void *)owner, (void *)3, (void *)-1,
                                config, mode, enabled, 1, 250);
            second = fn_80154DB4((void *)owner, (void *)3, (void *)-1,
                                 0, enabled, mode, 255, lbl_8064E384);
            fn_80047CBC(&first, &second);
            if (effect != 0) {
                fn_8007C22C(effect, &query.position, (void *)owner, enabled);
                if (fn_801E855C(0x14, effect, 0) == 0) {
                    fn_801E8328(0x14, effect);
                }
            }
            fn_801E7974(lbl_8064C4E0, 0x467);
        }
    }
}
