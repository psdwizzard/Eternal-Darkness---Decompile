typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;

#pragma use_lmw_stmw on

typedef struct Vec3s {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

typedef struct Vec3f {
    float x;
    float y;
    float z;
} Vec3f;

typedef struct EffectRecord {
    u32 pad00;
    void* object;
    s32 type;
    u32 pad0C;
} EffectRecord;

typedef struct EffectList {
    u8 pad00[8];
    u8 count;
    u8 pad09[3];
    EffectRecord* records;
} EffectList;

typedef struct TransitionEffectState {
    u8 pad000[0x1B8];
    u8 values[12];
    u32 flags;
} TransitionEffectState;

typedef struct Object Object;

extern TransitionEffectState lbl_8030F540;
extern void* lbl_8064C848;
extern const double lbl_8064E4E0;

extern void* fn_8015E4A4(void);
extern void* fn_80156938(Object*);
extern void* fn_8017FDE4(void*);
extern void* fn_801938A8(void*);
extern int fn_80156FF4(Object*);
extern void* fn_801D5898(Vec3f*, Vec3f*, int, int, int, u8, u8, u8, u8, u8,
                         int, u8, u8, u8, u8, u32, u32);
extern u32 fn_80193860(void*);
extern void fn_801938D8(void*, u32);
extern void fn_801938E0(void*, s8);
extern void fn_801938D0(void*, u8);

void fn_800542D0(u8 first, u8 second, u8 third, u8 fourth, u8 fifth,
                 u8 sixth, u8 seventh, u8 eighth, u8 ninth, u8 tenth,
                 u8 eleventh, u8 twelfth, s32 flags)
{
    Vec3f first_float;
    Vec3f second_float;
    Vec3s* first_pos;
    Vec3s* second_pos;
    s32 offset;
    s32 index;
    EffectList* list = fn_8015E4A4();

    lbl_8030F540.values[0] = (s8)first != -1 ? first : lbl_8030F540.values[0];
    lbl_8030F540.values[1] = (s8)second != -1 ? second : lbl_8030F540.values[1];
    lbl_8030F540.values[2] = (s8)third != -1 ? third : lbl_8030F540.values[2];
    lbl_8030F540.values[3] = (s8)fourth != -1 ? fourth : lbl_8030F540.values[3];
    lbl_8030F540.values[4] = (s8)fifth != -1 ? fifth : lbl_8030F540.values[4];
    lbl_8030F540.values[5] = (s8)sixth != -1 ? sixth : lbl_8030F540.values[5];
    lbl_8030F540.values[6] = (s8)seventh != -1 ? seventh : lbl_8030F540.values[6];
    lbl_8030F540.values[7] = (s8)eighth != -1 ? eighth : lbl_8030F540.values[7];
    lbl_8030F540.values[8] = (s8)ninth != -1 ? ninth : lbl_8030F540.values[8];
    lbl_8030F540.values[9] = (s8)tenth != -1 ? tenth : lbl_8030F540.values[9];
    lbl_8030F540.values[10] = (s8)eleventh != -1 ? eleventh : lbl_8030F540.values[10];
    lbl_8030F540.values[11] = (s8)twelfth != -1 ? twelfth : lbl_8030F540.values[11];
    lbl_8030F540.flags = flags != -1 ? flags : lbl_8030F540.flags;

    index = 0;
    offset = 0;
    while (index < list->count) {
        if (((EffectRecord*)((u8*)list->records + offset))->object != 0) {
            switch (((EffectRecord*)((u8*)list->records + offset))->type) {
            case 0x23:
            case 0x24:
            case 0x25:
            case 0x26:
            case 0x28:
            case 0x2B: {
                lbl_8064C848 = fn_80156938(
                    ((EffectRecord*)((u8*)list->records + offset))->object);
                first_pos = fn_8017FDE4(lbl_8064C848);
                second_pos = fn_801938A8(lbl_8064C848);
                first_float.x = first_pos->x;
                first_float.y = first_pos->y;
                first_float.z = first_pos->z;
                second_float.x = second_pos->x;
                second_float.y = second_pos->y;
                second_float.z = second_pos->z;
                fn_80156FF4(
                    ((EffectRecord*)((u8*)list->records + offset))->object);
                /* Explicit byte casts preserve GC/1.3 argument temporaries. */
                ((EffectRecord*)((u8*)list->records + offset))->object = fn_801D5898(
                    &first_float, &second_float, 1,
                    (u8)lbl_8030F540.values[0], (u8)lbl_8030F540.values[1],
                    (u8)lbl_8030F540.values[2], (u8)lbl_8030F540.values[3],
                    (u8)lbl_8030F540.values[4], (u8)lbl_8030F540.values[5],
                    (u8)lbl_8030F540.values[6], (u8)lbl_8030F540.values[7],
                    (u8)lbl_8030F540.values[8], (u8)lbl_8030F540.values[9],
                    (u8)lbl_8030F540.values[10], 0x84,
                    lbl_8030F540.flags | 8, 0);
                if (((EffectRecord*)((u8*)list->records + offset))->object != 0) {
                    lbl_8064C848 = fn_80156938(
                        ((EffectRecord*)((u8*)list->records + offset))->object);
                    fn_801938D8(lbl_8064C848,
                                fn_80193860(lbl_8064C848) | 0x848);
                    fn_801938E0(lbl_8064C848, 1);
                    fn_801938D0(lbl_8064C848,
                                (u8)lbl_8030F540.values[11]);
                }
                break;
            }
            }
        }
        offset += 0x10;
        index++;
    }
}
