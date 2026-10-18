typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct DebugSource {
    u32 value;
    u8 slot;
    u8 pad[3];
} DebugSource;

typedef struct DebugVertex {
    u32 word;
    char text[52];
} DebugVertex;

typedef struct DebugBatch {
    u8 pad0[0x3C];
    u16 count;
    u16 pad3e;
    DebugSource* sources;
    DebugVertex* vertices;
    u8 pad48[4];
    void* output;
} DebugBatch;

extern u32 lbl_8064C4E0;
extern char lbl_8064BA00;
extern char lbl_802FC53C[];

extern void fn_801ED468(int);
extern void GXSetCullMode(int);
extern void fn_801ED118(void);
extern void fn_801EDA7C(void*, int, int, int);
extern void fn_801ECF50(int);
extern void GXSetLineWidth(int, int);
extern int fn_801E79FC(void*, int);
extern void fn_80140E70(void*, DebugVertex*, u8, int, u32);
extern void sprintf(char*, const char*, ...);
extern void fn_800ED4BC(char*, int, const char*, ...);

void fn_80141484(DebugBatch* batch, u32 value)
{
    DebugSource* source;
    DebugVertex* vertices;
    void* output;
    u16 i;

    source = batch->sources;
    vertices = batch->vertices;
    output = batch->output;
    fn_801ED468(0x1B);
    GXSetCullMode(0);
    fn_801ED118();
    fn_801EDA7C(lbl_802FC53C, 0, 0x2BF, 0);
    fn_801ECF50(4);
    GXSetLineWidth(0x12, 0);

    i = 0;
    while (i < batch->count) {
        DebugVertex* vertex = (DebugVertex*)((u8*)vertices + source->slot * 0x38);
        u8 color = fn_801E79FC((void *)lbl_8064C4E0, source->value) ? 6 : 12;
        fn_80140E70(output, vertex, color, 4, value);
        i++;
        source++;
    }

    source = batch->sources;
    i = 0;
    while (i < batch->count) {
        DebugVertex* vertex = (DebugVertex*)((u8*)vertices + source->slot * 0x38);
        char text[24];
        sprintf(text, &lbl_8064BA00, source->value);
        fn_800ED4BC(vertex->text, 3, text);
        i++;
        source++;
    }
}
