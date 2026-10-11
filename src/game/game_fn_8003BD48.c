typedef unsigned int u32;

extern u32 fn_80038DAC(void *source, void *target, void *effect);
extern u32 fn_80039044(void *source, void *target, void *effect);
extern int fn_8003957C(void *source, void *target, void *effect);
extern int fn_8003A0B0(void *source, void *target, void *effect);
extern int fn_8003A280(void *source, void *target, void *effect);
extern int fn_8003A6DC(void *source, void *target, void *effect);
extern u32 fn_801A7490(void *effect);
extern u32 fn_801A7498(void *effect);
extern u32 fn_801A74C0(void *effect);
extern u32 fn_801A7560(void *effect, u32 flags);
extern u32 fn_801A7570(void *effect);
extern void *fn_80201814(int id);

int fn_8003BD48(void *unused, register void *effect)
{
    register u32 flags;
    register void *source;
    register void *target;
    register int result;
    register u32 sourceId;
    register u32 targetId;

    result = 0;
    sourceId = fn_801A7498(effect);
    targetId = fn_801A7490(effect);
    source = fn_80201814(sourceId);
    target = fn_80201814(targetId);

    if (source != 0) {
        fn_801A74C0(effect);
        flags = fn_801A7570(effect);
        if (flags & 4) {
            result = fn_8003957C(source, target, effect);
        } else if (flags & 2) {
            result = fn_80039044(source, target, effect);
        } else if (flags & 0x10) {
            result = fn_8003A0B0(source, target, effect);
        } else if (flags & 8) {
            result = fn_8003A280(source, target, effect);
        } else if (flags & 0x10000) {
            result = fn_8003A6DC(source, target, effect);
        } else if (flags & 0x2000) {
            result = fn_8003957C(source, target, effect);
        } else if (flags & 0x4000) {
            result = fn_8003957C(source, target, effect);
        } else {
            result = fn_80038DAC(source, target, effect);
        }
        if ((flags & 0x800) && result != 0) {
            u32 currentFlags = fn_801A7570(effect);
            fn_801A7560(effect, currentFlags | 0x1000);
        }
    }
    return result;
}
