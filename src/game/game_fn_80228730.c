/* GXInitTexObjLOD: set the filtering and LOD parameters of a texture
 * object (min/mag filter, LOD range and bias, edge LOD, anisotropy). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef float f32;

typedef struct __GXTexObjInt {
    u32 mode0;
    u32 mode1;
    u32 image0;
    u32 image3;
    void *userData;
    u32 fmt;
    u32 tlutName;
    u16 loadCnt;
    u8 loadFmt;
    u8 flags;
} __GXTexObjInt;

typedef struct GXTexObj {
    u32 dummy[8];
} GXTexObj;

#define SET_REG_FIELD(reg, size, shift, val) \
    ((reg) = ((u32)(reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)))

/* GX2HWFiltConv: GXTexFilter -> hardware min filter encoding */
extern u8 GX2HWFiltConv[8];

void GXInitTexObjLOD(GXTexObj *obj, int min_filt, int mag_filt, f32 min_lod, f32 max_lod,
                 f32 lod_bias, u8 bias_clamp, u8 do_edge_lod, u32 max_aniso)
{
    u8 lbias;
    u8 lmin;
    u8 lmax;
    __GXTexObjInt *t = (__GXTexObjInt *)obj;

    if (lod_bias < -4.0f) {
        lod_bias = -4.0f;
    } else if (lod_bias >= 4.0f) {
        lod_bias = 3.99f;
    }

    lbias = (u8)(32.0f * lod_bias);
    SET_REG_FIELD(t->mode0, 8, 9, lbias);
    SET_REG_FIELD(t->mode0, 1, 4, (mag_filt == 1) ? 1 : 0);
    SET_REG_FIELD(t->mode0, 3, 5, GX2HWFiltConv[min_filt]);
    SET_REG_FIELD(t->mode0, 1, 8, do_edge_lod ? 0 : 1);
    SET_REG_FIELD(t->mode0, 1, 17, 0);
    SET_REG_FIELD(t->mode0, 1, 18, 0);
    SET_REG_FIELD(t->mode0, 2, 19, max_aniso);
    SET_REG_FIELD(t->mode0, 1, 21, bias_clamp);

    if (min_lod < 0.0f) {
        min_lod = 0.0f;
    } else if (min_lod > 10.0f) {
        min_lod = 10.0f;
    }
    lmin = (u8)(16.0f * min_lod);

    if (max_lod < 0.0f) {
        max_lod = 0.0f;
    } else if (max_lod > 10.0f) {
        max_lod = 10.0f;
    }
    lmax = (u8)(16.0f * max_lod);

    SET_REG_FIELD(t->mode1, 8, 0, lmin);
    SET_REG_FIELD(t->mode1, 8, 8, lmax);
}
