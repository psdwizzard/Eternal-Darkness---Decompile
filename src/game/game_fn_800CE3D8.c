typedef unsigned char u8;

typedef struct AttributeBlock {
    u8 positions[2][0x18];
    u8 colors[2][0x10];
    u8 texcoords[2][0x10];
} AttributeBlock;

typedef struct Data {
    u8 pad[8];
    AttributeBlock blocks[2];
} Data;

typedef struct RuntimeState {
    u8 pad[0x1C];
    Data *data;
} RuntimeState;

extern void *fn_80201B8C();
extern int fn_801ED57C(int);
extern void DCFlushRange(void *, unsigned int);
extern void fn_80027150(void *, void *, void *);
extern void GXSetAlphaUpdate(int);
extern void GXSetColorUpdate(int);
extern void fn_801ECC4C(void);
extern void fn_801EA9F8(void);
extern int lbl_8064D738;

void fn_800CE3D8(void *object)
{
    int saved = fn_801ED57C(0);
    Data *data = ((RuntimeState *)fn_80201B8C(object))->data;
    AttributeBlock *first = &data->blocks[0];
    AttributeBlock *second = &data->blocks[1];

    DCFlushRange(first->positions[lbl_8064D738], 0x18);
    DCFlushRange(first->texcoords[lbl_8064D738], 0x10);
    DCFlushRange(first->colors[lbl_8064D738], 0x10);
    fn_80027150(first->positions[lbl_8064D738],
                first->colors[lbl_8064D738], first->texcoords[lbl_8064D738]);
    DCFlushRange(second->positions[lbl_8064D738], 0x18);
    DCFlushRange(second->texcoords[lbl_8064D738], 0x10);
    DCFlushRange(second->colors[lbl_8064D738], 0x10);
    GXSetAlphaUpdate(1);
    GXSetColorUpdate(1);
    fn_80027150(second->positions[lbl_8064D738],
                second->colors[lbl_8064D738], second->texcoords[lbl_8064D738]);
    GXSetAlphaUpdate(0);
    fn_801ECC4C();
    fn_801EA9F8();
    fn_801ED57C(saved);
}
