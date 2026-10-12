typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct MeshGroup {
    u16 count;
    u16 first;
    u8 pad[0x110];
} MeshGroup;

typedef struct MeshGroupRange {
    u8 pad;
    u8 count;
    u16 first;
} MeshGroupRange;

typedef struct MeshInfo {
    u8 pad0[0xC];
    u16 group_count;
    u8 padE[0x10];
    u16 vertex_count;
    u8 pad20[8];
    MeshGroup* groups;
    u8 pad2C[0x14];
    MeshGroupRange* ranges;
} MeshInfo;

typedef struct Entry {
    u32 a, b, c;
    int group;
} Entry;

typedef struct MeshOutput {
    u32* data;
    MeshInfo* info;
    Entry* entries;
    int size;
    int entry_count;
    int limit;
} MeshOutput;

extern double lbl_806500B0;
extern u32* lbl_8064CECC;
extern Entry* lbl_8064CED4;
/* The caller also supplies vertex_count in the unused fourth argument slot. */
extern void fn_80122FD0();
extern void fn_80123080(MeshInfo*, int, int, int);
extern void fn_801312C0(MeshInfo*, float);
extern void fn_8013133C(MeshInfo*, int);
extern void DCInvalidateRange(void*, u32);

void fn_80122428(register MeshInfo* arg_info, register MeshOutput* arg_output, register int arg_limit, register int arg_mode, int scaled)
{
    int i;
    register int mode;
    register int limit;
    register MeshInfo* info;
    register MeshOutput* output;
    MeshGroup* group;
    double conversion;
    register float scale;
    register double value, bias;
    register u32 exponent, bits;

    /* ASM: mr preserves the retail order of argument copies; C schedules
     * these copies among the output stores. */
    asm {
        mr info, arg_info
        mr limit, arg_limit
        mr output, arg_output
        mr mode, arg_mode
    }
    output->data = lbl_8064CECC;
    output->entries = lbl_8064CED4;
    output->info = info;
    output->limit = limit;
    if ((u32)scaled == 0) {
        fn_8013133C(arg_info, limit);
    } else {
        /* ASM: xoris, lis, stw, lfd, stw, lfd and fsubs use the shared
         * conversion bias and round directly to single precision. C emits
         * a private bias or a separate double subtraction and rounding. */
        asm {
            xoris bits, limit, 0x8000
            lis exponent, 0x4330
            stw bits, conversion + 4
            lfd bias, lbl_806500B0
            stw exponent, conversion
            lfd value, conversion
            fsubs scale, value, bias
        }
        fn_801312C0(arg_info, scale);
    }
    for (i = 0; i < info->group_count; i++) {
        group = &info->groups[i];
        fn_80122FD0(info, &info->ranges[group->first], group->count, info->vertex_count);
        fn_80123080(info, i, limit, mode);
    }
    output->size = (u8*)lbl_8064CECC - (u8*)output->data;
    output->entry_count = ((int)lbl_8064CED4 - (int)output->entries) / 16;
    DCInvalidateRange(output->data, output->size);
}
