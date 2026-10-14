/* GXLoadTexObj: select a texture region and load the texture object. */
typedef unsigned char u8;
typedef unsigned long u32;

typedef struct GXTexObjInt GXTexObjInt;
typedef struct GXTexRegionInt GXTexRegionInt;
typedef GXTexRegionInt *(*GXTexRegionCallback)(GXTexObjInt *obj, u32 id);

typedef struct GXData {
    u8 pad0[0x410];
    GXTexRegionCallback texRegionCallback;
} GXData;

extern GXData *gx;
extern void fn_80228954(GXTexObjInt *t, GXTexRegionInt *r, u32 id);

void fn_80228AFC(GXTexObjInt *obj, u32 id)
{
    GXTexRegionInt *region = gx->texRegionCallback(obj, id);
    fn_80228954(obj, region, id);
}
