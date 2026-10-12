typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;

typedef struct Header {
    u16 magic;
    u16 version;
} Header;

typedef struct ResourceTable ResourceTable;

typedef struct ModelNode {
    u8 pad0[0x3C];
    struct ModelNode* parent; /* stored as node index, -1 for none */
    u8 pad40[0x10];
} ModelNode; /* size 0x50 */

typedef struct ModelSection {
    u8 pad0[0x104];
    u8* data0; /* stored as byte sizes, converted to running pointers */
    u8* data1;
    u8* data2;
} ModelSection; /* size 0x110 */

typedef struct ModelElem18 {
    u8 pad0[0x18];
} ModelElem18;

typedef struct ModelElemC {
    u8 pad0[0xC];
} ModelElemC;

typedef struct ModelElem14 {
    u8 pad0[0x14];
} ModelElem14;

typedef struct ModelElem1C {
    u8 pad0[0x1C];
} ModelElem1C;

typedef struct ModelMesh {
    u8 pad0[0x60];
    u16 count18;
    u8 pad62[2];
    ModelElem18* list18;
    u16 countC;
    u8 pad6A[2];
    ModelElemC* listC;
    u16 count14;
    u8 pad72[2];
    ModelElem14* list14;
} ModelMesh; /* size 0x78 */

typedef struct ModelGroup {
    u8 pad0[6];
    u16 indexCount;
    u16* indices;
    u8 padC[4];
    u16 count1C;
    u8 pad12[2];
    ModelElem1C* list1C;
} ModelGroup; /* size 0x18 */

typedef struct ModelMaterial {
    u8 pad0[4];
    s16 slotA;
    u8 pad6[8];
    s16 slotB;
    u8 pad10[0x10];
} ModelMaterial; /* size 0x20 */

typedef struct Model {
    Header header;
    u8 pad4[4];
    u16 nodeCount;
    u8 padA[0x1A];
    ModelNode* nodes;
    void* p28;
    void* p2C;
    void* p30;
    void* p34;
    void* p38;
    void* p3C;
    void* p40;
    void* p44;
    void* p48;
    void* p4C;
    void* p50;
    void* p54;
    u8 pad58[4];
    int materialCount;
    ModelMaterial* materials;
    u8 pad64[4];
    void* resources;
    u8 pad6C[2];
    u16 sectionCount;
    ModelSection* sections;
    u8 pad74[0xC];
    void* p80;
    u16 meshCountA;
    u8 pad86[2];
    ModelMesh* meshesA;
    u16 meshCountB;
    u8 pad8E[2];
    ModelMesh* meshesB;
    u8 pad94[4];
    ModelElem18* elems18;
    u8 pad9C[4];
    ModelElemC* elemsC;
    u8 padA4[2];
    u16 flags;
    ModelElem14* elems14;
    void* pAC;
    void* pB0;
    void* pB4;
    u8 padB8[4];
    ModelElem1C* elems1C;
    u8 padC0[0x1C];
    void* pDC;
    int groupCount;
    ModelGroup* groups;
    u8 padE8[4];
    u16* indices;
    u8 padF0[4];
    void* pF4;
} Model;

int fn_80125D50(Header* header);
void fn_8015DAB0(ResourceTable* table);

/* Convert a file-relative offset into an absolute pointer. */
#define RELOC(m, field) \
    ((m)->field = (void*)((u8*)(m) + (u32)(m)->field))
/* Same, but a zero offset means "no data" and stays NULL. */
#define RELOC_OPT(m, field) \
    ((m)->field = (int)(m)->field == 0 ? 0 : (void*)((u8*)(m) + (u32)(m)->field))

Model* fn_80125788(Model* model)
{
    int i;
    u8* data;

    if (model == 0) {
        return 0;
    }

    fn_80125D50(&model->header);

    RELOC_OPT(model, nodes);
    RELOC_OPT(model, p2C);
    RELOC(model, p28);
    RELOC(model, p30);
    RELOC(model, p34);
    RELOC(model, p38);
    RELOC(model, p3C);
    RELOC(model, p40);
    RELOC(model, p44);
    RELOC(model, p48);
    RELOC_OPT(model, p4C);
    RELOC(model, p50);
    RELOC_OPT(model, p54);
    RELOC_OPT(model, resources);
    RELOC_OPT(model, materials);
    if (model->resources != 0) {
        fn_8015DAB0((ResourceTable*)model->resources);
    }
    RELOC_OPT(model, p80);
    RELOC_OPT(model, elems1C);
    RELOC_OPT(model, sections);
    data = (u8*)(model->sections + model->sectionCount);
    RELOC_OPT(model, meshesA);
    RELOC_OPT(model, meshesB);
    RELOC_OPT(model, elems18);
    RELOC_OPT(model, elemsC);
    RELOC_OPT(model, elems14);
    RELOC_OPT(model, pAC);
    RELOC_OPT(model, pB0);
    RELOC_OPT(model, pB4);
    RELOC_OPT(model, pDC);
    RELOC_OPT(model, groups);
    RELOC_OPT(model, indices);
    RELOC_OPT(model, pF4);

    for (i = 0; i < model->nodeCount; i++) {
        ModelNode* node = &model->nodes[i];
        int parent = (int)node->parent;

        node->parent = &model->nodes[parent];
        if (parent == -1) {
            node->parent = 0;
        }
    }

    for (i = 0; i < model->sectionCount; i++) {
        ModelSection* section = &model->sections[i];
        u32 size;

        size = (u32)section->data0;
        section->data0 = data;
        data += size;
        size = (u32)section->data1;
        section->data1 = data;
        data += size;
        size = (u32)section->data2;
        section->data2 = data;
        data += size;
    }

    for (i = 0; i < model->meshCountA; i++) {
        ModelMesh* mesh = &model->meshesA[i];

        if (mesh->count18 != 0) {
            mesh->list18 = &model->elems18[(u32)mesh->list18];
        }
        if (mesh->countC != 0) {
            mesh->listC = &model->elemsC[(u32)mesh->listC];
        }
        if (mesh->count14 != 0) {
            mesh->list14 = &model->elems14[(u32)mesh->list14];
        }
    }

    for (i = 0; i < model->meshCountB; i++) {
        ModelMesh* mesh = &model->meshesB[i];

        if (mesh->count18 != 0) {
            mesh->list18 = &model->elems18[(u32)mesh->list18];
        }
        if (mesh->countC != 0) {
            mesh->listC = &model->elemsC[(u32)mesh->listC];
        }
        if (mesh->count14 != 0) {
            mesh->list14 = &model->elems14[(u32)mesh->list14];
        }
    }

    for (i = 0; i < model->groupCount; i++) {
        ModelGroup* group = &model->groups[i];

        if (group->indexCount != 0) {
            group->indices = &model->indices[(u32)group->indices];
        }
        if (group->count1C != 0) {
            group->list1C = &model->elems1C[(u32)group->list1C];
        }
    }

    model->flags &= ~3;
    for (i = 0; i < model->materialCount; i++) {
        ModelMaterial* material = &model->materials[i];

        if (material->slotB != -1) {
            model->flags |= 1;
        }
        if (material->slotA != -1) {
            model->flags |= 2;
        }
        if ((model->flags & 3) == 3) {
            break;
        }
    }

    return model;
}
