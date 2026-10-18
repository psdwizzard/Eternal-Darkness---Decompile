/* GXSetTexCoordGen2: program a texture coordinate generator in XF and
 * record its texture matrix index. */
typedef unsigned char u8;
typedef unsigned long u32;

typedef struct GXData {
    u8 pad0[0x80];
    u32 matIdxA;
    u32 matIdxB;
} GXData;
extern GXData *gx;

typedef enum {
    GX_TG_MTX3x4, GX_TG_MTX2x4,
    GX_TG_BUMP0, GX_TG_BUMP1, GX_TG_BUMP2, GX_TG_BUMP3,
    GX_TG_BUMP4, GX_TG_BUMP5, GX_TG_BUMP6, GX_TG_BUMP7,
    GX_TG_SRTG
} GXTexGenType;

typedef enum {
    GX_TG_POS, GX_TG_NRM, GX_TG_BINRM, GX_TG_TANGENT,
    GX_TG_TEX0, GX_TG_TEX1, GX_TG_TEX2, GX_TG_TEX3,
    GX_TG_TEX4, GX_TG_TEX5, GX_TG_TEX6, GX_TG_TEX7,
    GX_TG_TEXCOORD0, GX_TG_TEXCOORD1, GX_TG_TEXCOORD2, GX_TG_TEXCOORD3,
    GX_TG_TEXCOORD4, GX_TG_TEXCOORD5, GX_TG_TEXCOORD6,
    GX_TG_COLOR0, GX_TG_COLOR1
} GXTexGenSrc;

#define GX_VA_TEX0MTXIDX 1

#define SET_REG_FIELD(reg, size, shift, val) \
    ((reg) = ((u32)(reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)))

#define GX_WRITE_U8(v) (*(volatile u8 *)0xCC008000 = (u8)(v))
#define GX_WRITE_U32(v) (*(volatile u32 *)0xCC008000 = (u32)(v))

extern void __GXSetMatrixIndex(int attr);

void GXSetTexCoordGen2(int dst_coord, GXTexGenType func, GXTexGenSrc src_param, u32 mtx,
                 u8 normalize, u32 pt_texmtx)
{
    u32 reg = 0;
    u32 row;
    u32 form;

    form = 0;
    row = 5;
    switch (src_param) {
    case GX_TG_POS:     row = 0;  form = 1; break;
    case GX_TG_NRM:     row = 1;  form = 1; break;
    case GX_TG_BINRM:   row = 3;  form = 1; break;
    case GX_TG_TANGENT: row = 4;  form = 1; break;
    case GX_TG_COLOR0:  row = 2;  break;
    case GX_TG_COLOR1:  row = 2;  break;
    case GX_TG_TEX0:    row = 5;  break;
    case GX_TG_TEX1:    row = 6;  break;
    case GX_TG_TEX2:    row = 7;  break;
    case GX_TG_TEX3:    row = 8;  break;
    case GX_TG_TEX4:    row = 9;  break;
    case GX_TG_TEX5:    row = 10; break;
    case GX_TG_TEX6:    row = 11; break;
    case GX_TG_TEX7:    row = 12; break;
    case GX_TG_TEXCOORD0:
    case GX_TG_TEXCOORD1:
    case GX_TG_TEXCOORD2:
    case GX_TG_TEXCOORD3:
    case GX_TG_TEXCOORD4:
    case GX_TG_TEXCOORD5:
    case GX_TG_TEXCOORD6:
    default:
        break;
    }

    switch (func) {
    case GX_TG_MTX2x4:
        SET_REG_FIELD(reg, 1, 1, 0);
        SET_REG_FIELD(reg, 1, 2, form);
        SET_REG_FIELD(reg, 3, 4, 0);
        SET_REG_FIELD(reg, 5, 7, row);
        break;
    case GX_TG_MTX3x4:
        SET_REG_FIELD(reg, 1, 1, 1);
        SET_REG_FIELD(reg, 1, 2, form);
        SET_REG_FIELD(reg, 3, 4, 0);
        SET_REG_FIELD(reg, 5, 7, row);
        break;
    case GX_TG_BUMP0:
    case GX_TG_BUMP1:
    case GX_TG_BUMP2:
    case GX_TG_BUMP3:
    case GX_TG_BUMP4:
    case GX_TG_BUMP5:
    case GX_TG_BUMP6:
    case GX_TG_BUMP7:
        SET_REG_FIELD(reg, 1, 1, 0);
        SET_REG_FIELD(reg, 1, 2, form);
        SET_REG_FIELD(reg, 3, 4, 1);
        SET_REG_FIELD(reg, 5, 7, row);
        SET_REG_FIELD(reg, 3, 12, src_param - GX_TG_TEXCOORD0);
        SET_REG_FIELD(reg, 3, 15, func - GX_TG_BUMP0);
        break;
    case GX_TG_SRTG:
        SET_REG_FIELD(reg, 1, 1, 0);
        SET_REG_FIELD(reg, 1, 2, form);
        if (src_param == GX_TG_COLOR0) {
            SET_REG_FIELD(reg, 3, 4, 2);
        } else {
            SET_REG_FIELD(reg, 3, 4, 3);
        }
        SET_REG_FIELD(reg, 5, 7, 2);
        break;
    default:
        break;
    }

    GX_WRITE_U8(0x10);
    GX_WRITE_U32(0x1040 + dst_coord);
    GX_WRITE_U32(reg);

    reg = 0;
    SET_REG_FIELD(reg, 6, 0, pt_texmtx - 64);
    SET_REG_FIELD(reg, 1, 8, normalize);
    GX_WRITE_U8(0x10);
    GX_WRITE_U32(0x1050 + dst_coord);
    GX_WRITE_U32(reg);

    switch (dst_coord) {
    case 0: SET_REG_FIELD(gx->matIdxA, 6, 6, mtx); break;
    case 1: SET_REG_FIELD(gx->matIdxA, 6, 12, mtx); break;
    case 2: SET_REG_FIELD(gx->matIdxA, 6, 18, mtx); break;
    case 3: SET_REG_FIELD(gx->matIdxA, 6, 24, mtx); break;
    case 4: SET_REG_FIELD(gx->matIdxB, 6, 0, mtx); break;
    case 5: SET_REG_FIELD(gx->matIdxB, 6, 6, mtx); break;
    case 6: SET_REG_FIELD(gx->matIdxB, 6, 12, mtx); break;
    default: SET_REG_FIELD(gx->matIdxB, 6, 18, mtx); break;
    }

    __GXSetMatrixIndex(dst_coord + GX_VA_TEX0MTXIDX);
}
