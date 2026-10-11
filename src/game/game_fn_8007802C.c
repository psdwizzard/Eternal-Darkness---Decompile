typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct ActionState {
    u8 padding[0x1C1];
    u8 count;
    u8 unknown1C2;
    u8 busy;
    u8 pending;
} ActionState;

typedef struct Runtime Runtime;
extern void *fn_80201BC8(void *object);
extern s32 fn_80201B54(void *object);
extern void *fn_80200C38(void *node);
extern u32 fn_801A7570(void *data);
extern u16 fn_801A7580(void *data);
extern u32 fn_801A7770(void *data);
extern u32 fn_800FBFB0(void);
extern Runtime *fn_801294DC(void *object, s32 type, s32 value, s32 flags);
extern void fn_80128C44(Runtime *runtime, u32 callback, u32 event);
extern void fn_80128C28(Runtime *runtime, u32 callback, u32 event);
extern int fn_80204810(void *object, int event);
extern void fn_80201D2C(void *object, s32 value);
extern void fn_80201D14(void *object, u8 value);
extern double lbl_8064E888;
extern float lbl_8064E87C;
extern float lbl_8064E900;
extern float lbl_8064E904;

void fn_8007802C(void *object, void *node, ActionState *state)
{
    void *resource;
    s32 action = 0x49;
    s32 objectId;
    void *data;
    s32 chance;
    u16 level;
    register float fraction;
    register float divisor;
    register double converted;
    register double bias;
    register float limit;
    s32 kind;
    union {
        double value;
        struct {
            u32 high, low;
        } words;
    } conversion;

    resource = fn_80201BC8(object);
    objectId = fn_80201B54(object);
    data = fn_80200C38(node);
    state->pending = 0;
    if (fn_801A7570(data) & 0x38) {
        level = fn_801A7580(data);
        chance = 100;
        if (level > 15U) {
            conversion.words.low = (level - 15) ^ 0x80000000;
            conversion.words.high = 0x43300000;
            bias = lbl_8064E888;
            converted = conversion.value;
            divisor = lbl_8064E900;
            limit = lbl_8064E87C;
            /* ASM: fsubs and fdivs use the shared double-word conversion bias
             * and round directly to single precision. With this explicit bias,
             * MWCC emits fsub followed by an extra frsp for the C expression. */
            asm {
                fsubs converted, converted, bias
                fdivs fraction, converted, divisor
            }
            /* ASM: fcmpo, bge, b, fmr preserve the ordered minimum's two
             * branch paths. MWCC folds a C if/else into one branch, or hoists
             * the following scale load when the minimum uses a ternary. */
            asm {
                fcmpo cr0, limit, fraction
                bge use_fraction
                b minimum_done
            use_fraction:
                fmr limit, fraction
            minimum_done:
            }
            chance = 100 - (s32)(lbl_8064E904 * limit);
        }
        if ((s32)fn_800FBFB0() % 100 < chance) {
            if (state->count < 3U && state->busy == 0) {
                kind = fn_801A7770(data);
                if (kind == 2) {
                    action = 0x4A;
                } else if (kind == 3) {
                    action = 0x49;
                } else if (fn_800FBFB0() & 1) {
                    action = 0x4A;
                }
                data = fn_801294DC(resource, action, 0x30, 8);
                if (data != 0) {
                    objectId <<= 8;
                    fn_80128C44(data, (u32)fn_80204810, objectId | 7);
                    fn_80128C28(data, (s32)fn_80204810, objectId | 0x7C);
                    fn_80201D2C(object, 4);
                    fn_80201D14(object, 1);
                }
            } else {
                state->pending = 1;
            }
        }
    }
}
