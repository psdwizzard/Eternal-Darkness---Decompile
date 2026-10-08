typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Effect {
    u8 pad0[0x10];
    s16 starts[3];
    u8 pad16[0x36];
    u8* owner;
    u8 pad50[0x3f];
    u8 kind;
    u8 pad90[7];
    u8 count;
    u8 mode;
    u8 pad99[3];
    u16 channel_flags[3];
    s16 targets[3];
    s16 steps[3];
    u8 padAE[6];
    s16 bounds[3][13];
    u8 pad102[6];
    u32 flags;
    float scales[3];
} Effect;

extern const float lbl_80650B70;

void fn_801871F0(u8*, u16*, s16*, int, int, int, int, int, int, int);
void fn_80187320(u8*, u16*, s16*, int, int, int, int, int, float, int);
void fn_80187488(u8*, u16*, s16*, int, int, int, s16*, s16*, int, int);
void fn_801875FC(u8*, u16*, s16*, int, int, int, s16*, s16*, int, int);

void fn_80195AEC(int arg)
{
    int end;
    u8* owner;
    s16* starts;
    Effect* object;
    u16* flags0;
    u16* flags1;
    u16* flags2;
    s16* bounds0;
    s16* bounds1;
    s16* bounds2;
    u8 count;
    u32 flags;
    u8 mode;
    int kind;

    flags = ((Effect*)arg)->flags;
    object = (Effect*)arg;
    flags0 = &object->channel_flags[0];
    flags1 = &object->channel_flags[1];
    count = object->count - 4;
    arg = ((Effect*)arg)->channel_flags[0];
    kind = object->kind;
    mode = object->mode;
    owner = object->owner;
    flags2 = &object->channel_flags[2];
    bounds0 = object->bounds[0];
    bounds1 = object->bounds[1];
    bounds2 = object->bounds[2];
    end = (arg & 7) + 1;
    starts = object->starts;
    if (flags & 0x8000) {
        if (object->flags & 0x32000) {
            if (object->flags & 0x10000) {
                fn_801875FC(owner + 0x38, flags0, bounds0, 0, 0, count,
                            starts, object->targets, mode, end);
            } else {
                fn_80187320(owner + 0x38, flags0, bounds0, 0, 0, count,
                            starts[0], kind, object->scales[0], end);
            }
            if (object->flags & 0x20000) {
                fn_801875FC(owner + 0x38, flags1, bounds1, 1, 0, count,
                            starts, object->targets, mode, end);
            } else {
                fn_80187320(owner + 0x38, flags1, bounds1, 1, 0, count,
                            starts[1], kind, object->scales[1], end);
            }
            if (object->flags & 0x2000) {
                fn_801875FC(owner + 0x38, flags2, bounds2, 2, 0, count,
                            starts, object->targets, mode, end);
            } else {
                fn_80187320(owner + 0x38, flags2, bounds2, 2, 0, count,
                            starts[2], kind, object->scales[2], end);
            }
        } else if (object->flags & 0x100) {
            int half;
            u8 whole;
            int rest;
            float scale;

            whole = count;

            fn_80187320(owner + 0x38, flags0, bounds0, 0, 0, whole,
                        starts[0], kind, object->scales[0], end);
            fn_80187320(owner + 0x38, flags1, bounds1, 1, 0, whole,
                        starts[1], kind, object->scales[1], end);
            half = whole >> 1;
            scale = lbl_80650B70 * object->scales[2];
            fn_80187320(owner + 0x38, flags2, bounds2, 2, 0, half,
                        starts[2], kind, scale, end);
            rest = whole - half;
            fn_80187320(owner + 0x38 + half * 0x38, flags2, bounds2, 2,
                        half, whole, (int)((float)half * scale + (float)starts[2]), kind,
                        object->scales[2] / (float)rest, end);
        } else if (object->flags & 0x400) {
            int rest;
            int whole;
            u8* entry;
            int half;
            float scale;

            whole = count;
            half = whole >> 1;

            scale = lbl_80650B70 * object->scales[0];
            fn_80187320(owner + 0x38, flags0, bounds0, 0, 0, half,
                        starts[0], kind, scale, end);
            rest = whole - half;
            entry = owner + 0x38 + half * 0x38;
            fn_80187320(entry, flags0, bounds0, 0, half, whole,
                        (int)((float)half * scale + (float)starts[0]), kind,
                        object->scales[0] / (float)rest, end);

            scale = lbl_80650B70 * object->scales[1];
            fn_80187320(owner + 0x38, flags1, bounds1, 1, 0, half,
                        starts[1], kind, scale, end);
            fn_80187320(entry, flags1, bounds1, 1, half, whole, (int)((float)half * scale + (float)starts[1]), kind,
                        object->scales[1] / (float)rest, end);

            scale = lbl_80650B70 * object->scales[2];
            fn_80187320(owner + 0x38, flags2, bounds2, 2, 0, half,
                        starts[2], kind, scale, end);
            fn_80187320(entry, flags2, bounds2, 2, half, whole, (int)((float)half * scale + (float)starts[2]), kind,
                        object->scales[2] / (float)rest, end);
        } else {
            fn_80187320(owner + 0x38, flags0, bounds0, 0, 0, count,
                        starts[0], kind, object->scales[0], end);
            fn_80187320(owner + 0x38, flags1, bounds1, 1, 0, count,
                        starts[1], kind, object->scales[1], end);
            fn_80187320(owner + 0x38, flags2, bounds2, 2, 0, count,
                        starts[2], kind, object->scales[2], end);
        }
    } else {
        if (object->flags & 0x32000) {
            if (object->flags & 0x10000) {
                fn_80187488(owner + 0x38, flags0, bounds0, 0, 0, count,
                            starts, object->targets, mode, end);
            } else {
                fn_801871F0(owner + 0x38, flags0, bounds0, 0, 0, count,
                            starts[0], object->steps[0], kind, end);
            }
            if (object->flags & 0x20000) {
                fn_80187488(owner + 0x38, flags1, bounds1, 1, 0, count,
                            starts, object->targets, mode, end);
            } else {
                fn_801871F0(owner + 0x38, flags1, bounds1, 1, 0, count,
                            starts[1], object->steps[1], kind, end);
            }
            if (object->flags & 0x2000) {
                fn_80187488(owner + 0x38, flags2, bounds2, 2, 0, count,
                            starts, object->targets, mode, end);
            } else {
                fn_801871F0(owner + 0x38, flags2, bounds2, 2, 0, count,
                            starts[2], object->steps[2], kind, end);
            }
        } else if (object->flags & 0x100) {
            u8 whole;
            int half;
            int step;

            whole = count;

            fn_801871F0(owner + 0x38, flags0, bounds0, 0, 0, whole,
                        starts[0], object->steps[0], kind, end);
            fn_801871F0(owner + 0x38, flags1, bounds1, 1, 0, whole,
                        starts[1], object->steps[1], kind, end);
            half = whole >> 1;
            step = object->steps[2] * 2;
            fn_801871F0(owner + 0x38, flags2, bounds2, 2, 0, half,
                        starts[2], step, kind, end);
            fn_801871F0(owner + 0x38 + half * 0x38, flags2, bounds2, 2,
                        half, whole, starts[2] + half * step, object->steps[2] / (whole - half),
                        kind, end);
        } else if (object->flags & 0x400) {
            int half;
            int whole;
            int rest;
            int step;
            u8* entry;

            whole = count;
            half = whole >> 1;

            step = object->steps[0] * 2;
            fn_801871F0(owner + 0x38, flags0, bounds0, 0, 0, half,
                        starts[0], step, kind, end);
            rest = whole - half;
            entry = owner + 0x38 + half * 0x38;
            fn_801871F0(entry, flags0, bounds0, 0, half, whole, starts[0] + half * step,
                        object->steps[0] / rest, kind, end);

            step = object->steps[1] * 2;
            fn_801871F0(owner + 0x38, flags1, bounds1, 1, 0, half,
                        starts[1], step, kind, end);
            fn_801871F0(entry, flags1, bounds1, 1, half, whole, starts[1] + half * step,
                        object->steps[1] / rest, kind, end);

            step = object->steps[2] * 2;
            fn_801871F0(owner + 0x38, flags2, bounds2, 2, 0, half,
                        starts[2], step, kind, end);
            fn_801871F0(entry, flags2, bounds2, 2, half, whole, starts[2] + half * step,
                        object->steps[2] / rest, kind, end);
        } else {
            fn_801871F0(owner + 0x38, flags0, bounds0, 0, 0, count,
                        starts[0], object->steps[0], kind, end);
            fn_801871F0(owner + 0x38, flags1, bounds1, 1, 0, count,
                        starts[1], object->steps[1], kind, end);
            fn_801871F0(owner + 0x38, flags2, bounds2, 2, 0, count,
                        starts[2], object->steps[2], kind, end);
        }
    }
}
