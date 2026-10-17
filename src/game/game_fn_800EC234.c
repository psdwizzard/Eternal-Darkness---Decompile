typedef unsigned char u8;
typedef unsigned short u16;
typedef signed char s8;
typedef signed short s16;

typedef struct Vector {
    float x;
    float y;
    float z;
} Vector;

typedef struct DebugSource {
    u8 pad0[0x28];
    void* value;
    u8 pad2c[0x2C];
    u8 slot;
    u8 pad59[3];
} DebugSource;

typedef struct DebugMeshPart {
    u16 count;
    u16 pad;
    u16* indices;
} DebugMeshPart;

/* Layout from fn_80140E70, with the position in pad0 identified here. */
typedef struct DebugMesh {
    u8 pad0[4];
    Vector position;
    u8 pad10[4];
    float offset[3];
    u8 pad20[8];
    u16 count;
    u16 pad2a;
    u16* indices;
    s8 part_count;
    u8 pad31[3];
    DebugMeshPart* parts;
} DebugMesh;

typedef struct DebugBatch {
    u8 pad0[0x20];
    u16 count;
    u16 pad22;
    DebugSource* sources;
    DebugMesh* meshes;
    u8 pad2c[4];
    const s16* points;
} DebugBatch;

extern void* fn_8015C390(int);
extern void fn_801ED468(int);
extern void fn_80226D28(int);
extern void fn_801ED118(void);
extern int fn_801EDA7C(s16*, int, int, void*);
extern void fn_801ECF50(int);
extern void fn_80140E70(const s16*, DebugMesh*, u8, int, u8);
extern void fn_800ED4BC(Vector*, int, const char*, ...);

extern char lbl_8024A59C[];
extern s16 lbl_802FC53C[];
extern char lbl_8064DC80[];

void fn_800EC234(int selector)
{
    DebugBatch* batch;
    DebugSource* source;
    DebugMesh* meshes;
    const s16* points;
    int i;

    batch = fn_8015C390(selector);
    source = batch->sources;
    meshes = batch->meshes;
    points = batch->points;
    fn_801ED468(0x1B);
    fn_80226D28(0);
    fn_801ED118();
    fn_801EDA7C(lbl_802FC53C, 0, 0x2BF, 0);
    fn_801ECF50(4);

    i = 0;
    while (i < batch->count) {
        DebugMesh* mesh = &meshes[source->slot];
        fn_80140E70(points, mesh, 8, 7, 0x80);
        fn_800ED4BC(&mesh->position, 8, lbl_8024A59C, i, source,
                    lbl_8064DC80, source->value);
        i++;
        source++;
    }
}
